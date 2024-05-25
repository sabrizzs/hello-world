/*
    nome: Sabrina Araujo da Silva
    nUSP: 12566182
*/

#include <iostream>
#include <fstream>   //le arquivo
#include <sstream>   //muda de string para int
#include <vector>    //implementa lista de adjacencia
#include <queue>
#include <cstring>
#include <algorithm> //itera o vetor
using namespace std;

class Grafo{
    private:
        int V;               //numero de vertices
        int E;               //numero de arestas
        int z = 0;           //aux para distancia media
        int d = 0;
        vector<int> *adj;    //lista de adjacencia
        queue<int> conexas;  //tamanho de cada componente

        //busca em profundidade
        void dfs(){
            bool *marked = new bool[V];
            for(int i = 0; i<V; i++){
                marked[i] = false;
            }
            for(int i = 0; i<V; i++){
                queue<int> cc; //componentes conexas
                if(!marked[i]) dfsR(i, marked, &cc);                
                if(!cc.empty())conexas.push(cc.size());          
            }
            cout<< "Numero de componentes conexas: "<< conexas.size() << endl;
            cout<< "Tamanho das componentes "<< endl;
            int k = 1;
            while(!conexas.empty()){
                cout<< "componente "<<k <<": "<<conexas.front() << endl;
                conexas.pop();
                k++;
            }
        }

        void dfsR(int v, bool marked[], queue<int> *cc){
            marked[v] = true;
            cc->push(v);
            for(int i = 0; i<adj[v].size(); i++){
                int w = adj[v].at(i);
                if(!marked[w]) dfsR(w, marked, cc);
            }
        }

        //busca em largura
        void bfs(int i){
            bool *marked = new bool[V];
            int *pred = new int[V];
            int *dist = new int[V];
            int n = 0; //distancia media
            queue<int> fila;
            for(int w=0; w<V; w++){
                marked[w] = false;
                pred[w] = -1;
                dist[w] = 0;
            }
            int distancia = 0;
            if(!marked[i]){
                marked[i] = true;
                pred[i] = i;
                fila.push(i);
                while(!fila.empty()){
                    int u = fila.front();
                    fila.pop();
                    for(int j=0; j<adj[u].size(); j++){
                        int v = adj[u].at(j);
                        if(!marked[v]){
                            marked[v] = true;
                            pred[v] = u;
                            dist[v] = dist[u] + 1;
                            cout<< "Distancia de "<< i << " ate "<< v << ": " << dist[v] << endl;
                            z = z + dist[v];
                            d++;
                            fila.push(v);
                        }
                    }
                }
            }          
        }

    public:
        Grafo(int V, int E){
            this->V = V;
            this->E = E;
            adj = new vector<int>[V];
        }

        //distancia media
        int dm(){
            return z/d;
        }

        //adiciona vertice v na lista de adjacencia de u
        void add(int u, int v){
            if (std::count(adj[u].begin(), adj[u].end(), v)) {
                cout << "Element found";
            }      
            adj[u].push_back(v);
            //adj[v].push_back(u);
        }

        //dado um vertice u calcula a distancia de u ate todos os vertices do grafo
        void distancia(int u){
            bfs(u);
            return;
        }

        //determina o numero de componentes conexas e o tamanho de cada componente
        void compConexas(){
            dfs();
            return;
        }

        int achaFonte(){
            for(int q = 0; q<V; q++){
                bool fonte = false;
                for(int i = 0; i<V; i++){
                    if(std::count(adj[i].begin(), adj[i].end(), q) && q != i){
                        fonte = true;
                    }
                }
                if(fonte == false) return q;
            }
            return -1;
        }

        bool testaCaminho(int seq[], int tam){
            for(int i = 0; i<tam-1; i++){
                bool caminho = false;
                for(int j = 0; j<adj[seq[i]].size(); j++){
                    if(adj[seq[i]].at(j) == seq[i+1]){
                        caminho = true;
                    }
                }
                if(caminho == false) return false;
            }
            return true;
        }
        
};

//converte string para int para auxiliar com as instrucoes
int converte(string str){
    int num; stringstream ss; 
    ss << str;  
    ss >> num;
    return num;
}

Grafo criaGrafo(int *V, int *E){    //le a lista de adjacencia do arquivo
    string line;
    ifstream myfile("grafo.txt");

    //le arquivo
    if(myfile.is_open()){

        getline(myfile, line,' ');  //armazena o numero de vertices e arestas
        *V = converte(line);

        getline(myfile, line); 
        *E = converte(line);

        Grafo gr(*V, *E);

        while(!myfile.eof()){       //le lista de adjacencia
            getline(myfile, line, ' ');
            int u = converte(line);

            getline(myfile, line);
            int v = converte(line);

            gr.add(u,v);
        }
        myfile.close();
        return gr;

    } else cout<< "Nao foi possível abrir o arquivo." << endl;
}

int main(){
    int V; //numero de vertices
    int E; //numero de arestas 

    Grafo grafo = criaGrafo(&V, &E);

    //dado um vertice u calcula a distancia de u ate todos os vertices do grafo
    for(int i = 0; i<V; i++){
        grafo.distancia(i);
    }

    //dado um grafo determina o numero de componentes conexas e o tamanho de cada componente
    grafo.compConexas();
    
    cout<< "Acha fonte: " <<  grafo.achaFonte() << endl;

    int seq[] = {4,6,9};
    cout<< "Testa caminho " << grafo.testaCaminho(seq, 3) << endl;

    cout<< "Distancia media: " << grafo.dm() << endl;

    return 0;
}