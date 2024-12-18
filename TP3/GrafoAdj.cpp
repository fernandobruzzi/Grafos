#include "GrafoAdj.h"

GrafoAdj::GrafoAdj(string num, bool directed){
    
    graph_num = num;
    is_directed = directed;
    string source = "grafos_de_estudo/grafo_rf_.txt";
    source.insert(26, num); //definimos qual o grafo a ser trabalhado

    ifstream myfile; //definimos a variavel para a leitura do arquivo
    myfile.open(source); //abrimos o arquivo que queremos
    
    if(!myfile.is_open()){ //aqui confer  imos se o arquivo conseguiu ser lido
        cerr << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    string linha; //declaramos uma string para guardar cada linha do arquivo de texto

    getline(myfile, linha);//pegamos a primeira linha que é sempre a quantidade de vertices
   
    n = stoi(linha);
    lista_adjacencia.resize(n);
    degree.resize(n,0);

    while(getline(myfile, linha)){
        
        stringstream ss(linha); //separamos a nossa linha
        
        string v, u, c;

        //obtemos cada vértice
        ss >> v;
        ss >> u;
        ss >> c;
        
        set_edge(stoi(v), stoi(u), stoi(c));
        if(!is_directed){set_edge(stoi(u), stoi(v), stoi(c));}; //se o grafo nao for direcionado precisamos apenas tomar o cuidado de ao setar u-v setar v-u
    }

    myfile.close();

}

void GrafoAdj:: find_path_fftask(vector<vector<array<int,2>>>& g_res, int s, int t, vector<array<int,2>>&parent){

    //aqui fazemos uma bfs comum e depois retornamos um caminho de s até t
    queue<int> q;
    parent.assign(n,array<int,2>{-1,-1}); //iniciamos todo mundo inicialmente com o pai sendo -1, que nunca será o indice de nenhum vertice. entao, ao final da execucao do algoritmo se o pai de t ainda for -1 é porque nao temos um caminho entre s-t. alem disso, guardamos qual a capacidade da aresta utilizada
    vector<bool> visited(n,false);
    
    q.push(s);

    while(!q.empty()){

        int u = q.front();
        q.pop();
        visited[u]= true;
        


        for(array<int,2> & e : g_res[u]){
            if((e[1]>0) && (visited[e[0]]==false)){ 
                // só precisamos analisar uma aresta se ela tiver capacidade maior do que 0, pois só assim podemos enviar mais fluxo por ela
                //fazemos isso para evitar passar por um mesmo vertice mais de uma vez
                q.push(e[0]);
                parent[e[0]][0] = u;
                parent[e[0]][1] = e[1];
                if(e[0]==t){ 
                    return; //aqui fazemos a nossa bfs parar na primeira vez que achamos um caminho entre s e t
                }
            }
        }
    }
}


void GrafoAdj::augment_ff(int s, int &f, vector<array<int, 2>>&p, vector<vector<array<int,2>>>&g_res){
    
    int min = numeric_limits<int>::max(); //a partir desse valor vamos fazer as comparacoes para que possamos achar a aresta de menor custo, o GARGALO
    for(array<int,2> & m : p){
        if(m[1] < min){
            min = m[1];
        }
    }
    f+=min;
    
    //agora basta atualizar o fluxo no grafo orginal considerando se temos uma aresta original ou não
    int u = s;
    for(int m = 0; m < p.size(); m++){ 
        
        for(array<int,3> & e : lista_adjacencia[u]){
            if (e[0]==p[m][0]){
                if(e[1]-e[2]==p[m][1]){ //checamos se temos uma aresta original ou nao 
                    e[2] += min;
                }
                else{
                    e[2] -= min;
                }
            }
        }
        u = p[m][0];
    }
}





int GrafoAdj:: Ford_Fulkerson(int s, int t, bool store_in_disk, double& execution_time){

    auto start = chrono::high_resolution_clock::now();

    //primeiro devemos resetar o fluxo de cada aresta para 0 e criar o grafo residual
    s--; t--; //fazemos esse decrescimo por causa da indexacao
    vector<vector<array<int,2>>> g_res(n);
    int f =0;
    for(int i = 0; i < n; i++){
        for(array<int,3> & e : lista_adjacencia[i]){
            e[2] = 0;
            //sabemos que cada aresta do grafo original gera duas novas arestas no grafo residual
            g_res[i].push_back(array<int,2>{e[0],e[1]});
            g_res[e[0]].push_back(array<int, 2>{i,e[2]});
        }
    }

    
    //agora fazemos o while principal e consideramos que a principio existe um caminho
    vector<array<int,2>> parent;
    find_path_fftask(g_res, s, t, parent);
    bool exist_path=1;
    if(parent[t][0]==-1){exist_path=0;}; //se t tiver um pai diferente de -1, entao ele foi atingido na busca e temos um caminho
    
    while(exist_path){

        //montamos o caminho e fazemos a atualizacao do fluxo conforme for necessario
        vector<array<int,2>> p;
        //como montamos o caminho de trás para frente, devido a estrutura parent, o primeiro vértice do caminho é t
        int u = t;
        while(u!=s){
            p.push_back(array<int,2>{u,parent[u][1]});
            u=parent[u][0];
        }
        // é importante notar que aqui o nosso caminho p não possui o vértice s diretamente devido a condição de parada do while
        
        //agora precisamos apenas inverter o caminho
        reverse(p.begin(),p.end());

        //empurramos mais fluxo no grafo original
        augment_ff(s,f,p,g_res);
        //agora precisamos atualizar nosso grafo residual, para fazer isso vamos reconstruir ele do zero
        
        g_res.clear();
        g_res.resize(n);
        for(int i = 0; i < n; i++){
            for(array<int,3> & e : lista_adjacencia[i]){
                g_res[i].push_back(array<int,2>{e[0],e[1]-e[2]});
                g_res[e[0]].push_back(array<int,2>{i,e[2]});
                }
            }
        
        //checamos se ainda temos um caminho no grafo residual entre s e t, se tivermos o nosso algoritmo continua
        find_path_fftask(g_res, s, t, parent);
        if(parent[t][0]==-1){exist_path=0;};

        }

    auto end = chrono::high_resolution_clock::now();
    execution_time = double(chrono::duration_cast<chrono::milliseconds>(end - start).count());

    //agora basta salvar o fluxo obtido nas arestas se o usuário desejar
    if(store_in_disk){
    //definir path onde será salvo o arquivo e com que nome
    ostringstream oss;
    oss << "resultados/Alocacao de fluxo maximo das arestas do grafo " << graph_num << ".txt";

    string filename = oss.str();

    // criar o arquivo de texto
    ofstream myfiletext(filename);

    //importante checar caso o arquivo não tenho sido criado
    if (!myfiletext.is_open()) {
        cerr << "Erro ao abrir o arquivo de texto" << endl;
    }
    myfiletext << "O fluxo maximo encontrado foi " << f << endl;
    myfiletext << "O fluxo em cada aresta e: " << endl;
    for(int i = 0; i < n; i ++){
        for(array<int,3>& e: lista_adjacencia[i]){
            myfiletext << i+1 << " -> " << e[0]+1 << " f(" << i+1 << "," << e[0]+1<<") = " << e[1] <<"/"<< e[2] << endl;
        }
    }
    // fechar o arquivo de texto
    myfiletext.close();
    }

    return f;
}


double GrafoAdj::avg_ff(){
    //obtêm a média de uma execucao de ford fulkerson a partir de 10 amostras
    double average = 0;
    for(int k = 0; k<10; k++){
        double execution_time = 0;
        Ford_Fulkerson(1,2,0,execution_time);
        average+= execution_time;
    }
    average = average/10;
    average = average/1000;//dividimos por 1000 aqui para passar de milissegundos para segundos 

    return average;
}

pair<set<int>,set<int>> GrafoAdj::min_cut(int s, int t){

    //para achar o corte mínimo vamos aplicar o algoritmo de Ford_Fulkerson e depois realizar uma busca no grafo residual a partir de s
    //sabemos que quando a rede estiver passando o fluxo máximo, o conjunto de vértices que define um corte mínimo será a união de dois conjuntos de vértices 
    //no grafo residual, sendo que em cada um deles tem os seus vértices internos atingindo todos os outros que vértices que fazem parte da mesma componenete
    double time;
    Ford_Fulkerson(s,t,false,time);

    //agora que já temos o fluxo máximo passando, podemos montar nosso grafo residual e realizar a busca
    vector<vector<array<int,2>>> g_res(n);
    for(int i = 0; i < n; i++){
        for(array<int,3> & e : lista_adjacencia[i]){
            //sabemos que cada aresta do grafo original gera duas novas arestas no grafo residual
            g_res[i].push_back(array<int,2>{e[0],e[1]-e[2]});
            g_res[e[0]].push_back(array<int, 2>{i,e[2]});
        }
    }

    s--; //para a execucao da busca
    vector<bool> visited(n,false);
    queue<int> qu;

    visited[s]=true;
    qu.push(s);
    int u;

    while(!qu.empty()){
        
        u = qu.front(); 
        qu.pop();

        for(array<int,2> & e: g_res[u]){
            if((e[1]>0)&&(visited[e[0]]==false)){
                qu.push(e[0]);
                visited[e[0]]=true;
            }
        }
    }

    //agora, partindo da premissa mencionada anteriormente, podemos criar os nossos conjuntos A e B
    pair<set<int>,set<int>> set_A_set_B;
    for(int i = 0; i < n; i++){
        if(visited[i]){
            set_A_set_B.first.insert(i+1);//inserimos o elemento com seu indice correto para o usuário
        }
        else{
            set_A_set_B.second.insert(i+1);
        }
    }

    return set_A_set_B;
}