#ifndef GRAFOADJ_H
#define GRAFOADJ_H

#include <algorithm> //para realizar operacoes como max e min em um vetor
#include <vector>
#include <queue> //para bfs
#include <stack> // para dfs
#include <numeric> //para inicializacao do vetor parent
#include <iostream>
#include <fstream> //para a leitura
#include <sstream> //para a leitura
#include <random>//para sortear inteiros  tralvez nao precisa
#include <chrono> //para medir o tempo de execucao

using namespace std;

#pragma once

class GrafoAdj
{
public:

    GrafoAdj(string num); //metodo que le um arquivo de texto para criar o grafo de acordo com o arquivo escolhido

    int get_vertex(){return n;};
    int get_degree(int i){return degree[i-1];};

    void set_edge(int i, int j){lista_adjacencia[i-1].push_back(j); lista_adjacencia[j-1].push_back(i); degree[i-1]+=1; degree[j-1]+=1;};
    
    int min_degree();
    int max_degree();
    double average_degree();
    double median_degree();
    int edge_count();

    void BFS(int s, vector<int>&parent, vector<int>&level, double &duration); //definimos um vertice onde realizamos a busca e passamos dois parametros que serão modificados dentro da funcao
    void DFS(int s, vector<int>&parent, vector<int>&level,double &duration);
    int distance(int u, int v);

    int diameter();
    int prox_diameter();

    void dfs(int s, vector<bool>&visited, vector<int>&component); //temos uma dfs dedicada as componentes conexas
    void connected_components(vector<vector<int>>&components);


    //conjunto de metodos para facilitar a obtencao dos dados para preencher o relatorio
    double size(); //fornece o tamanho ocupado pelo vetor de adjacencia
    double avg_bfs();
    double avg_dfs();
    vector<vector<int>> parent_3_vertex(int start);


    // ~GrafoAdj();

private:
    int n; //quantidade de vértices
    vector<vector<int>> lista_adjacencia; //representação em matriz de adjacencia
    vector<int> degree; //grau de cada vértices
};

#endif