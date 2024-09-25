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

#include <thread> //para fazer multithread para acelerar o algoritmo do diametro
#include <mutex>

using namespace std;

#pragma once

class GrafoMatriz
{
public:

    GrafoMatriz(string num);//metodo que le um arquivo de texto para criar o grafo de acordo com o arquivo escolhido

    int get_vertex(){return n;};
    int get_degree(int i){return degree[i-1];};

    void set_edge(int i, int j){matriz_de_adjacencia[i-1][j-1] = 1; matriz_de_adjacencia[j-1][i-1] = 1; degree[i-1]+=1; degree[j-1]+=1;};
    
    int min_degree();
    int max_degree();
    double average_degree();
    double median_degree();
    int edge_count();

    void BFS(int s, vector<int>&parent, vector<int>&level,  double &duration); //definimos um vertice onde realizamos a busca e passamos dois parametros que serão modificados dentro da funcao
    void DFS(int s, vector<int>&parent, vector<int>&level,  double &duration);
    int distance(int u, int v);

    int diameter();
    int prox_diameter(); //determina o diametro aproximado

    void dfs(int s, vector<bool>&visited, vector<int>&component); //temos uma dfs dedicada as componentes conexas
    void connected_components(vector<vector<int>>&components);

    // ~GrafoMatriz();

    //conjunto de funcoes para coletar os dados para o relatorio
    double size(); //fornece o tamanho ocupado pela matriz
    double avg_bfs();
    double avg_dfs();
    vector<vector<int>> parent_3_vertex(int start);
    
    //diametro em multithreading
    int diameter_multi();

private:
    int n; //quantidade de vértices
    vector<vector<bool>> matriz_de_adjacencia; //representação em matriz de adjacencia
    vector<int> degree; //grau de cada vértices
};

#endif