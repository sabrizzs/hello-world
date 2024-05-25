/*
    nome: Sabrina Araujo da Silva
    nUSP: 12566182
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>   //le arquivo
#include <sstream>
#include <algorithm> //itera o vetor
using namespace std;

//adiciona adjacencia sem repetir
bool adiciona(vector<string> *a, int u, int j){
    if(u > j){
        int aux = j;
        j = u; u = aux;
    }
    stringstream stream;
    stream<< u << " " << j;
    string adj = stream.str();

    if (!std::count(a->begin(), a->end(), adj)) {
        a->push_back(adj);
        return true;
    } else return false;
}

//cria uma entrada para representar um grafo
void simples(){
    vector<string> adj;
    unsigned seed = time(0); 
    srand(seed);
    int V; int E;

    V = rand()%20 + 1;       //numero de vertices aleatorio entre 1 e 20

    int max = 0;             //max de arestas do grafo
    for(int i = V-1; i>0; i--){
        max+= i;
    }

    if(V == 1) E = 0;
    else E = rand()%max + 1; //numero de arestas aleatorio entre 1 e max

    cout<< V << ' ' << E << "\n";

    for(int i = 0; i<E; i++){
        int u = rand()%V;
        int v = u;
        while(u == v){
            v = rand()%V;
        }
        if(!adiciona(&adj, u, v)) i--;
    }
    for(int i = 0; i<adj.size(); i++){
        cout<< adj[i] << endl;
    }
    return;
}

void palavras(int n){
    string line;
    ifstream myfile("palavras.txt");
    vector<string> palavras;
    vector<string> adj;

    //le arquivo
    if(myfile.is_open()){

        while(!myfile.eof()){  //le lista de palavras
            getline(myfile, line);
            palavras.push_back(line);
        }
        myfile.close();

    } else cout<< "Nao foi possível abrir o arquivo." << endl;

    for(int i = 0; i<palavras.size(); i++){
        string palavra = palavras[i];
        for(int j = 0; j<palavras.size(); j++){
            if(i != j){
                int dif = 0;
                for(int w = 0; w<n; w++){
                    if(palavras[i].substr(w,1) != palavras[j].substr(w,1)) dif++;
                }
                if(dif <= 1) adiciona(&adj, i, j);
            }
        }
    }
    cout<< palavras.size() << " " << adj.size() << endl;  
    for(int i = 0; i<adj.size(); i++){
        cout<< adj[i] << endl;
    }
}

void erdosReniy(int V, double p){
    vector<string> adj;
    unsigned seed = time(0);
    srand(seed);
    int x = rand()%100 + 1;

    for(int i = 0; i<V; i++){
        for(int j = 0; j<V; j++){
            if(i != j){
                double x = rand()%100 + 1;
                if(x/100 <= p) adiciona(&adj, i, j);
            }
        }  
    }
    cout<< V << " " << adj.size() << endl;
    for(int i = 0; i<adj.size(); i++){
        cout<< adj[i] << endl;
    }
    return;
}

int main(){
    //gerador de uma lista de adjacencia simples
    //simples();

    //gerador de uma lista de adjacencia a partir de uma lista de palavras (palavras.txt)
    //int n = 4;    //numero de letras de cada palavra
    //palavras(n);
    
    //gerador de uma lista de adjacencia a partir de uma probabilidade p
    //int V = 50;      //numero de vertices
    //double p = 0.1;  //probabilidade
    //erdosReniy(V, p);

    return 0;
}
