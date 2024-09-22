
#include <fstream> 
#include <iostream> 
#include <string>
#include "GrafoMatriz.h"
#include "GrafoAdj.h"



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

    ofstream myfilemat("resultados/Analise dos dados para representação em Matriz de Adjacencia.csv");
    if (!myfilemat.is_open()) {
    cerr << "Erro ao abrir o arquivo CSV" << endl;
    return;
    }
    
    myfilemat << "," << "Memoria utilizada[MB]" << "," << "Desempenho medio BFS[nanosegundos]" <<"," << "Desempenho medio DFS[nanosegundos]" << "," << "Pai dos vertices 10; 20; 30 BFS[1]" << "," << "Pai dos vertices 10; 20; 30 DFS[1]" << "," << "Pai dos vertices 10; 20; 30 BFS[2]" << "," << "Pai dos vertices 10; 20; 30 DFS[2]" << "," << "Pai dos vertices 10; 20; 30 BFS[3]" << "," << "Pai dos vertices 10; 20; 30 DFS[3]" << "," << "Distancia (10;20)" << "," << "Distancia(10;30)" << "," << "Distancia(20;30)" << "," << "Quantidade de Componentes conexas" << "," << "Tamanho maior componente conexa" << "," << "Tamanho menor componente conexa" << ","<< "Diametro grafo" << "," << "Diametro aproximado do Grafo";
     
    for(int i = 1; i <= 4; i++){
        
        //primeiro pegamos todas as informações que precisamos para preencher o csv
        GrafoMatriz grafo(to_string(i));
        
        double tamanho = grafo.size();
        
        double avgbfs = grafo.avg_bfs();
                
        double avgdfs = grafo.avg_dfs();
              
        vector<vector<int>> vec1 = grafo.parent_3_vertex(1);
             
        vector<vector<int>> vec2 = grafo.parent_3_vertex(2);
        vector<vector<int>> vec3 = grafo.parent_3_vertex(3);
        vector<vector<int>> components ;
        vector<int> distance(3);
        distance[0] = grafo.distance(10,20);
        
        distance[1] = grafo.distance(10,30);
        
        distance[2] = grafo.distance(20,30);
        
        grafo.connected_components(components);
       
        int diameter = grafo.diameter();
        
        int prox_diameter = grafo.prox_diameter();

        
        myfilemat << "\n" << "Grafo " << i << ","; 
        myfilemat << tamanho << "," << avgbfs << "," ;
        myfilemat << avgdfs << ",";
        myfilemat << vec1[0][0] << " " << vec1[0][1] << " " << vec1[0][2] << "," ;
        myfilemat << vec1[1][0] << " " << vec1[1][1] << " " << vec1[1][2] << "," ;
        myfilemat << vec2[0][0] << " " << vec2[0][1] << " " << vec2[0][2] << "," ;
        myfilemat << vec2[1][0] << " " << vec2[1][1] << " " << vec2[1][2]<< "," ;
        myfilemat << vec3[0][0] << " " << vec3[0][1] << " " << vec3[0][2] << ",";
        myfilemat << vec3[1][0] << " " << vec3[1][1] << " " << vec3[1][2] << "," ;
        myfilemat << distance[0] << "," << distance[1] << "," << distance[2] << "," ;
        myfilemat << components.size() << "," << components[0].size() << "," ;
        myfilemat<< components.back().size() <<"," << diameter << "," << prox_diameter;

        ofstream myfiletext("resultados/Descrição Grafo por Matriz de Adjacencia" + to_string(i) + "txt");


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
    myfilemat.close();

    ofstream myfileadj("resultados/Analise dos dados para representação em Vetor de Adjacencia.csv");
    if (!myfileadj.is_open()) {
    cerr << "Erro ao abrir o arquivo CSV" << endl;
    return;
    }
    cout << "abriu o arquivos" << endl; 
    myfileadj << "," << "Memoria utilizada[MB]" << "," << "Desempenho medio BFS[nanosegundos]" <<"," << "Desempenho medio DFS[nanosegundos]" << "," << "Pai dos vertices 10; 20; 30 BFS[1]" << "," << "Pai dos vertices 10; 20; 30 DFS[1]" << "," << "Pai dos vertices 10; 20; 30 BFS[2]" << "," << "Pai dos vertices 10; 20; 30 DFS[2]" << "," << "Pai dos vertices 10; 20; 30 BFS[3]" << "," << "Pai dos vertices 10; 20; 30 DFS[3]" << "," << "Distancia (10;20)" << "," << "Distancia(10;30)" << "," << "Distancia(20;30)" << "," << "Quantidade de Componentes conexas" << "," << "Tamanho maior componente conexa" << "," << "Tamanho menor componente conexa" << ","<< "Diametro grafo" << "," << "Diametro aproximado do Grafo";
    cout << "ESCREVREU AS COLUNAS TITULO" << endl; 
    for(int i = 1; i <= 6; i++){
        
        //primeiro pegamos todas as informações que precisamos para preencher o csv
        GrafoMatriz grafo(to_string(i));
        
        double tamanho = grafo.size();
        
        double avgbfs = grafo.avg_bfs();
                
        double avgdfs = grafo.avg_dfs();
              
        vector<vector<int>> vec1 = grafo.parent_3_vertex(1);
             
        vector<vector<int>> vec2 = grafo.parent_3_vertex(2);
        vector<vector<int>> vec3 = grafo.parent_3_vertex(3);
        vector<vector<int>> components ;
        vector<int> distance(3);
        distance[0] = grafo.distance(10,20);
        
        distance[1] = grafo.distance(10,30);
        
        distance[2] = grafo.distance(20,30);
        
        grafo.connected_components(components);
       
        int diameter = grafo.diameter();
        
        int prox_diameter = grafo.prox_diameter();

        
        myfileadj << "\n" << "Grafo " << i << ","; 
        myfileadj << tamanho << "," << avgbfs << "," ;
        myfileadj << avgdfs << ",";
        myfileadj << vec1[0][0] << " " << vec1[0][1] << " " << vec1[0][2] << "," ;
        myfileadj << vec1[1][0] << " " << vec1[1][1] << " " << vec1[1][2] << "," ;
        myfileadj << vec2[0][0] << " " << vec2[0][1] << " " << vec2[0][2] << "," ;
        myfileadj << vec2[1][0] << " " << vec2[1][1] << " " << vec2[1][2]<< "," ;
        myfileadj << vec3[0][0] << " " << vec3[0][1] << " " << vec3[0][2] << ",";
        myfileadj << vec3[1][0] << " " << vec3[1][1] << " " << vec3[1][2] << "," ;
        myfileadj << distance[0] << "," << distance[1] << "," << distance[2] << "," ;
        myfileadj << components.size() << "," << components[0].size() << "," ;
        myfileadj<< components.back().size() <<"," << diameter << "," << prox_diameter;

        ofstream myfiletext2("resultados/Descrição Grafo por Vetor de Adjacencia" + to_string(i) + "txt");


        myfiletext2 << "Número de vértices: " << grafo.get_vertex() << endl;
        myfiletext2 << "Número de arestas: " << grafo.edge_count() << endl;
        myfiletext2 << "Grau máximo: " << grafo.max_degree() << endl;
        myfiletext2 << "Grau mínimo: " << grafo.min_degree() << endl;
        myfiletext2 << "Grau médio: " << grafo.average_degree() << endl;
        myfiletext2 << "Mediana dos graus: " << grafo.median_degree() << endl;

        cout << "preencheu arquivo de descricao" << endl;
        for (size_t j = 0; j < components.size(); ++j) {
            myfiletext2 << "Componente: " << (j + 1) << " Tamanho: " << components[j].size() << " Vertices: ";
            for (size_t k = 0; k < components[j].size(); ++k) {
                myfiletext2 << components[j][k];
                if (k < components[j].size() - 1) {
                    myfiletext2 << ", "; // virgula entre os vertices
                }
            }
            myfiletext2 << endl;
        }
        cout << "fechou arquivo de descricao" << endl;
        myfiletext2.close(); 
    
    
    }
    myfileadj.close();

}



int main(){

    write2_csv();

    return 0;

}


