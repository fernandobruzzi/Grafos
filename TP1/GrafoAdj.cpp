#include "GrafoAdj.h"

int GrafoAdj:: min_degree(){
    auto min = min_element(degree.begin(),degree.end());
    return (*min);
}

int GrafoAdj:: max_degree(){
    auto max = max_element(degree.begin(),degree.end());
    return (*max);
}

double GrafoAdj:: average_degree(){
    double avg = 0;
    for(int i = 0; i < n; i++){
        avg+=degree[i];
    }
    avg = (avg/n);
    return avg;
}

double GrafoAdj:: median_degree(){
    vector<int> vec = degree; // criamos uma copia para que possamos ordenar os graus sem perder a informação com relacao a posicao
    sort(vec.begin(), vec.end());
    if(n%2!=0){ //se temos uma sequencia com uma quantidade impar de termos, o termo do meio dela(quando ela está em ordem crescente é justamente a mediana)
        return vec[n/2];
    }
    else{
        return ((vec[(n/2)-1]+vec[(n/2)])/2.0); //se a sequencia tem uma qunatidae par de termos temos que fazer a media dos dois termos que dividem a seuqencia ao meio
    }
}

int GrafoAdj::edge_count(){
    int edges= 0;
    for(int i = 0 ; i < n ; i++){
        edges+=degree[i];
    }
    return (edges/2);//como uma aresta conecta sempre duas pontas, quando somamos o grau de cada vertice acabamos somando um mesmo grau duas vezes, por isso dividimos por 2
}


void GrafoAdj::BFS(int s, vector<int>&parent, vector<int>&level){
    queue<int> q;
    level = vector<int>(n, -1); //na bfs vamos considerar que se um vértice não foi descoberto ainda ele está no level -1
    parent = vector<int>(n, -1);//na bfs vamos considerar que se um vértice não tem pai, seu pai é -1

    s--; //fazemos isso por causa da indexacao
    q.push(s); 
    level[s] = 0;
    parent[s] = s; //na bfs vamos considerar que o pai do vertice onde inciiamos a busca é ele mesmo

    while(!q.empty()){
        s = q.front();
        q.pop();
        
        for(int& i:lista_adjacencia[s]){
            if(level[i-1]==-1){
                parent[i-1] = s; //na hora de ler o vetor de pais fora da BFS devemos considerar que o pai de um vértice v é pai[v] +1, com v representando um numero INTEIRO(1,2,...)
                level[i-1] = level[s] +1; // o level do filho é 1 abaixo do pai
                q.push(i-1);
            }
        }
    }
}

void GrafoAdj::DFS(int s, vector<int>&parent, vector<int>&level){
    stack<int> st;
    level = vector<int>(n, -1); //na dfs vamos considerar que se um vértice não foi descoberto ainda ele está no level -1
    parent = vector<int>(n, -1);//na dfs vamos considerar que se um vértice não tem pai, seu pai é -1

    s--; //fazemos isso por causa da indexacao
    st.push(s); 
    level[s] = 0;
    parent[s] = s; //na dfs vamos considerar que o pai do vertice onde inciiamos a busca é ele mesmo

    while(!st.empty()){
        s = st.top();
        st.pop();

        for(int& i:lista_adjacencia[s]){
            if(level[i-1]==-1){
                parent[i-1] = s; //na hora de ler o vetor de pais fora da BFS devemos considerar que o pai de um vértice v é pai[v] +1, com v representando um numero INTEIRO(1,2,...)
                level[i-1] = level[s] +1; // o level do filho é 1 abaixo do pai
                st.push(i-1);
            }
        }
    }
}

int GrafoAdj::distance(int i, int j){
    vector<int> parent, level;

    BFS(i, parent, level);

    return(level[j-1]);
}

int GrafoAdj::diameter(){
    //para achar o diametro de um grafo fazemos o vemos o maior dos menores caminhos(BFS) entre cada par de vertices
    vector<int> parent, level;
    int d=0;
    for(int i = 0; i< n; i++){
        BFS(i, parent,level);
        auto max = max_element(level.begin(), level.end());
        if(*max > d){
            d = *max;
        }
    }
    return d;
}


void GrafoAdj::dfs(int s, vector<bool>&visited, vector<int>&component){
    stack<int> st;
    st.push(s);
    visited[s]=1;

    while(!st.empty()){
        s = st.top();
        st.pop();
        component.push_back(s+1); //somamos 1 por causa da nossa indexacao

        for(int& i:lista_adjacencia[s]){
            if(visited[i-1]==0){
                visited[i-1] = 1;
                st.push(i-1);
            }
        }
    
    }
}

void GrafoAdj::connected_components(vector<vector<int>>&components){

    vector<bool> visited(n,0); //como durante a dfs ele sempre marca os visitados, podemos definir um vetor de visitados todo de 0 inicialmente

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            vector<int> component;
            dfs(i, visited, component);
            components.push_back(component);
        }
    }
    sort(components.begin(), components.end(), [](const vector<int>& a, const vector<int>& b){ return a.size() > b.size();});
}


// GrafoAdj::~GrafoAdj()
// {

// }

