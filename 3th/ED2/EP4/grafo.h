/*
    nome: Sabrina Araujo da Silva
    nUSP: 12566182
*/

#include <vector>
#include <iostream>

using namespace std;

class Grafo{
    private:
        int V;               //numero de vertices
        vector<int> *adj;    //lista de adjacencia

    public:
        Grafo(int V){
            this->V = V;
            adj = new vector<int>[V];
        }

        //adiciona vertice v na lista de adjacencia de u
        void add(int u, int v){     
            adj[u].push_back(v);
        }

        int size(){
            return V;
        }

        void dfsR(int v, bool marked[]){
            marked[v] = true;
            for(int i = 0; i<adj[v].size(); i++){
                if(v < V){
                    int w = adj[v].at(i);
                    if(!marked[w]) dfsR(w, marked);
                }
            }
        }
        
};