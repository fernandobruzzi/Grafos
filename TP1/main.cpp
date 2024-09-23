#include <fstream> 
#include <iostream> 
#include <string>
#include "GrafoMatriz.h"
#include "GrafoAdj.h"


void write_csv(int i) {

    ostringstream ossmat;
    ossmat << "resultados/Analise_dos_dados_para_representacao_em_Matriz_de_Adjacencia_grafo_" << i << ".txt";
    string filenamemat = ossmat.str();

    ostringstream ossadj;
    ossadj << "resultados/Analise_dos_dados_para_representacao_em_Vetor_de_Adjacencia_grafo_" << i << ".txt";
    string filenameadj = ossadj.str();

    // Abrir arquivos CSV
    ofstream myfilemat(filenamemat);
    ofstream myfileadj(filenameadj);

    if (!myfilemat.is_open() || !myfileadj.is_open()) {
        cerr << "Erro ao abrir os arquivos CSV" <<endl;
        return;
    }

    // Escrever cabeçalhos
    string header = ",Memoria utilizada[MB],Desempenho medio BFS[nanosegundos],Desempenho medio DFS[nanosegundos],Pai dos vertices 10; 20; 30 BFS[1],Pai dos vertices 10; 20; 30 DFS[1],Pai dos vertices 10; 20; 30 BFS[2],Pai dos vertices 10; 20; 30 DFS[2],Pai dos vertices 10; 20; 30 BFS[3],Pai dos vertices 10; 20; 30 DFS[3],Distancia (10;20),Distancia(10;30),Distancia(20;30),Quantidade de Componentes conexas,Tamanho maior componente conexa,Tamanho menor componente conexa,Diametro grafo,Diametro aproximado do Grafo";
    myfilemat << header << endl;
    myfileadj << header << endl;

    // Iterar sobre os grafos
    for (int i = 1; i <= 6; i++) {
        cout << i;
        string grafo_num = to_string(i);

        if(i<= 4){ // a partir do 5 nao roda
        // GrafoMatriz
        GrafoMatriz grafoMatriz(grafo_num);
        vector<vector<int>> vec1M = grafoMatriz.parent_3_vertex(1);
        vector<vector<int>> vec2M = grafoMatriz.parent_3_vertex(2);
        vector<vector<int>> vec3M = grafoMatriz.parent_3_vertex(3);
        vector<vector<int>> componentsM;
        grafoMatriz.connected_components(componentsM);
        cout << "CALCULOU ATRE COMPONETNTES" << endl;

        myfilemat << "\nGrafo " << i << ",";
        myfilemat << grafoMatriz.size() << "," << grafoMatriz.avg_bfs() << "," << grafoMatriz.avg_dfs() << ",";
        myfilemat << vec1M[0][0] << " " << vec1M[0][1] << " " << vec1M[0][2] << ",";
        myfilemat << vec1M[1][0] << " " << vec1M[1][1] << " " << vec1M[1][2] << ",";
        myfilemat << vec2M[0][0] << " " << vec2M[0][1] << " " << vec2M[0][2] << ",";
        myfilemat << vec2M[1][0] << " " << vec2M[1][1] << " " << vec2M[1][2] << ",";
        myfilemat << vec3M[0][0] << " " << vec3M[0][1] << " " << vec3M[0][2] << ",";
        myfilemat << vec3M[1][0] << " " << vec3M[1][1] << " " << vec3M[1][2] << ",";
        myfilemat << grafoMatriz.distance(10, 20) << "," << grafoMatriz.distance(10, 30) << "," << grafoMatriz.distance(20, 30) << ",";
        myfilemat << componentsM.size() << "," << componentsM[0].size() << "," << componentsM.back().size() << ",";
        myfilemat << grafoMatriz.diameter() << "," << grafoMatriz.prox_diameter();
        }
        cout << "BOTOU TUDO EM UMA DAS FILES" << endl;
        // GrafoAdj
        GrafoAdj grafoAdj(grafo_num);
        vector<vector<int>> vec1A = grafoAdj.parent_3_vertex(1);
        vector<vector<int>> vec2A = grafoAdj.parent_3_vertex(2);
        vector<vector<int>> vec3A = grafoAdj.parent_3_vertex(3);
        vector<vector<int>> componentsA;
        grafoAdj.connected_components(componentsA);

        myfileadj << "\nGrafo " << i << ",";
        myfileadj << grafoAdj.size() << "," << grafoAdj.avg_bfs() << "," << grafoAdj.avg_dfs() << ",";
        myfileadj << vec1A[0][0] << " " << vec1A[0][1] << " " << vec1A[0][2] << ",";
        myfileadj << vec1A[1][0] << " " << vec1A[1][1] << " " << vec1A[1][2] << ",";
        myfileadj << vec2A[0][0] << " " << vec2A[0][1] << " " << vec2A[0][2] << ",";
        myfileadj << vec2A[1][0] << " " << vec2A[1][1] << " " << vec2A[1][2] << ",";
        myfileadj << vec3A[0][0] << " " << vec3A[0][1] << " " << vec3A[0][2] << ",";
        myfileadj << vec3A[1][0] << " " << vec3A[1][1] << " " << vec3A[1][2] << ",";
        myfileadj << grafoAdj.distance(10, 20) << "," << grafoAdj.distance(10, 30) << "," << grafoAdj.distance(20, 30) << ",";
        myfileadj << componentsA.size() << "," << componentsA[0].size() << "," << componentsA.back().size() << ",";
        myfileadj << grafoAdj.diameter() << "," << grafoAdj.prox_diameter();
    }

    // Fechar arquivos CSV
    myfilemat.close();
    myfileadj.close();
}

