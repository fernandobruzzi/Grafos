#include "GrafoMatriz.h"
#include "GrafoAdj.h"

using namespace std;

// void write_csv(int i) {

//     //definir path onde serão salvos os arquivos e com que nome
//     ostringstream ossmat;
//     ossmat << "resultados/Analise_dos_dados_para_representacao_em_Matriz_de_Adjacencia_grafo_" << i << ".csv";
//     string filenamemat = ossmat.str();

//     ostringstream ossadj;
//     ossadj << "resultados/Analise_dos_dados_para_representacao_em_Vetor_de_Adjacencia_grafo_" << i << ".csv";
//     string filenameadj = ossadj.str();

//     // criar os arquivos CSV
//     ofstream myfilemat(filenamemat);
//     ofstream myfileadj(filenameadj);

//     //importante checar caso os arquivos não tenho sido criados
//     if (!myfilemat.is_open() || !myfileadj.is_open()) {
//         cerr << "Erro ao abrir os arquivos CSV" <<endl;
//         return;
//     }

//     // escrever cabeçalhos
//     string header = ",Memoria utilizada[MB],Desempenho medio BFS[nanosegundos],Desempenho medio DFS[nanosegundos],Pai dos vertices 10; 20; 30 BFS[1],Pai dos vertices 10; 20; 30 DFS[1],Pai dos vertices 10; 20; 30 BFS[2],Pai dos vertices 10; 20; 30 DFS[2],Pai dos vertices 10; 20; 30 BFS[3],Pai dos vertices 10; 20; 30 DFS[3],Distancia (10;20),Distancia(10;30),Distancia(20;30),Quantidade de Componentes conexas,Tamanho maior componente conexa,Tamanho menor componente conexa,Diametro grafo,Diametro aproximado do Grafo";
//     myfilemat << header << endl;
//     myfileadj << header << endl;


//     string grafo_num = to_string(i);

        
//     // GrafoMatriz
//     GrafoMatriz grafoMatriz(grafo_num);
//     vector<vector<int>> vec1M = grafoMatriz.parent_3_vertex(1);
//     vector<vector<int>> vec2M = grafoMatriz.parent_3_vertex(2);
//     vector<vector<int>> vec3M = grafoMatriz.parent_3_vertex(3);
//     vector<vector<int>> componentsM;
//     grafoMatriz.connected_components(componentsM);
//     cout << "CALCULOU ATRE COMPONETNTES" << endl; 

//     myfilemat << "\nGrafo " << i << ",";
//     myfilemat << grafoMatriz.size() << "," << grafoMatriz.avg_bfs() << "," << grafoMatriz.avg_dfs() << ",";
//     myfilemat << vec1M[0][0] << " " << vec1M[0][1] << " " << vec1M[0][2] << ",";
//     myfilemat << vec1M[1][0] << " " << vec1M[1][1] << " " << vec1M[1][2] << ",";
//     myfilemat << vec2M[0][0] << " " << vec2M[0][1] << " " << vec2M[0][2] << ",";
//     myfilemat << vec2M[1][0] << " " << vec2M[1][1] << " " << vec2M[1][2] << ",";
//     myfilemat << vec3M[0][0] << " " << vec3M[0][1] << " " << vec3M[0][2] << ",";
//     myfilemat << vec3M[1][0] << " " << vec3M[1][1] << " " << vec3M[1][2] << ",";
//     myfilemat << grafoMatriz.distance(10, 20) << "," << grafoMatriz.distance(10, 30) << "," << grafoMatriz.distance(20, 30) << ",";
//     myfilemat << componentsM.size() << "," << componentsM[0].size() << "," << componentsM.back().size() << ",";
//     myfilemat << grafoMatriz.diameter() << "," << grafoMatriz.prox_diameter();
//     // myfileadj << "X" << "," << grafoMatriz.prox_diameter(); caso calcular o diametro nao seja viavel
        
//     // GrafoAdj
//     GrafoAdj grafoAdj(grafo_num);
//     vector<vector<int>> vec1A = grafoAdj.parent_3_vertex(1);
//     vector<vector<int>> vec2A = grafoAdj.parent_3_vertex(2);
//     vector<vector<int>> vec3A = grafoAdj.parent_3_vertex(3);
//     vector<vector<int>> componentsA;
//     grafoAdj.connected_components(componentsA);

