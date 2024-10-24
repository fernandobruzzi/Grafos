#include "GrafoAdj.h"

GrafoAdj::GrafoAdj(string num){

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
    lista_adjacencia.resize(n);
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

    myfile.close();

}


int GrafoAdj:: min_degree(){
    //calculamos o menor grau
    auto min = min_element(degree.begin(),degree.end());
    return (*min);
}

int GrafoAdj:: max_degree(){
    //calculamos o maior grau
    auto max = max_element(degree.begin(),degree.end());
    return (*max);
}

double GrafoAdj:: average_degree(){
    //calculamos o grau médio
    double avg = 0;
    for(int i = 0; i < n; i++){
        avg+=degree[i];
    }
    avg = (avg/n);
    return avg;
}

double GrafoAdj:: median_degree(){
    //calculamos a mediana dos graus

    vector<int> vec = degree; // criamos uma copia para que possamos ordenar os graus sem perder a informação com relacao a posicao
    sort(vec.begin(), vec.end());
    if(n%2!=0){ //se temos uma sequencia com uma quantidade impar de termos, o termo do meio dela(quando ela está em ordem crescente é justamente a mediana)
        return vec[n/2];
    }
    else{
        return ((vec[(n/2)-1]+vec[(n/2)])/2.0); //se a sequencia tem uma qunatidae par de termos temos que fazer a media dos dois termos que dividem a sequencia ao meio
    }
}

int GrafoAdj::edge_count(){
    int edges= 0;
    for(int i = 0 ; i < n ; i++){
        edges+=degree[i];
    }
    return (edges/2);//como uma aresta conecta sempre duas pontas, quando somamos o grau de cada vertice acabamos somando um mesmo grau duas vezes, por isso dividimos por 2
}


