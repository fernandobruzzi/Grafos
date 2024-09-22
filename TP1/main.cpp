
#include <fstream> 
#include <iostream> 
#include <string>
#include "GrafoMatriz.h"
#include "GrafoAdj.h"
using namespace std;


void write_csv(){

    ofstream myfileadj("resultados/Analise dos dados para representação em Matriz de Adjacencia.csv");
    cout << "abriu o arquivos" << endl; 
    myfileadj << "," << "Memoria utilizada[MB]" << "," << "Desempenho medio BFS[nanosegundos]" <<"," << "Desempenho medio DFS[nanosegundos]" << "," << "Pai dos vertices 10; 20; 30 BFS[1]" << "," << "Pai dos vertices 10; 20; 30 DFS[1]" << "," << "Pai dos vertices 10; 20; 30 BFS[2]" << "," << "Pai dos vertices 10; 20; 30 DFS[2]" << "," << "Pai dos vertices 10; 20; 30 BFS[3]" << "," << "Pai dos vertices 10; 20; 30 DFS[3]" << "," << "Distancia (10;20)" << "," << "Distancia(10;30)" << "," << "Distancia(20;30)" << "," << "Quantidade de Componentes conexas" << "," << "Tamanho maior componente conexa" << "," << "Tamanho menor componente conexa" << ","<< "Diametro grafo" << "," << "Diametro aproximado do Grafo";
    cout << "ESCREVREU AS COLUNAS TITULO" << endl; 
    for(int i = 1; i <= 1; i++){
        cout << "entrou no primeiro loop" << endl;
        
        GrafoMatriz grafo(to_string(i));
        
        
        
        vector<vector<int>> vec1 = grafo.parent_3_vertex(1);
        vector<vector<int>> vec2 = grafo.parent_3_vertex(2);
        vector<vector<int>> vec3 = grafo.parent_3_vertex(3);
        vector<vector<int>> components ;
        grafo.connected_components(components);


        cout << "calculou o que precisava" << endl;
        
        
        myfileadj << "\n" << "Grafo " << i << ","; 
        cout << "check0" << endl;
        myfileadj << grafo.size() << "," << grafo.avg_bfs() << "," ;
        cout << "check1" << endl;
        myfileadj << grafo.avg_dfs() << ",";
        myfileadj << vec1[0][0] << " " << vec1[0][1] << " " << vec1[0][2] << "," ;
        cout << "check2" << endl;
        myfileadj << vec1[1][0] << " " << vec1[1][1] << " " << vec1[1][2] << "," ;
        myfileadj << vec2[0][0] << " " << vec2[0][1] << " " << vec2[0][2] << "," ;
        myfileadj << vec2[1][0] << " " << vec2[1][1] << " " << vec2[1][2]<< "," ;
        myfileadj << vec3[0][0] << " " << vec3[0][1] << " " << vec3[0][2] << ",";
        myfileadj << vec3[1][0] << " " << vec3[1][1] << " " << vec3[1][2] << "," ;
        myfileadj << grafo.distance(10,20) << "," << grafo.distance(10,30) << "," << grafo.distance(20,30) << "," ;
        myfileadj << components.size() << "," << components[0].size() << "," ;
        myfileadj<< components.back().size() <<"," << grafo.diameter() << "," << grafo.prox_diameter();

        ofstream myfiletext("resultados/Descrição Grafo por Matriz de Adjacencia" + to_string(i) + "txt");

        cout << "criou arquivo de descricao" << endl;

        myfiletext << "Número de vértices: " << grafo.get_vertex() << endl;
        myfiletext << "Número de arestas: " << grafo.edge_count() << endl;
        myfiletext << "Grau máximo: " << grafo.max_degree() << endl;
        myfiletext << "Grau mínimo: " << grafo.min_degree() << endl;
        myfiletext << "Grau médio: " << grafo.average_degree() << endl;
        myfiletext << "Mediana dos graus: " << grafo.median_degree() << endl;

        cout << "preencheu arquivo de descricao" << endl;
        for (size_t j = 0; j < components.size(); ++j) {
            myfiletext << "Componente: " << (j + 1) << " Tamanho: " << components[j].size() << " Vertices: ";
            for (size_t k = 0; k < components[j].size(); ++k) {
                myfiletext << components[j][k];
                if (k < components[j].size() - 1) {
                    myfiletext << ", "; // virgula entre os vertices
                }
            }
            myfiletext << endl;
        }
        cout << "fechou arquivo de descricao" << endl;
        myfiletext.close(); 
    
    
    }
    myfileadj.close();
    cout << "fechou tudo" << endl;

    ofstream myfilemat("resultados/Analise dos dados para representação em Vetor de Adjacencia.csv");
    
    myfilemat << "," << "Memoria utilizada[MB]" << "," << "Desempenho medio BFS[nanosegundos]" <<"," << "Desempenho medio DFS[nanosegundos]" << "," << "Pai dos vertices 10; 20; 30 BFS[1]" << "," << "Pai dos vertices 10; 20; 30 DFS[1]" << "," << "Pai dos vertices 10; 20; 30 BFS[2]" << "," << "Pai dos vertices 10; 20; 30 DFS[2]" << "," << "Pai dos vertices 10; 20; 30 BFS[3]" << "," << "Pai dos vertices 10; 20; 30 DFS[3]" << "," << "Distancia (10;20)" << "," << "Distancia(10;30)" << "," << "Distancia(20;30)" << "," << "Quantidade de Componentes conexas" << "," << "Tamanho maior componente conexa" << "," << "Tamanho menor componente conexa" << ","<< "Diametro grafo" << "," << "Diametro aproximado do Grafo";

    for(int i = 1; i <= 1; i++){
        
        GrafoMatriz grafo(to_string(i));

        vector<vector<int>> vec1 = grafo.parent_3_vertex(1);
        vector<vector<int>> vec2 = grafo.parent_3_vertex(2);
        vector<vector<int>> vec3 = grafo.parent_3_vertex(3);
        vector<vector<int>> components ;
        grafo.connected_components(components);
        
        myfilemat << "\n" << "Grafo " << i << "," << grafo.size() << "," << grafo.avg_bfs() << "," << grafo.avg_dfs() << "," << vec1[0][0] << " " << vec1[0][1] << " " << vec1[0][2] << "," << vec1[1][0] << " " << vec1[1][1] << " " << vec1[1][2] << "," << vec2[0][0] << " " << vec2[0][1] << " " << vec2[0][2] << "," << vec2[1][0] << " " << vec2[1][1] << " " << vec2[1][2]<< "," << vec3[0][0] << " " << vec3[0][1] << " " << vec3[0][2] << "," << vec3[1][0] << " " << vec3[1][1] << " " << vec3[1][2] << "," << grafo.distance(10,20) << "," << grafo.distance(10,30) << "," << grafo.distance(20,30) << "," << components.size() << "," << components[0].size() << "," << components.back().size() <<"," << grafo.diameter() << "," << grafo.prox_diameter();


        ofstream myfiletext("resultados/Descrição Grafo por Matriz de Adjacencia" + to_string(i) + "txt");

        myfiletext << "Número de vértices: " << grafo.get_vertex() << endl;
        myfiletext << "Número de arestas: " << grafo.edge_count() << endl;
        myfiletext << "Grau máximo: " << grafo.max_degree() << endl;
        myfiletext << "Grau mínimo: " << grafo.min_degree() << endl;
        myfiletext << "Grau médio: " << grafo.average_degree() << endl;
        myfiletext << "Mediana dos graus: " << grafo.median_degree() << endl;

        
        for (size_t j = 0; j < components.size(); ++j) {
            myfiletext << "Componente: " << (j + 1) << " Tamanho: " << components[j].size() << " Vertices: ";
            for (size_t k = 0; k < components[j].size(); ++k) {
                myfiletext << components[j][k];
                if (k < components[j].size() - 1) {
                    myfiletext << ", "; // virgula entre os vertices
                }
            }
            myfiletext << endl;
        }

        myfiletext.close(); 
    
    }
    myfilemat.close();

}




