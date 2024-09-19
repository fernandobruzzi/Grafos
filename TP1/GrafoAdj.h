#ifndef GRAFOADJ_H
#define GRAFOADJ_H

#include <algorithm> //para realizar operacoes como max e min em um vetor
#include <vector>
#include <queue> //para bfs
#include <stack> // para dfs
#include <numeric> //para inicializacao do vetor parent
#include <iostream>

using namespace std;

#pragma once

class GrafoAdj
{
public:
    GrafoAdj(int v){n=v; lista_adjacencia.resize(v); degree.resize(v,0);}; //ao criarmos nosso objeto definimos uma matriz n x n  e o grau de cada vertice como 0
    
    int get_vertex(){return n;};
    int get_degree(int i){return degree[i-1];};
    
    void set_edge(int i, int j){lista_adjacencia[i-1].push_back(j); lista_adjacencia[j-1].push_back(i); degree[i-1]+=1; degree[j-1]+=1;};
    
    int min_degree();
    int max_degree();
    double average_degree();
    double median_degree();
    int edge_count();

    void BFS(int s, vector<int>&parent, vector<int>&level); //definimos um vertice onde realizamos a busca e passamos dois parametros que serão modificados dentro da funcao
    void DFS(int s, vector<int>&parent, vector<int>&level);
    int distance(int u, int v);

    int diameter();

    void dfs(int s, vector<bool>&visited, vector<int>&component); //temos uma dfs dedicada as componentes conexas
    void connected_components(vector<vector<int>>&components);

    vector<int> neighbors(int u);

    // ~GrafoAdj();

private:
    int n; //quantidade de vértices
    vector<vector<int>> lista_adjacencia; //representação em matriz de adjacencia
    vector<int> degree; //grau de cada vértices
};

#endif