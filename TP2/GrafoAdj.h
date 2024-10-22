#ifndef GRAFOADJ_H
#define GRAFOADJ_H

#include <algorithm> //para realizar operacoes como max e min em um vetor
#include <vector>
#include <queue> //para bfs
#include <stack> // para dfs
#include <numeric> //
#include <iostream>
#include <fstream> //para a leitura
#include <sstream> //para a leitura
#include <random>//para sortear inteiros  tralvez nao precisa
#include <chrono> //para medir o tempo de execucao

#include <thread> //para fazer multithread para acelerar o algoritmo do diametro
#include <mutex>

using namespace std;

#pragma once

// //comparador usado para heap 
// struct Compare {
//     bool operator()(pair<float, int> const& p1, pair<float, int> const& p2) {
//         return p1.first > p2.first; // usamos a distancia para montar o min heap
//     }
// };

class GrafoAdj
{
public:

    GrafoAdj(string num); //metodo que le um arquivo de texto para criar o grafo de acordo com o arquivo escolhido

    int get_vertex(){return n;};
    int get_degree(int i){return degree[i-1];};

    void set_edge(int i, int j, float w){lista_adjacencia[i-1].push_back(make_pair(j-1, w)); degree[i-1]+=1;};
    
    int min_degree();
    int max_degree();
    double average_degree();
    double median_degree();
    int edge_count();

    void BFS(int s, vector<int>&parent, vector<int>&level, double &duration); //definimos um vertice onde realizamos a busca e passamos dois parametros que serão modificados dentro da funcao
    void DFS(int s, vector<int>&parent, vector<int>&level,double &duration);
    int distance(int u, int v);

    int diameter();
    int prox_diameter(); //nao faz sentido mais tentarmos ver o diametro aproximado já que não tem heuristica admissivel para isso devido aos pesos

    void dfs(vector<vector<pair<int,float>>>, int s, vector<bool>&visited); //temos uma dfs dedicada as componentes conexas
    
    void Grev(vector<vector<pair<int,float>>>&grev); //retorna um Grafo com as arestas invertidas
    void connected_components(vector<vector<int>>&components);


    //conjunto de metodos para facilitar a obtencao dos dados para preencher o relatorio
    double size(); //fornece o tamanho ocupado pelo vetor de adjacencia
    double avg_bfs();
    double avg_dfs();
    vector<vector<int>> parent_3_vertex(int start);

    //diametro em multithreading
    int diameter_multi();

    void Djikstra_vec(int s, vector<float>&cost, vector<int>&parent);


    bool exist_edge(int i, int j){
        i--;
        bool b = false;
        for(pair<int,float>&p : lista_adjacencia[i]){
            if(p.first==j-1){
                b = true;
            }
        }
        return b;
    }
    //falta determinar a funcao de distancai de de diametro ja que precisamos de dijsktra para issso
    // ~GrafoAdj();

private:
    int n; //quantidade de vértices
    vector<vector<pair<int, float>>> lista_adjacencia; //representação em matriz de adjacencia
    vector<int> degree; //grau de cada vértices
};

#endif