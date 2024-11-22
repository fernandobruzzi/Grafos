#include "GrafoMatriz.h"
#include "GrafoAdj.h"

using namespace std;

void distancia_redes_de_colaboração(vector<pair<vector<int>,float>>&path_dist){
    
    vector<pair<string, int>> pesquisadores_e_vertices = {
        {"Edsger W. Dijkstra", -1},
        {"Alan M. Turing", -1},
        {"J. B. Kruskal", -1},
        {"Jon M. Kleinberg", -1},
        {"Éva Tardos", -1},
        {"Daniel R. Figueiredo", -1}
    };

    string source = "grafos_de_estudo/rede_colaboracao_vertices.txt";

    ifstream myfile; //definimos a variavel para a leitura do arquivo
    myfile.open(source); //abrimos o arquivo que queremos
    
    if(!myfile.is_open()){ //aqui confer  imos se o arquivo conseguiu ser lido
        cerr << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    string linha; //declaramos uma string para guardar cada linha do arquivo de texto

    getline(myfile, linha);//pegamos a primeira linha que é sempre a quantidade de vertices
    
    while(getline(myfile, linha)){
        
        stringstream ss(linha); //separamos a nossa linha
        
        string vertex_num, name; 

        getline(ss, vertex_num, ','); //pegamos o numero
        getline(ss, name); //pegamos o nome

        for(pair<string,int>&it:pesquisadores_e_vertices){

            if(name == it.first){
                it.second = stoi(vertex_num);
            }
        }
    }
    myfile.close();


    //agora que já temos os nosso vertices de interesse podemos carregar o grafo e realizar a busca nele
    //para facilitar a leitura do grafo, o seu nome de "rede_colaboração" foi alterado para grafo_W_10  
    GrafoAdj graph("10");
    path_dist.resize(5); //onde cada posicao se refere a distancia e o caminho entre Dijkstra e Alan Turing[0], Dijkstra e Kruskal[1],...,Dijkstra e Daniel[4]

    for(int i = 0; i < 5; i++){
        graph.path_i_to_j_and_cost(pesquisadores_e_vertices[0].second,pesquisadores_e_vertices[i+1].second,path_dist[i].first, path_dist[i].second);
        // cout << pesquisadores_e_vertices[0].first << " " << pesquisadores_e_vertices[i+1].first << " " << path_dist[i].second << endl;
    }
}
    
void find_names(vector<int>vertex_seq, vector<string>&names){
  	//funcao que transforma uma sequencia de vertices em uma sequencia de nomes
    names.resize(vertex_seq.size());
    
    string source = "grafos_de_estudo/rede_colaboracao_vertices.txt";

    ifstream myfile; //definimos a variavel para a leitura do arquivo
    myfile.open(source); //abrimos o arquivo que queremos
    
    if(!myfile.is_open()){ //aqui confer  imos se o arquivo conseguiu ser lido
        cerr << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    string linha; //declaramos uma string para guardar cada linha do arquivo de texto

    getline(myfile, linha);//pegamos a primeira linha que é sempre a quantidade de vertices
    
    while(getline(myfile, linha)){
        
        stringstream ss(linha); //separamos a nossa linha
        
        string vertex_num, name; 

        getline(ss, vertex_num, ','); //pegamos o numero
        getline(ss, name); //pegamos o nome

        for(int j = 0; j < vertex_seq.size(); j++){
            //procuramos no nosso vetor de vertices quem tem o nome correspondente 
            if(stoi(vertex_num) == vertex_seq[j]){
                names[j] = name;
            }
        }
    }
    myfile.close();

}

void write_csv_graph(int i) {

    //definir path onde serão salvos os arquivos e com que nome
    ostringstream ossmat;
    ossmat << "resultados/Analise_dos_dados_para_representacao_em_Matriz_de_Adjacencia_grafo_" << i << ".csv";
    string filenamemat = ossmat.str();

    ostringstream ossadj;
    ossadj << "resultados/Analise_dos_dados_para_representacao_em_Vetor_de_Adjacencia_grafo_" << i << ".csv";
    string filenameadj = ossadj.str();

    // criar os arquivos CSV
    ofstream myfilemat(filenamemat);
    ofstream myfileadj(filenameadj);

    //importante checar caso os arquivos não tenho sido criados
    if (!myfilemat.is_open() || !myfileadj.is_open()) {
        cerr << "Erro ao abrir os arquivos CSV" <<endl;
        return;
    }

    if(!myfileadj.is_open()){
        cerr << "Erro ao abrir os arquivos CSV" << endl;
        return;
    }

    // escrever cabeçalhos
    string header = ",Distancia 10-20,Caminho 10-20,Distancia 10-30,Caminho 10-30,Distancia 10-40,Caminho 10-40,Distancia 10-50,Caminho 10-50,Distancia 10-60,Caminho 10-60, Tempo medio Dijkstra heap[nanosegundos], Tempo medio Dikstra sem heap[nanosegundos]";
    // myfilemat << header << endl;
    myfileadj << header << endl;


    string grafo_num = to_string(i);
        
    GrafoMatriz grafomatriz(grafo_num);
    myfilemat << "Grafo " << i << ",";
    
    //vetor e variavel utilizados para calcular e armazenar o custo respectivamente
    vector<int> path; 
    float cost;
    grafomatriz.path_i_to_j_and_cost(10,20, path, cost);
    
    myfilemat << cost << ",";
    for(int&p:path){
        myfilemat << p << " ";
    }
    myfilemat << ",";
    path.clear();
    
    
    grafomatriz.path_i_to_j_and_cost(10,30, path, cost);
    myfilemat << cost << ",";
    for(int&p:path){
        myfilemat << p << " ";
    }
    myfilemat << ",";
    path.clear();

    grafomatriz.path_i_to_j_and_cost(10,40, path, cost);
    myfilemat << cost << ",";
    for(int&p:path){
        myfilemat << p << " ";
    }
    myfilemat << ",";
    path.clear();

    grafomatriz.path_i_to_j_and_cost(10,50, path, cost);
    myfilemat << cost << ",";
    for(int&p:path){
        myfilemat << p << " ";
    }
    myfilemat <<  ",";
    path.clear();

    grafomatriz.path_i_to_j_and_cost(10,60, path, cost);
    myfilemat << cost << ",";
    for(int&p:path){
        myfilemat << p << " ";
    }
    myfilemat << ",";
    path.clear();

    myfilemat << grafomatriz.avg_dijkstra_heap() << "," << grafomatriz.avg_dijkstra_vec();


    //agora fazemos o mesmo para a representacao em vetor de adjacencia

    GrafoAdj grafoadj(grafo_num);
    myfileadj << "\nGrafo " << i << ",";
    
    //vetor e variavel utilizados para calcular e armazenar o custo respectivamente
    grafoadj.path_i_to_j_and_cost(10,20, path, cost);
    myfileadj << cost << ",";
    for(int&p:path){
        myfileadj << p << " ";
    }
    myfileadj <<  ",";
    path.clear();
    
    grafoadj.path_i_to_j_and_cost(10,30, path, cost);
    myfileadj << cost << ",";
    for(int&p:path){
        myfileadj << p << " ";
    }
    myfileadj << ",";
    path.clear();

    grafoadj.path_i_to_j_and_cost(10,40, path, cost);
    myfileadj << cost << ",";
    for(int&p:path){
        myfileadj << p << " ";
    }
    myfileadj <<  ",";
    path.clear();

    grafoadj.path_i_to_j_and_cost(10,50, path, cost);
    myfileadj << cost << ",";
    for(int&p:path){
        myfileadj << p << " ";
    }
    myfileadj << ",";
    path.clear();
    
    
    path.clear();
    grafoadj.path_i_to_j_and_cost(10,60, path, cost);
    myfileadj << cost << ",";
    for(int&p:path){
        myfileadj << p << " ";
    }
    myfileadj << ",";
    path.clear();


    myfileadj << grafoadj.avg_dijkstra_heap() << "," << grafoadj.avg_dijkstra_vec();
    myfileadj << grafoadj.avg_dijkstra_heap() << "," << "infinito";

    // fechar os arquivos CSV
    myfilemat.close();
    myfileadj.close();
}

void write_csv_rede_colaboração(){

    vector<pair<vector<int>,float>> path_dist;
    vector<string> names;
    distancia_redes_de_colaboração(path_dist);
    //definir path onde serão salvos os arquivos e com que nome
    ostringstream ossrede;
    ossrede << "resultados/Analise_dos_dados_rede_de_colaboracao.csv";
    string filenamerede = ossrede.str();

    // criar os arquivos CSV
    ofstream myfilerede(filenamerede);

    //importante checar caso os arquivos não tenho sido criados
    if (!myfilerede.is_open()) {
        cerr << "Erro ao abrir os arquivos CSV" <<endl;
        return;
    }

    // escrever cabeçalhos
    string header = ",Distancia ate Edsger W. Dijkstra, Caminho ate Edsger W. Dijkstra(em vertices como numeros), Caminho ate Edsger W. Dijkstra(em vertices como nome)";
    myfilerede << header << endl;
    
    myfilerede << "Alan M. Turing" << "," << path_dist[0].second << ",";
    for(int&i:path_dist[0].first){
        myfilerede << i << " ";
    }
    myfilerede << ",";
    find_names(path_dist[0].first, names);
    for(string&n:names){
        myfilerede << n << " ";
    }

    
    myfilerede << "\n J. B. Kruskal" << "," << path_dist[1].second << ",";
    for(int&i:path_dist[1].first){
        myfilerede << i << " ";
    }
    myfilerede << ",";
    find_names(path_dist[1].first, names);
    for(string&n:names){
        myfilerede << n << " ";
    }

    myfilerede << "\n Jon M.Kleinberg" << "," << path_dist[2].second << ",";
    for(int&i:path_dist[2].first){
        myfilerede << i << " ";
    }
    myfilerede << ",";
    find_names(path_dist[2].first, names);
    for(string&n:names){
        myfilerede << n << " ";
    }

    myfilerede << "\n Eva Tardos" << "," << path_dist[3].second << ",";
    for(int&i:path_dist[3].first){
        myfilerede << i << " ";
    }
    myfilerede << ",";
    find_names(path_dist[3].first, names);
    for(string&n:names){
        myfilerede << n << " ";
    }

    myfilerede << "\n Daniel R. Figueiredo" << "," << path_dist[4].second << ",";
    for(int&i:path_dist[4].first){
        myfilerede << i << " ";
    }
    myfilerede << ",";
    find_names(path_dist[4].first, names);
    for(string&n:names){
        myfilerede << n << " ";
    }

    myfilerede.close();

}

int main() {
    
    write_csv_rede_colaboração();
    for(int i =1; i <=5 ; i++){
        write_csv_graph(i);
    }



    return 0;
}