void write_txt(int i) {
    
    ostringstream oss;
    oss << "resultados/Descricao_do_grafo_" << i << ".txt";
    string filename = oss.str();

    // Abrir arquivo de texto
    ofstream myfiletext(filename);

    if (!myfiletext.is_open()) {
        cerr << "Erro ao abrir o arquivo de texto" << endl;
        return;
    }

    // Iterar sobre os grafos
    for (int i = 1; i <= 6; i++) {
        string grafo_num = std::to_string(i);

        // GrafoMatriz (apenas até o grafo 4, devido ao problema de memória)
        if (i <= 4) {
            cout << "Processando GrafoMatriz " << i << endl;
            GrafoMatriz grafoMatriz(grafo_num);
            vector<vector<int>> componentsM;
            grafoMatriz.connected_components(componentsM);

            myfiletext << "GrafoMatriz " << i << ":\n";
            myfiletext << "Número de vértices: " << grafoMatriz.get_vertex() << endl;
            myfiletext << "Número de arestas: " << grafoMatriz.edge_count() << endl;
            myfiletext << "Grau máximo: " << grafoMatriz.max_degree() << endl;
            myfiletext << "Grau mínimo: " << grafoMatriz.min_degree() << endl;
            myfiletext << "Grau médio: " << grafoMatriz.average_degree() << endl;
            myfiletext << "Mediana dos graus: " << grafoMatriz.median_degree() << endl;
            cout << "preencheu arquivo de descricao para GrafoMatriz " << i << endl;
            for (size_t j = 0; j < componentsM.size(); ++j) {
                myfiletext << "Componente: " << (j + 1) << " Tamanho: " << componentsM[j].size() << " Vertices: ";
                for (size_t k = 0; k < componentsM[j].size(); ++k) {
                    myfiletext << componentsM[j][k];
                    if (k < componentsM[j].size() - 1) {
                        myfiletext << ", "; // virgula entre os vertices
                    }
                }
                myfiletext << std::endl;
            }
            myfiletext << std::endl;
        }

        // GrafoAdj (para todos os grafos)
        cout << "Processando GrafoAdj " << i << endl;
        GrafoAdj grafoAdj(grafo_num);
        vector<vector<int>> componentsA;
        grafoAdj.connected_components(componentsA);

        myfiletext << "GrafoAdj " << i << ":\n";
        myfiletext << "Número de vértices: " << grafoAdj.get_vertex() << endl;
        myfiletext << "Número de arestas: " << grafoAdj.edge_count() << endl;
        myfiletext << "Grau máximo: " << grafoAdj.max_degree() << endl;
        myfiletext << "Grau mínimo: " << grafoAdj.min_degree() << endl;
        myfiletext << "Grau médio: " << grafoAdj.average_degree() << endl;
        myfiletext << "Mediana dos graus: " << grafoAdj.median_degree() << endl;
        cout << "preencheu arquivo de descricao para GrafoAdj " << i << endl;
        for (size_t j = 0; j < componentsA.size(); ++j) {
            myfiletext << "Componente: " << (j + 1) << " Tamanho: " << componentsA[j].size() << " Vertices: ";
            for (size_t k = 0; k < componentsA[j].size(); ++k) {
                myfiletext << componentsA[j][k];
                if (k < componentsA[j].size() - 1) {
                    myfiletext << ", "; // virgula entre os vertices
                }
            }
            myfiletext << endl;
        }
        myfiletext << endl;
    }

    // Fechar arquivo de texto
    myfiletext.close();
}



int main() {
    write_csv();
    write_txt();
    return 0;
}



