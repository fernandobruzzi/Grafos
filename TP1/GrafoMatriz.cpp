#include "GrafoMatriz.h"

GrafoMatriz::GrafoMatriz(string num){

    string source = "grafos_de_estudo/grafo_.txt";
    source.insert(23, num); //definimos qual o grafo a ser trabalhado

    ifstream myfile; //definimos a variavel para a leitura do arquivo
    myfile.open(source); //abrimos o arquivo que queremos
    
    if(!myfile.is_open()){ //aqui confer  imos se o arquivo conseguiu ser lido
        cerr << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    string linha; //declaramos uma string para guardar cada linha do arquivo de texto

    getline(myfile, linha);//pegamos a primeira linha que é sempre a quantidade de vertices
     
    n = stoi(linha);
    matriz_de_adjacencia.resize(n,vector<bool>(n,0));
    degree.resize(n,0); 

    while(getline(myfile, linha)){
        
        stringstream ss(linha); //separamos a nossa linha
        
        string v, u; 

        //obtemos cada vértice
        ss >> v;
        ss >> u;

        set_edge(stoi(v), stoi(u));

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
            if((matriz_de_adjacencia[s][i])&&(level[i]==-1)){
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

        for(int i = 0; i < n; i++){
            if((matriz_de_adjacencia[s][i])&& (level[i]==-1)){
                st.push(i);
                parent[i] = s+1; //somamos por causa da deducao feita no inicio e por causa da posicao deslocada pela matriz
                level[i] = level[s] + 1; //o nivel do filho é um abaixo do pai
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    duration = double(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
}

int GrafoMatriz::distance(int i, int j){
    //sabemos que a distancia entre dois vértices é dado pelo caminho mínimo entre eles, por isso usamos a BFS
    vector<int> parent, level;
    double duration;
    BFS(i, parent, level, duration);
    
    return(level[j-1]);
}

int GrafoMatriz::diameter() {

    //sabemos que o diamêtro do grafo só é definido quando o mesmo é conexo, e que para achar ele devemos ver todos os caminhos entre arestas para pegar o menor

    vector<int> parent, level;
    double duration;
    int d = 0;
    BFS(1, parent, level, duration); //se ao rodar a BFS eu não conseguir atingir todos os vértices do grafo, ele não é conexo
    auto minimum = min_element(level.begin(), level.end());

    
    if(*minimum == -1){ //se eu tiver algum elemento -1 nos vetor dos levels, significa que tem algum vértice que não foi atingido pela BFS
        return -1; //nesse caso -1 significa que o diametro é infinito
    }
    //caso contrario devemos calcular o diametro realizando bfs em todos os vértices
    for (int i = 1; i <= n; i++) {
        BFS(i, parent, level, duration);
        auto maximum = max_element(level.begin(), level.end());
        if (*maximum > d) {
            d = *maximum;
            }
        }
    return d;
}

int GrafoMatriz::prox_diameter(){
    //sabemos que o diamêtro do grafo só é definido quando o mesmo é conexo, e que para achar ele devemos ver todos os caminhos entre arestas para pegar o menor
    
    //usamos a ideia da heurística "Second BFS para calcular" o diâmetro aproximado
    vector<int> parent, level;
    double duration;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distr(1,n);

    //sorteamos um numero aleatorio para realizar a BFS
    int r = distr(gen);

    BFS(r, parent, level, duration);
    auto max_it = max_element(level.begin(),level.end());
    r = int(max_it - level.begin());
    r++; //somamos por causa da nossa indexacao
    
    auto minimum = min_element(level.begin(), level.end());
    //se ao rodar a BFS eu não conseguir atingir todos os vértices do grafo, ele não é conexo, logo o diametro tem que ser 0
    if(*minimum == -1){
        return -1; //diametro infinito
    }

    BFS(r, parent, level, duration);
    max_it = max_element(level.begin(),level.end());
    return *max_it;
}

//dfs para auxiliar o calculo das componentes conexas
void GrafoMatriz::dfs(int s, vector<bool>&visited, vector<int>&component){
    stack<int> st;
    st.push(s);
    visited[s]=1;

    while(!st.empty()){
        s = st.top();
        st.pop();
        component.push_back(s+1); //somamos 1 por causa da nossa indexacao

        for(int i = 0; i < n; i++){
            if(matriz_de_adjacencia[s][i] && visited[i]==0){
                st.push(i);
                visited[i]=1;
            }

        }
    
    }
}

void GrafoMatriz::connected_components(vector<vector<int>>&components){

    vector<bool> visited(n,0); //como durante a dfs ele sempre marca os visitados, podemos definir um vetor de visitados todo de 0 inicialmente

    for(int i = 0; i < n; i++){ //realizamos a BFS em todos os vértices que não tiverem sido atingindo ainda, como no início ninguém foi atingido, começamos do vértice indexado em 0 (vertice 1)
        if(!visited[i]){
            vector<int> component;
            dfs(i, visited, component);
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
        total_size += sizeof(bool) * vec.capacity(); // tamanho dos elemetos do vetor
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


    //sabemos que o diamêtro do grafo só é definido quando o mesmo é conexo, e que para achar ele devemos ver todos os caminhos entre arestas para pegar o menor

    vector<int> parent, level;
    double duration;
    int d = 0;
    BFS(1, parent, level, duration); //se ao rodar a BFS eu não conseguir atingir todos os vértices do grafo, ele não é conexo
    auto minimum = min_element(level.begin(), level.end());
    if(*minimum == -1){
        return -1;
    }
    //caso contrário temos de calcular o diametro
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
// GrafoMatriz::~GrafoMatriz()
// {

// }