void GrafoAdj::BFS(int s, vector<int>&parent, vector<int>&level, double &duration){
    auto start = chrono::high_resolution_clock::now();
    
    queue<int> q;
    level = vector<int>(n, -1); //na bfs vamos considerar que se um vértice não foi descoberto ainda ele está no level -1
    parent = vector<int>(n, -1);//na bfs vamos considerar que se um vértice não tem pai, seu pai é -1

    s--; //fazemos isso por causa da indexacao
    q.push(s); 
    level[s] = 0; //na bfs vamos considerar que o level do vertice onde inciamos a busca é 0
    parent[s] = s; //na bfs vamos considerar que o pai do vertice onde inciiamos a busca é ele mesmo

    while(!q.empty()){
        s = q.front();
        q.pop();
        
        for(pair<int,float>& i:lista_adjacencia[s]){
            if(level[i.first]==-1){
                parent[i.first] = s+1; ////somamos por causa da deducao feita no inicio e por causa da posicao deslocada pela lista
                level[i.first] = level[s] +1; // o level do filho é 1 abaixo do pai
                q.push(i.first);
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    duration = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
}



void GrafoAdj::DFS(int s, vector<int>&parent, vector<int>&level, double &duration){

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

        for(pair<int,float>& i:lista_adjacencia[s]){
            if(level[i.first]==-1){ //note que enquanto um vertice nao tiver sido explorado, ele poderá ter seu pai alterado até que no final tem o pai como sendo quem foi explorado e descobriu ele
                parent[i.first] = s+1; //somamos por causa da deducao feita no inicio e por causa da posicao deslocada pela matriz

                st.push(i.first);
            }
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    duration = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());

}




void GrafoAdj::dfs(int s, vector<bool>&visited, vector<int>&component){
    stack<int> st;
    st.push(s);
    visited[s]=1;

    while(!st.empty()){
        s = st.top();
        st.pop(); 

        for(pair<int,float>&i:lista_adjacencia[s]){
            if(visited[i.first]==0){
                visited[i.first] = 1;
                st.push(i.first);
            }
        }
    
    }
}


void GrafoAdj::connected_components(vector<vector<int>>&components){

    vector<bool> visited(n,0); //como durante a dfs ele sempre marca os visitados, podemos definir um vetor de visitados todo de 0 inicialmente

    for(int i = 0; i < n; i++){//realizamos a BFS em todos os vértices que não tiverem sido atingindo ainda, como no início ninguém foi atingido, começamos do vértice indexado em 0 (vertice 1)
        if(!visited[i]){
            vector<int> component;
            dfs(i, visited, component);
            components.push_back(component);
        }
    }
    sort(components.begin(), components.end(), [](const vector<int>& a, const vector<int>& b){ return a.size() > b.size();});
}

double GrafoAdj::size(){
    //calculamos o tamanho da memória utilizada pela estrutura
    size_t total_size = 0;

    for (const auto& vec : lista_adjacencia) {
        total_size += sizeof(vec); // tamamho do objeto vetor
        total_size += sizeof(pair<int,float>) * vec.capacity(); // tamanho dos elementos do vetor
    }

    //conversao para MB
    double size_in_MB = static_cast<double>(total_size) / (1024 * 1024);
    return size_in_MB;
}

// a partir daqui temos uma sequencia de funcoes que coletam os dados para o relatorio e não precisam de nenhuma explicação específica
double GrafoAdj::avg_bfs(){
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

double GrafoAdj::avg_dfs(){
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

vector<vector<int>> GrafoAdj:: parent_3_vertex(int start){
    
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
mutex mtxq; // muter para um acesso seguro aos recursos thread-safe access to shared resources

void bfs_task(GrafoAdj& graph, int start, int end, int& max_distance) {
    std::vector<int> parent, level;
    double duration;
    for (int i = start; i < end; ++i) {
        graph.BFS(i, parent, level, duration);
        cout << "Grafos Vetor" << i << " " <<  endl;
        int local_max = *std::max_element(level.begin(), level.end());
        std::lock_guard<std::mutex> lock(mtxq);
        if (local_max > max_distance) {
            max_distance = local_max;
        }
    }
}


int GrafoAdj::diameter_multi() {

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


void GrafoAdj::Djikstra_vec(int s, vector<float>&cost, vector<int>&parent, double &duration){

    auto start = chrono::high_resolution_clock::now();
    s--;
    cost.resize(n,INFINITY);
    parent.resize(n, -1);
    vector<bool> explored(n,false);

    cost[s] = 0;
    parent[s] = s;
    explored[s] = true;

    //inicialmente temos que o custo de cada vértice é o peso da aresta que liga u a eles
    for(pair<int,float>&i:lista_adjacencia[s]){
        cost[i.first] = i.second;
        parent[i.first] = s;
    }

    for(int c = 1; c < n; c++){

        float min_cost = INFINITY;
        int v = -1;

        for(int j = 0; j < n; j++){

            if((!explored[j])&&(cost[j] < min_cost)){
                v = j;
                min_cost = cost[j];
            }
        }

        if(min_cost < 0){
        cout << "Dijkstra não pode ser aplicada nesse grafo devido a presença de uma aresta negativa";
        break;
        //se cost[u] < 0, significa que na componente considerada onde estamos aplicando tem uma aresta com custo negativo, logo o dijkstra não irá retornar resultados corretos
        }

        if((v==-1)||(min_cost==INFINITY)){break;}//nao temos mais vertices a serem explorados
        explored[v]=true;

        for(pair<int,float>&u : lista_adjacencia[v]){
            if(explored[u.first]==false){
                if(cost[u.first] > cost[v] + u.second){
                    cost[u.first] = cost[v] + u.second;
                    parent[u.first] = v;
                }
            }

        }

    }
    auto end = chrono::high_resolution_clock::now();
    duration = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
}

void GrafoAdj::Djikstra_heap(int s, vector<float>&cost, vector<int>&parent, double &duration){
    
    auto start = chrono::high_resolution_clock::now();
    s--;

    vector<bool> explored(n,0);
    priority_queue<pair<float, int>, vector<pair<float, int>>, Compare2> heap;

    parent.resize(n,-1);
    cost.resize(n,INFINITY);

    heap.push({0,s});
    cost[s] = 0;
    parent[s] = s;

    while(!heap.empty()){

        auto top = heap.top(); //pegamos o elemento do topo
        int u = top.second;
        heap.pop(); // removemos o elemento do topo

        //como não atualizamos a nossa heap, temos que checar se um vértice já foi explorado antes ou não
        if(explored[u]==false){
        explored[u] = true;

        if(cost[u] < 0){
            cout << "Dijkstra não pode ser aplicada nesse grafo devido a presença de uma aresta negativa";
            break;
            //se cost[u] < 0, significa que na componente considerada onde estamos aplicando tem uma aresta com custo negativo, logo o dijkstra não irá retornar resultados corretos
        }
        
        for(pair<int,float>&v : lista_adjacencia[u]){
            if(cost[v.first] > cost[u] + (v.second)){
                cost[v.first] = cost[u] + (v.second);
                heap.push({v.second+cost[u],v.first});
                parent[v.first] = u;
                
                }
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    duration = double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
}

//a ser calculada corretamente com dijkstra
float GrafoAdj::distance(int i, int j){
    //sabemos que a distancia entre dois vértices é dado pelo caminho mínimo entre eles, por isso usamos Dijkstra
    vector<int> parent;
    vector<float> cost;
    double duration;

    Djikstra_heap(i,cost,parent,duration);
    return(cost[j-1]);
}


float GrafoAdj::diameter(){

    //sabemos que o diamêtro do grafo pode ser obtido calculando a maior menor distância entre um par de vértices, ou seja, precisamos fazer uma BFS em todos os vértices e pegar o maior valor de level
    
    vector<int> parent;
    vector<float> cost;
    double duration;
    float d = -INFINITY; //valor usado para comparacao
    Djikstra_heap(1, cost, parent, duration); //se ao rodar a BFS eu não conseguir atingir todos os vértices do grafo, ele não é conexo
    
    for (int i = 1; i <= n; i++) {
        Djikstra_heap(i, cost, parent,duration);
        auto maximum = max_element(cost.begin(), cost.end());
        if (*maximum > d) {
            d = *maximum;
            }
        }
    return d;
}


double GrafoAdj::avg_dijkstra_vec(){

    vector<int> parent;
    vector<float> cost;
    double duration;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distr(1,n);

    
    int r;
    int i = 0;
    double avg = 0;

    while(i<100){

        r = distr(gen);   
        Djikstra_vec(r,cost,parent,duration);
        avg+= duration;
        i++;
    }
    avg = avg/100;

    return avg;

}


double GrafoAdj::avg_dijkstra_heap(){

        
    vector<int> parent;
    vector<float> cost;
    double duration;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distr(1,n);

    
    int r;
    int i = 0;
    double avg = 0;

    while(i<100){

        r = distr(gen);   
        Djikstra_heap(r,cost,parent,duration);
        avg+= duration;
        i++;
    }
    avg = avg/100;

    return avg;

}

void GrafoAdj::path_i_to_j_and_cost(int i, int j, vector<int>& p, float& c){


    vector<float> cost;
    vector<int> parent;
    double duration;

    Djikstra_heap(i,cost,parent,duration);
    c = cost[j-1];

    if(c==INFINITY){p = {-1};return;}; // nao temos caminho

    p.push_back(j);
    
    int v = j-1;
    while(v!=i-1){
        p.push_back(parent[v]+1);
        v = parent[v];
    }
    reverse(p.begin(),p.end());
}
// GrafoAdj::~GrafoAdj()
// {

// }

