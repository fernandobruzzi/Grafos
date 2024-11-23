#ifndef GRAFOADJ_H
#define GRAFOADJ_H

#include <algorithm> //para realizar operacoes como max e min em um vetor
#include <vector>
#include <queue> //para bfs
#include <stack> // para dfs
#include <numeric> 
#include <iostream>
#include <fstream> //para a leitura
#include <sstream> //para a leitura

#include <chrono> //para medir o tempo de execucao
#include <set>  //para criar o conjunto A e B num corte mínimo
#include <limits> //para representar o infinito para inteiros

using namespace std;

#pragma once

//comparador usado para heap 
struct Compare2 {
    bool operator()(pair<float, int> const& p1, pair<float, int> const& p2) {
        return p1.first > p2.first; // usamos a distancia para montar o min heap
    }
};

class GrafoAdj
{
public:

    GrafoAdj(string num, bool directed); //metodo que le um arquivo de texto para criar o grafo de acordo com o arquivo escolhido

    int get_vertex(){return n;};
    int get_degree(int i){return degree[i-1];};

    void set_edge(int i, int j, int c){lista_adjacencia[i-1].push_back({j-1,c,0}); degree[i-1]+=1;}; //inicialmente consideramos o fluxo 0 nas arestas ao ler o grafo


    void find_path_fftask(vector<vector<array<int,2>>>& g_res, int s, int t, vector<array<int,2>>&parent); //funcao usada para achar um caminho entre s e t na bfs executada em ford fulkerson
    void augment_ff(int s, int &f, vector<array<int, 2>>&p, vector<vector<array<int,2>>>&g_res);
    int Ford_Fulkerson(int s, int t, bool store_in_disk, double& execution_time);
    double avg_ff();
    
    pair<set<int>,set<int>> min_cut(int s, int t);
    

private:
    int n; //quantidade de vértices
    vector<vector<array<int,3>>> lista_adjacencia; //representação em vetor de adjaceencia onde lista_adjacencia[u] é um vetor que em cada posicao guarda um array de tres elementos na seguinte ordem: vértice que se conecta a u, capacidade da aresta, fluxo da aresta
    vector<int> degree; //grau de cada vértices
    bool is_directed; //is_directed = 1 true quando o grafo é direcionado e is_directed = 0 false quando o grafo é nao direcionado
    string graph_num; //guarda o numero do grafo que é utilizado na hora de indicar qual o grafo que está sendo trabalhado
};

#endif