//     myfileadj << "\nGrafo " << i << ",";
//     myfileadj << grafoAdj.size() << "," << grafoAdj.avg_bfs() << "," << grafoAdj.avg_dfs() << ",";
//     myfileadj << vec1A[0][0] << " " << vec1A[0][1] << " " << vec1A[0][2] << ",";
//     myfileadj << vec1A[1][0] << " " << vec1A[1][1] << " " << vec1A[1][2] << ",";
//     myfileadj << vec2A[0][0] << " " << vec2A[0][1] << " " << vec2A[0][2] << ",";
//     myfileadj << vec2A[1][0] << " " << vec2A[1][1] << " " << vec2A[1][2] << ",";
//     myfileadj << vec3A[0][0] << " " << vec3A[0][1] << " " << vec3A[0][2] << ",";
//     myfileadj << vec3A[1][0] << " " << vec3A[1][1] << " " << vec3A[1][2] << ",";
//     myfileadj << grafoAdj.distance(10, 20) << "," << grafoAdj.distance(10, 30) << "," << grafoAdj.distance(20, 30) << ",";
//     myfileadj << componentsA.size() << "," << componentsA[0].size() << "," << componentsA.back().size() << ",";
//     myfileadj << grafoAdj.diameter() << "," << grafoAdj.prox_diameter();
//     // myfileadj << "X" << "," << grafoAdj.prox_diameter(); caso calcular o diametro nao seja viavel


//     // fechar os arquivos CSV
//     myfilemat.close();
//     myfileadj.close();
// }

// void write_txt(int i) {
    
//     //definir path onde será salvo o arquivo e com que nome
//     ostringstream oss;
//     oss << "resultados/Descricao_do_grafo_" << i << ".txt";
//     string filename = oss.str();

//     // criar o arquivo de texto
//     ofstream myfiletext(filename);

//     //importante checar caso os arquivos não tenho sido criados
//     if (!myfiletext.is_open()) {
//         cerr << "Erro ao abrir o arquivo de texto" << endl;
//         return;
//     }

//     string grafo_num = to_string(i);

//     // GrafoMatriz 
        
//     cout << "Processando GrafoMatriz " << i << endl;
//     GrafoMatriz grafoMatriz(grafo_num);
//     vector<vector<int>> componentsM;
//     grafoMatriz.connected_components(componentsM);

//     myfiletext << "GrafoMatriz " << i << ":\n";
//     myfiletext << "Número de vértices: " << grafoMatriz.get_vertex() << endl;
//     myfiletext << "Número de arestas: " << grafoMatriz.edge_count() << endl;
//     myfiletext << "Grau máximo: " << grafoMatriz.max_degree() << endl;
//     myfiletext << "Grau mínimo: " << grafoMatriz.min_degree() << endl;
//     myfiletext << "Grau médio: " << grafoMatriz.average_degree() << endl;
//     myfiletext << "Mediana dos graus: " << grafoMatriz.median_degree() << endl;
//     for (size_t j = 0; j < componentsM.size(); ++j) {
//         myfiletext << "Componente: " << (j + 1) << " Tamanho: " << componentsM[j].size() << " Vertices: ";
//         for (size_t k = 0; k < componentsM[j].size(); ++k) {
//             myfiletext << componentsM[j][k];
//             if (k < componentsM[j].size() - 1) {
//                 myfiletext << ", "; // virgula entre os vertices
//                 }
//             }
//             myfiletext << std::endl;
//         }
//         myfiletext << std::endl;
    

//     // GrafoAdj (para todos os grafos)
//     GrafoAdj grafoAdj(grafo_num);
//     vector<vector<int>> componentsA;
//     grafoAdj.connected_components(componentsA);

//     myfiletext << "GrafoAdj " << i << ":\n";
//     myfiletext << "Número de vértices: " << grafoAdj.get_vertex() << endl;
//     myfiletext << "Número de arestas: " << grafoAdj.edge_count() << endl;
//     myfiletext << "Grau máximo: " << grafoAdj.max_degree() << endl;
//     myfiletext << "Grau mínimo: " << grafoAdj.min_degree() << endl;
//     myfiletext << "Grau médio: " << grafoAdj.average_degree() << endl;
//     myfiletext << "Mediana dos graus: " << grafoAdj.median_degree() << endl;
//     cout << "preencheu arquivo de descricao para GrafoAdj " << i << endl;
//     for (size_t j = 0; j < componentsA.size(); ++j) {
//         myfiletext << "Componente: " << (j + 1) << " Tamanho: " << componentsA[j].size() << " Vertices: ";
//         for (size_t k = 0; k < componentsA[j].size(); ++k) {
//             myfiletext << componentsA[j][k];
//             if (k < componentsA[j].size() - 1) {
//                 myfiletext << ", "; // virgula entre os vertices
//             }
//         }
//         myfiletext << endl;
//     }
//     myfiletext << endl;
    

//     // fechar os arquivos de texto
//     myfiletext.close();
// }



int main() {
    
    GrafoAdj g("2");


    vector<float> cost1, cost2;
    vector<int> parent1, parent2;

    double d;
    
    g.Djikstra_vec(10,cost1,parent1);
   
    // cout << cost1[19];
    cout << g.exist_edge(94, 993) << endl;
    // cout << g.exist_edge(9500,6534) << endl;
    // cout << g.exist_edge(6534,9492) << endl;
    // cout << g.exist_edge(9492,4780) << endl;
    // cout << g.exist_edge(4780,7300) << endl;
    // cout << g.exist_edge(7300,5294) << endl;
    // cout << g.exist_edge(5294,4290) << endl;
    // cout << g.exist_edge(4290,3) << endl;
    
    

    return 0;
}



