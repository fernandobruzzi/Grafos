#include "GrafoAdj.h"

using namespace std;


void results(){

    //definir path onde será salvo os arquivos 
    ostringstream ossresults;
    ossresults << "resultados/Analise_dos_grafos_" << "5 e 6" << ".csv";
    string filename = ossresults.str();

    // criar o arquivo CSV
    ofstream myfileresult(filename);

    //importante checar caso o arquivo não tenho sido criado
    if (!myfileresult.is_open()) {
        cerr << "Erro ao abrir os arquivos CSV" <<endl;
        return;
    }

    // escrever cabeçalhos
    string header = "Grafo,Fluxo maximo 1->2, Tempo medio Ford Fulkerson [segundos]";
    myfileresult << header << endl;

    double time =0 ;
    //coletamos os dados para o csv aqui
    for(int i = 5; i <=6 ; i++){
        GrafoAdj g(to_string(i),true);
        myfileresult << "Grafo " << to_string(i) << "," << g.Ford_Fulkerson(1,2,false,time) <<"," << g.avg_ff() << endl;
    }
    myfileresult.close();

    //em um loop separado coletamos os dados da alocacao do fluxo para cada grafo
    for(int i = 1; i <=6 ; i++){
        GrafoAdj g(to_string(i),true);
        g.Ford_Fulkerson(1,2,true,time);
    }

}



int main() {
    
    results();

    // GrafoAdj g("12", true);

    // pair<set<int>,set<int>> set_A_set_B =g.min_cut(1,7);
    // cout << endl <<  "Conjunto A : ";
    // for(set<int>::iterator itr=set_A_set_B.first.begin(); itr != set_A_set_B.first.end();itr++){
    //     cout << *itr << " ";
    // }
    // cout << endl;
    // cout << "Conjunto B : ";
    // for(set<int>::iterator itr=set_A_set_B.second.begin(); itr != set_A_set_B.second.end();itr++){
    //     cout << *itr << " ";
    // }
    // cout << endl;
}