void write2_csv(){

    ofstream myfileadj("resultados/Analise dos dados para representação em Matriz de Adjacencia.csv");
    cout << "abriu o arquivos" << endl; 
    myfileadj << "," << "Memoria utilizada[MB]" << "," << "Desempenho medio BFS[nanosegundos]" <<"," << "Desempenho medio DFS[nanosegundos]" << "," << "Pai dos vertices 10; 20; 30 BFS[1]" << "," << "Pai dos vertices 10; 20; 30 DFS[1]" << "," << "Pai dos vertices 10; 20; 30 BFS[2]" << "," << "Pai dos vertices 10; 20; 30 DFS[2]" << "," << "Pai dos vertices 10; 20; 30 BFS[3]" << "," << "Pai dos vertices 10; 20; 30 DFS[3]" << "," << "Distancia (10;20)" << "," << "Distancia(10;30)" << "," << "Distancia(20;30)" << "," << "Quantidade de Componentes conexas" << "," << "Tamanho maior componente conexa" << "," << "Tamanho menor componente conexa" << ","<< "Diametro grafo" << "," << "Diametro aproximado do Grafo";
    cout << "ESCREVREU AS COLUNAS TITULO" << endl; 
    for(int i = 1; i <= 1; i++){
        cout << "entrou no primeiro loop" << endl;
        
        //primeiro pegamos todas as informações que precisamos para preencher o csv
        GrafoMatriz grafo(to_string(i));
        cout << "calculou1" << endl;
        double tamanho = grafo.size();
        cout << "calculou2" << endl;
        // double avgbfs = grafo.avg_bfs();
                cout << "calculou3" << endl;
        // double avgdfs = grafo.avg_dfs();
                cout << "'calculou4'" << endl;
        vector<vector<int>> vec1 = grafo.parent_3_vertex(1);
                cout << "calculou5" << endl;
        vector<vector<int>> vec2 = grafo.parent_3_vertex(2);
        vector<vector<int>> vec3 = grafo.parent_3_vertex(3);
        vector<vector<int>> components ;
        vector<int> distance(3);
        distance[0] = grafo.distance(10,20);
        cout << "calculou5" << endl;
        distance[1] = grafo.distance(10,30);
        cout << "calculou6" << endl;
        distance[2] = grafo.distance(20,30);
        cout << "calculou7" << endl;
        grafo.connected_components(components);
        cout << "calculou8" << endl;
        int diameter = grafo.diameter();
        cout << "calculou9" << endl;
        int prox_diameter = grafo.prox_diameter();


        cout << "calculou o que precisava" << endl;
        
        myfileadj << "\n" << "Grafo " << i << ","; 
        cout << "check0" << endl;
        // myfileadj << tamanho << "," << avgbfs << "," ;
        cout << "check1" << endl;
        // myfileadj << avgdfs << ",";
        myfileadj << vec1[0][0] << " " << vec1[0][1] << " " << vec1[0][2] << "," ;
        cout << "check2" << endl;
        myfileadj << vec1[1][0] << " " << vec1[1][1] << " " << vec1[1][2] << "," ;
        myfileadj << vec2[0][0] << " " << vec2[0][1] << " " << vec2[0][2] << "," ;
        myfileadj << vec2[1][0] << " " << vec2[1][1] << " " << vec2[1][2]<< "," ;
        myfileadj << vec3[0][0] << " " << vec3[0][1] << " " << vec3[0][2] << ",";
        myfileadj << vec3[1][0] << " " << vec3[1][1] << " " << vec3[1][2] << "," ;
        myfileadj << distance[0] << "," << distance[1] << "," << distance[2] << "," ;
        myfileadj << components.size() << "," << components[0].size() << "," ;
        myfileadj<< components.back().size() <<"," << diameter << "," << prox_diameter;

        // ofstream myfiletext("resultados/Descrição Grafo por Matriz de Adjacencia" + to_string(i) + "txt");

        // cout << "criou arquivo de descricao" << endl;

        // myfiletext << "Número de vértices: " << grafo.get_vertex() << endl;
        // myfiletext << "Número de arestas: " << grafo.edge_count() << endl;
        // myfiletext << "Grau máximo: " << grafo.max_degree() << endl;
        // myfiletext << "Grau mínimo: " << grafo.min_degree() << endl;
        // myfiletext << "Grau médio: " << grafo.average_degree() << endl;
        // myfiletext << "Mediana dos graus: " << grafo.median_degree() << endl;

        // cout << "preencheu arquivo de descricao" << endl;
        // for (size_t j = 0; j < components.size(); ++j) {
        //     myfiletext << "Componente: " << (j + 1) << " Tamanho: " << components[j].size() << " Vertices: ";
        //     for (size_t k = 0; k < components[j].size(); ++k) {
        //         myfiletext << components[j][k];
        //         if (k < components[j].size() - 1) {
        //             myfiletext << ", "; // virgula entre os vertices
        //         }
        //     }
        //     myfiletext << endl;
        // }
        cout << "fechou arquivo de descricao" << endl;
        // myfiletext.close(); 
    
    
    }
    myfileadj.close();
    cout << "fechou tudo" << endl;

    // ofstream myfilemat("resultados/Analise dos dados para representação em Vetor de Adjacencia.csv");
    
    // myfilemat << "," << "Memoria utilizada[MB]" << "," << "Desempenho medio BFS[nanosegundos]" <<"," << "Desempenho medio DFS[nanosegundos]" << "," << "Pai dos vertices 10; 20; 30 BFS[1]" << "," << "Pai dos vertices 10; 20; 30 DFS[1]" << "," << "Pai dos vertices 10; 20; 30 BFS[2]" << "," << "Pai dos vertices 10; 20; 30 DFS[2]" << "," << "Pai dos vertices 10; 20; 30 BFS[3]" << "," << "Pai dos vertices 10; 20; 30 DFS[3]" << "," << "Distancia (10;20)" << "," << "Distancia(10;30)" << "," << "Distancia(20;30)" << "," << "Quantidade de Componentes conexas" << "," << "Tamanho maior componente conexa" << "," << "Tamanho menor componente conexa" << ","<< "Diametro grafo" << "," << "Diametro aproximado do Grafo";

    // for(int i = 1; i <= 1; i++){
        
    //     GrafoMatriz grafo(to_string(i));

    //     vector<vector<int>> vec1 = grafo.parent_3_vertex(1);
    //     vector<vector<int>> vec2 = grafo.parent_3_vertex(2);
    //     vector<vector<int>> vec3 = grafo.parent_3_vertex(3);
    //     vector<vector<int>> components ;
    //     grafo.connected_components(components);
        
    //     myfilemat << "\n" << "Grafo " << i << "," << grafo.size() << "," << grafo.avg_bfs() << "," << grafo.avg_dfs() << "," << vec1[0][0] << " " << vec1[0][1] << " " << vec1[0][2] << "," << vec1[1][0] << " " << vec1[1][1] << " " << vec1[1][2] << "," << vec2[0][0] << " " << vec2[0][1] << " " << vec2[0][2] << "," << vec2[1][0] << " " << vec2[1][1] << " " << vec2[1][2]<< "," << vec3[0][0] << " " << vec3[0][1] << " " << vec3[0][2] << "," << vec3[1][0] << " " << vec3[1][1] << " " << vec3[1][2] << "," << grafo.distance(10,20) << "," << grafo.distance(10,30) << "," << grafo.distance(20,30) << "," << components.size() << "," << components[0].size() << "," << components.back().size() <<"," << grafo.diameter() << "," << grafo.prox_diameter();


    //     ofstream myfiletext("resultados/Descrição Grafo por Matriz de Adjacencia" + to_string(i) + "txt");

    //     myfiletext << "Número de vértices: " << grafo.get_vertex() << endl;
    //     myfiletext << "Número de arestas: " << grafo.edge_count() << endl;
    //     myfiletext << "Grau máximo: " << grafo.max_degree() << endl;
    //     myfiletext << "Grau mínimo: " << grafo.min_degree() << endl;
    //     myfiletext << "Grau médio: " << grafo.average_degree() << endl;
    //     myfiletext << "Mediana dos graus: " << grafo.median_degree() << endl;

        
    //     for (size_t j = 0; j < components.size(); ++j) {
    //         myfiletext << "Componente: " << (j + 1) << " Tamanho: " << components[j].size() << " Vertices: ";
    //         for (size_t k = 0; k < components[j].size(); ++k) {
    //             myfiletext << components[j][k];
    //             if (k < components[j].size() - 1) {
    //                 myfiletext << ", "; // virgula entre os vertices
    //             }
    //         }
    //         myfiletext << endl;
    //     }

    //     myfiletext.close(); 
    
    // }
    // myfilemat.close();

}


int main(){

    write2_csv();

    return 0;

}


