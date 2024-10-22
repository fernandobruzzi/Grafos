#include "GrafoMatriz.h"
const float INF = 1e9;

GrafoMatriz::GrafoMatriz(string num){

    string source = "grafos_de_estudo/grafo_W_.txt";
    source.insert(25, num); //definimos qual o grafo a ser trabalhado
    
    ifstream myfile; //definimos a variavel para a leitura do arquivo
    myfile.open(source); //abrimos o arquivo que queremos
    
    if(!myfile.is_open()){ //aqui confer  imos se o arquivo conseguiu ser lido
        cerr << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    string linha; //declaramos uma string para guardar cada linha do arquivo de texto

    getline(myfile, linha);//pegamos a primeira linha que é sempre a quantidade de vertices
     
    n = stoi(linha);
    matriz_de_adjacencia.resize(n,vector<float>(n,INF));
    
    degree.resize(n,0);
    
    while(getline(myfile, linha)){
        
        stringstream ss(linha); //separamos a nossa linha
        
        string v, u, w; 

        //obtemos cada vértice
        ss >> v;
        ss >> u;
        ss >> w;

        set_edge(stoi(v), stoi(u), stof(w));

    }
}

int GrafoMatriz:: min_degree(){
    //calculamos o menor grau
    auto min = min_element(degree.begin(),degree.end());
    return (*min);
}

int GrafoMatriz:: max_degree(){
    //calculamos o maior grau
    auto max = max_element(degree.begin(),degree.end());
    return (*max);
}

double GrafoMatriz:: average_degree(){
    //calculamos o grau médio
    double avg = 0;
    for(int i = 0; i < n; i++){
        avg+=degree[i];
    }
    avg = (avg/n);
    return avg;
}

double GrafoMatriz:: median_degree(){
    //calculamos a mediana dos graus

    vector<int> vec = degree; // criamos uma copia para que possamos ordenar os graus sem perder a informação com relacao a posicao

    sort(vec.begin(), vec.end()); //precisamos ordenar o vetor de graus para achar a mediana

    if(n%2!=0){ //se temos uma sequencia com uma quantidade impar de termos, o termo do meio dela(quando ela está em ordem crescente é justamente a mediana)
        return vec[n/2];
    }
    else{
        return ((vec[(n/2)-1]+vec[(n/2)])/2.0); //se a sequencia tem uma quantidade par de termos temos que fazer a media dos dois termos que dividem a sequência ao meio
    }
}

int GrafoMatriz::edge_count(){
    int edges= 0;
    for(int i = 0 ; i < n ; i++){
        edges+=degree[i];
    }
    return (edges/2);//como uma aresta conecta sempre duas pontas, quando somamos o grau de cada vertice acabamos somando um mesmo grau duas vezes, por isso dividimos por 2
}


void GrafoMatriz::BFS(int s, vector<int>&parent, vector<int>&level, double &duration){
    
    auto start = chrono::high_resolution_clock::now();
    queue <int> q;
    level = vector<int>(n, -1); //na bfs vamos considerar que se um vértice não foi descoberto ainda ele está no level -1
    parent = vector<int>(n, -1);//na bfs vamos considerar que se um vértice não tem pai, seu pai é -1
    
    s--; //fazemos isso por causa da indexacao
    q.push(s); 
    level[s] = 0;   //na bfs vamos considerar que o level do vertice onde inciamos a busca é 0
    parent[s] = s; //na bfs vamos considerar que o pai do vertice onde inciamos a busca é ele mesmo

    while(!q.empty()){
        s = q.front();
        q.pop();
        for(int i = 0; i<n; i++){
            if((matriz_de_adjacencia[s][i]!= INF)&&(level[i]==-1)){
                parent[i] = s+1; //somamos por causa da deducao feita no inicio e por causa da posicao deslocada pela matriz
                level[i] = level[s] +1; // o level do filho é 1 abaixo do pai
                q.push(i);
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    duration = double(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
}


void GrafoMatriz::DFS(int s, vector<int>&parent, vector<int>&level, double &duration){
    
    auto start = chrono::high_resolution_clock::now();
    stack<int> st;
    level = vector<int>(n, -1); //na dfs vamos considerar que se um vértice não foi descoberto ainda ele está no level -1
    parent = vector<int>(n, -1);//na dfs vamos considerar que se um vértice não tem pai, seu pai é -1

    s--; //fazemos isso por causa da indexacao
    st.push(s); 
    level[s] = 0; //na bfs vamos considerar que o level do vertice onde inciamos a busca é 0
    parent[s] = s; //na dfs vamos considerar que o pai do vertice onde inciiamos a busca é ele mesmo

    while(!st.empty()){
        s = st.top();
        st.pop();
        
        level[s] = level[parent[s]] +1; //aqui vamos explorar um vértice, só quando ele tiver o nivel definido ele será explorado e o seu nivel é um abaixo do pai


        for(int i = 0; i < n; i++){
            if((matriz_de_adjacencia[s][i]!=INF)&& (level[i]==-1)){
                st.push(i);
                parent[i] = s+1; //somamos por causa da deducao feita no inicio e por causa da posicao deslocada pela matriz
                // level[i] = level[s] + 1; //o nivel do filho é um abaixo do pai
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    duration = double(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
}




// int GrafoMatriz::prox_diameter(){
//     //sabemos que o diamêtro do grafo só é definido quando o mesmo é conexo, e que para achar ele devemos ver todos os caminhos entre arestas para pegar o menor

//     //usamos a ideia da heurística "Second BFS para calcular" o diâmetro aproximado
//     vector<int> parent, level;
//     double duration;
//     random_device rd;
//     mt19937 gen(rd());
//     uniform_int_distribution<int> distr(1,n);

//     //sorteamos um numero aleatorio para realizar a BFS
//     int r = distr(gen);

//     BFS(r, parent, level, duration);
//     auto max_it = max_element(level.begin(),level.end());
//     r = int(max_it - level.begin());
//     r++; //somamos por causa da indexacao

//     BFS(r, parent, level, duration);
//     max_it = max_element(level.begin(),level.end());
//     return *max_it;
// }

// dfs para auxiliar o calculo das componentes conexas
void GrafoMatriz::dfs(vector<vector<float>>g, int s, vector<bool>&visited){
    stack<int> st;
    st.push(s);
    visited[s]=1;

    while(!st.empty()){
        s = st.top();
        st.pop();
        

        for(int i = 0; i < n; i++){
            if((g[s][i]!= INF) && visited[i]==0){
                st.push(i);
                visited[i]=1;
            }

        }
    
    }
}

void GrafoMatriz::Grev(vector<vector<float>>&grev){
    grev.resize(n, vector<float>(n,INF));
    
    for(int i = 0; i<n ; i++){
        for(int j = 0; j < n; j++){
            grev[i][j] = matriz_de_adjacencia[j][i];
        }
    }
}

void GrafoMatriz::connected_components(vector<vector<int>>&components){

    vector<float> visited(n,0); //como durante a dfs ele sempre marca os visitados, podemos definir um vetor de visitados todo de 0 inicialmente. Sendo que o vertice so se torna visitado quando tem valor 1 na sua posicao
    vector<vector<float>> grev;
    Grev(grev); //faz o grafo com as arestas invertidas
 

    for(int i = 0; i < n; i++){ //realizamos a BFS em todos os vértices que não tiverem sido atingindo ainda, como no início ninguém foi atingido, começamos do vértice indexado em 0 (vertice 1)
        if(visited[i]!=1){
            vector<bool> vis1(n,0);
            vector<bool> vis2(n,0);

            dfs(matriz_de_adjacencia, i, vis1);
            dfs(grev, i, vis2);
            vector<int> component;

            for(int j = 0; j<n; j++){
                if(vis1[j]&&vis2[j]){
                    visited[j]=1;
                    component.push_back(j+1);//por causa do indice
                }
            }
            components.push_back(component);
        }
    }
    sort(components.begin(), components.end(), [](const vector<int>& a, const vector<int>& b){ return a.size() > b.size();});
}



double GrafoMatriz::size(){
    //calculamos o tamanho da memória utilizada pela estrutura
    size_t total_size = 0;

    for (const auto& vec : matriz_de_adjacencia) {
        total_size += sizeof(vec); // tamanho do objeto vetor
        total_size += sizeof(float) * vec.capacity(); // tamanho dos elemetos do vetor
    }

    // conversao para MB
    double size_in_MB = static_cast<double>(total_size) / (1024 * 1024);
    return size_in_MB;
}


// a partir daqui temos uma sequencia de funcoes que coletam os dados para o relatorio e não precisam de nenhuma explicação específica
double GrafoMatriz::avg_bfs(){
    vector<int> parent, level;
    double duration;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distr(1,n);

    
    int r;
    int i = 0;
    double avg = 0;

    while(i<100){

        r = distr(gen);   
        BFS(r,parent,level,duration);
        avg+= duration;
        i++;
    }
    avg = avg/100;

    return avg;


}

double GrafoMatriz::avg_dfs(){
    vector<int> parent, level;
    double duration;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distr(1,n);

    
    int r;
    int i = 0;
    double avg = 0;

    while(i<100){

        r = distr(gen);   
        DFS(r,parent,level,duration);
        avg+= duration;
        i++;
    }
    avg = avg/100;

    return avg;


}

vector<vector<int>> GrafoMatriz:: parent_3_vertex(int start){

    vector<vector<int>> resultado(2,vector<int>(3,-10));
    
    vector<int> parent, level;
    double duration;
    
    BFS(start, parent, level, duration);
    
    resultado[0][0]= parent[9];
    resultado[0][1]= parent[19];
    resultado[0][2]= parent[29];
    
    
    DFS(start,parent,level,duration);
    
    resultado[1][0]= parent[9];
    resultado[1][1]= parent[19];
    resultado[1][2]= parent[29];
   
    
    return resultado;
}


//metodo definido para o caso de termos um grafo muito grande e precisamos encontrar o diametro
mutex mtx; // muter para um acesso seguro aos recursos thread-safe access to shared resources

void bfs_task(GrafoMatriz& graph, int start, int end, int& max_distance) {

    vector<int> parent, level;
    double duration;
    for (int i = start; i < end; ++i) {
        cout << "Executando BFS para vértice " << i << endl;
        graph.BFS(i, parent, level, duration);
        int local_max = *std::max_element(level.begin(), level.end());

        std::lock_guard<std::mutex> lock(mtx);
        if (local_max > max_distance) {
            max_distance = local_max;
        }
    }
}


int GrafoMatriz::diameter_multi() {


    //sabemos que o diamêtro do grafo pode ser obtido calculando a maior menor distância entre um par de vértices, ou seja, precisamos fazer uma BFS em todos os vértices e pegar o maior valor de level
    int max_distance = -1; // já que não teremos nenhuma distância menor que isso
    int vertex_count = n;
    int num_threads = 8; // número de núcelos do processador
    vector<thread> threads;

    // divisão dos vértices entre as threads
    int vertices_per_thread = (vertex_count + num_threads - 1) / num_threads;

    for (int t = 0; t < num_threads; ++t) {
        int start_vertex = t * vertices_per_thread + 1;
        int end_vertex = std::min(start_vertex + vertices_per_thread, vertex_count + 1);

        threads.emplace_back(bfs_task, std::ref(*this), start_vertex, end_vertex, std::ref(max_distance));
    }

    // espera todas as threads terminarem
    for (auto& t : threads) {
        t.join();
    }

     return max_distance;
}



int GrafoMatriz::min_element_Dijkstra_vec(vector<float> cost, vector<bool> explored){
    
    //usamos o min element para servir de indice e o min_cost para representar o custo, incialmente utilizamos valores que nos permitem com certeza achar um elemento valido que tenha custo minimo
    int min_element = -1;
    float min_cost = INF;

    for(int j = 0 ; j < cost.size(); j++){
        if((cost[j] < min_cost) && (explored[j]==0)){
            min_element = j;
            min_cost = cost[j];
        }
    }

    return min_element;
}

void GrafoMatriz::Djikstra_vec(int s, vector<float>&cost, vector<int>&parent){
    
    s--;
    cost.resize(n, INF);
    parent.resize(n,-1);

    vector<bool> explored(n,0);

    cost[s] = 0;
    parent[s] = s;

    for(int c = 0; c < n; c++){

        // pegamos o elemento de menor custo
        int u = min_element_Dijkstra_vec(cost,explored);
        if(explored[u]){cout << "SENDO REVISITADO";};
        if(u==-1){
            break; //se u == -1 significa que já exploramos tudo que tínhamos que explorar
        }
        if(cost[u] < 0){
            cout << "Dijkstra não pode ser aplicada nesse grafo devido a presença de uma aresta negativa";
            break;
            //se cost[u] < 0, significa que na componente considerada onde estamos aplicando tem uma aresta com custo negativo, logo o dijkstra não irá retornar resultados corretos
        }

        explored[u] = 1;

        for(int i = 0; i < n; i++){
            if((explored[i]==0) &&(matriz_de_adjacencia[u][i]!=INF)){
                if(cost[i] > cost[u] + matriz_de_adjacencia[u][i]){
                    cost[i] = cost[u] + matriz_de_adjacencia[u][i];
                    parent[i] = u;
                }
            }
        }

    }
    
}



void GrafoMatriz::Djikstra_heap(int s, vector<float>&cost, vector<int>&parent){

    s--;
    priority_queue<pair<float, int>, vector<pair<float, int>>, Compare> heap;
    parent.resize(n,-1);
    cost.resize(n,INF);
    vector<bool> explored(n,0);



    heap.push({0,s});
    cost[s] = 0;
    parent[s] = s;


    while(!heap.empty()){

        auto top = heap.top(); //pegamos o elemento do topo
        int u = top.second;
        heap.pop(); // removemos o elemento do topo

        if(cost[u] < 0){
            cout << "Dijkstra não pode ser aplicada nesse grafo devido a presença de uma aresta negativa";
            break;
            //se cost[u] < 0, significa que na componente considerada onde estamos aplicando tem uma aresta com custo negativo, logo o dijkstra não irá retornar resultados corretos
        }
        
        for(int i = 0; i < n; i++){
            if(explored[u]==0){
                if(matriz_de_adjacencia[u][i]!=INF){
                    if(cost[i] > cost[u] + matriz_de_adjacencia[u][i]){
                        cost[i] = cost[u] + matriz_de_adjacencia[u][i];
                        heap.push({cost[u] + matriz_de_adjacencia[u][i],i});
                        parent[i] = u;
                    }
                }
            }
        }
    }
    
}


void GrafoMatriz::Dijkstraporfavor(int src, vector<float>&dist, vector<int>&parent, double &duration) {
    // Iniciando o cronômetro
    auto start = chrono::high_resolution_clock::now();

    src--; // Ajuste de índice para trabalhar com a matriz

    dist = vector<float>(n, INF); // Inicializa distâncias com infinito
    parent = vector<int>(n, -1); // Inicializa os pais como -1
    vector<bool> visited(n, false); // Vetor de vértices visitados

    // Definimos uma fila de prioridade para escolher sempre o vértice com a menor distância
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Distância do vértice origem para ele mesmo é 0
    dist[src] = 0;
    parent[src] = src; // O pai da origem é ela mesma
    pq.push({0, src}); // Colocamos o vértice origem na fila

    while (!pq.empty()) {
        int u = pq.top().second; // Pegamos o vértice com menor distância
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        // Relaxamento das arestas
        for (int v = 0; v < n; ++v) {
            if (matriz_de_adjacencia[u][v] != INF && !visited[v]) {
                int peso = matriz_de_adjacencia[u][v];

                // Verifica se podemos reduzir a distância
                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    parent[v] = u + 1; // Ajuste de índice para a matriz de adjacência
                    pq.push({dist[v], v}); // Adiciona o vértice à fila de prioridade
                }
            }
        }
    }

    // Parando o cronômetro
    auto end = chrono::high_resolution_clock::now();
    duration = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
}

//a ser definido corretamente com dijkstra
int GrafoMatriz::distance(int i, int j){
    //sabemos que a distancia entre dois vértices é dado pelo caminho mínimo entre eles, por isso usamos a BFS
    vector<int> parent, level;
    double duration;
    BFS(i, parent, level, duration);
    
    return(level[j-1]);
}


int GrafoMatriz::diameter() {

    //sabemos que o diamêtro do grafo pode ser obtido calculando a maior menor distância entre um par de vértices, ou seja, precisamos fazer uma BFS em todos os vértices e pegar o maior valor de level
    
    vector<int> parent, level;
    double duration;
    int d = -1; //menor valor possível para level
    BFS(1, parent, level, duration); //se ao rodar a BFS eu não conseguir atingir todos os vértices do grafo, ele não é conexo
    
    for (int i = 1; i <= n; i++) {
        BFS(i, parent, level, duration);
        auto maximum = max_element(level.begin(), level.end());
        if (*maximum > d) {
            d = *maximum;
            }
        }
    return d;
}