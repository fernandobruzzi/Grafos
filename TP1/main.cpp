#include<bits/stdc++.h>
#include <fstream> 
#include <iostream> 
#include <string>
#include "GrafoMatriz.h"
#include "GrafoAdj.h"
using namespace std;

GrafoMatriz read_graph_matriz(string num){

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
     
    GrafoMatriz grafo(stoi(linha)); 

    while(getline(myfile, linha)){
        
        stringstream ss(linha); //separamos a nossa linha
        
        string v, u;
    
        ss >> v;
        ss >> u;

        grafo.set_edge(stoi(v), stoi(u));

    }

    myfile.close();
    
    return grafo;

}

GrafoAdj read_graph_adj(string num){

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
     
    GrafoAdj grafo(stoi(linha)); 

    while(getline(myfile, linha)){
        
        stringstream ss(linha); //separamos a nossa linha
        
        string v, u;
    
        ss >> v;
        ss >> u;

        grafo.set_edge(stoi(v), stoi(u));

    }

    myfile.close();
    
    return grafo;

}

int main(){
    // GrafoMatriz grafo = read_graph_matriz("3");
    
    GrafoAdj grafo = read_graph_adj("2");


//     cout << "Número de vértices: " << grafo.get_vertex() << endl;
//     cout << "Número de arestas: " << grafo.edge_count() << endl;
//     cout << "Grau máximo: " << grafo.max_degree() << endl;
//     cout << "Grau mínimo: " << grafo.min_degree() << endl;
//     cout << "Grau médio: " << grafo.average_degree() << endl;
//     cout << "Mediana dos graus: " << grafo.median_degree() << endl;

//    vector<vector<int>> components;
//     grafo.connected_components(components);
//     for(int i = 0; i < components.size(); i++){
//         cout << "Componente " << ": "<< components[i].size() << endl;
//     }



//     GrafoAdj grafo1 = read_graph_adj("2");

//     cout << "Número de vértices: " << grafo1.get_vertex() << endl;
//     cout << "Número de arestas: " << grafo1.edge_count() << endl;
//     cout << "Grau máximo: " << grafo1.max_degree() << endl;
//     cout << "Grau mínimo: " << grafo1.min_degree() << endl;
//     cout << "Grau médio: " << grafo1.average_degree() << endl;
//     cout << "Mediana dos graus: " << grafo1.median_degree() << endl;

 vector<vector<int>> components1;
    grafo.connected_components(components1);
    for(int i = 0; i < components1.size(); i++){
        cout << "Componente " << ": "<< components1[i].size() << endl;
    }


    return 0;

}


