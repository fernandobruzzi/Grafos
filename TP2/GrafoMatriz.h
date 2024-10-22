#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include <algorithm> //para realizar operacoes como max e min em um vetor
#include <vector>
#include <queue> //para bfs
#include <stack> // para dfs
#include <numeric> 
#include <iostream>
#include <fstream> //para a leitura
#include <sstream> //para a leitura
#include <random>//para sortear inteiros  tralvez nao precisa
#include <chrono> //para medir o tempo de execucao
#include <utility> //para montarmos nosso min heap com um par de valores valor e vertice
// #include <limits> //para representar infinito

#include <thread> //para fazer multithread para acelerar o algoritmo do diametro
#include <mutex>

using namespace std;

#pragma once

//comparador usado para heap 
struct Compare {
    bool operator()(pair<float, int> const& p1, pair<float, int> const& p2) {
        return p1.first > p2.first; // usamos a distancia para montar o min heap
    }
};

class GrafoMatriz
{
public:

    GrafoMatriz(string num);//metodo que le um arquivo de texto para criar o grafo de acordo com o arquivo escolhido

    int get_vertex(){return n;};
    int get_degree(int i){return degree[i-1];};

    void set_edge(int i, int j, float w){matriz_de_adjacencia[i-1][j-1] = w; degree[i-1]++;};
    
    int min_degree();
    int max_degree();
    double average_degree();
    double median_degree();
    int edge_count();

    //tanto a DFS quanto a BFS só realizam a exploração, nao retornam distancias minimas devido ao peso das arestas
    void BFS(int s, vector<int>&parent, vector<int>&level,  double &duration); //definimos um vertice onde realizamos a busca e passamos dois parametros que serão modificados dentro da funcao
    void DFS(int s, vector<int>&parent, vector<int>&level,  double &duration);

    int diameter();
    int prox_diameter(); //nao faz sentido mais tentarmos ver o diametro aproximado já que não tem heuristica admissivel para isso devido aos pesos

    void dfs(vector<vector<float>>g, int s, vector<bool>&visited); //temos uma dfs dedicada as componentes conexas
    void Grev(vector<vector<float>> &grev);//retorna um Grafo com as arestas invertidas;
    void connected_components(vector<vector<int>>&components);

    // ~GrafoMatriz();

    //conjunto de funcoes para coletar os dados para o relatorio
    double size(); //fornece o tamanho ocupado pela matriz
    double avg_bfs();
    double avg_dfs();
    vector<vector<int>> parent_3_vertex(int start);
    
    //diametro em multithreading
    int diameter_multi();

    int min_element_Dijkstra_vec(vector<float> cost, vector<bool> explored);
    void Djikstra_vec(int s, vector<float>&cost, vector<int>&parent);
    void Djikstra_heap(int s, vector<float>&cost, vector<int>&parent);

    int distance(int u, int v);

    void Dijkstraporfavor(int src, vector<float>&dist, vector<int>&parent, double &duration);

    //falta determinar a funcao de distancai de de diametro ja que precisamos de dijsktra para issso

private:
    int n; //quantidade de vértices
    vector<vector<float>> matriz_de_adjacencia; //representação em matriz de adjacencia
    vector<int> degree; //grau de cada vértices
   };

#endif