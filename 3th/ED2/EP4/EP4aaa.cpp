/*
    nome: Sabrina Araujo da Silva
    nUSP: 12566182
*/
#include "grafo.h"
#include <iostream>
#include <stack>
#include <string.h> //strlen (dps substituir)
#include <cstring>  //auxiliar para a entrada
using namespace std;

void regex(Grafo G, char *expreg){
    stack<int> pilha;
    for(int i = 0; i<strlen(expreg); i++){
        int ant = i;

        //caso dos conjuntos
        if(expreg[i]=='['){
            while(expreg[i]!=']'){
                i++;
            }
            G.add(i,i+1);
        }

        if(expreg[i]=='(' || expreg[i]=='|'){
            pilha.push(i);
        } else { /*caractere ou ) */
            if(expreg[i] == ')' ){
                int otopo = pilha.top();
                pilha.pop();
                if(expreg[otopo] == '|'){
                    cout<< "eh uma barra em "<< i << endl;
                    stack<int> aux;
                    ant = otopo;
                    while(expreg[ant] != '('){
                        aux.push(ant);
                        G.add(ant, i);
                        ant = pilha.top();
                        pilha.pop();
                    }
                    while(!aux.empty()){
                        otopo = aux.top();
                        G.add(ant, otopo+1);
                        aux.pop();
                    }
                } else {
                    ant = otopo; /* era '(' */                    
                }             
            }

            if(i+1 < strlen(expreg) && expreg[i+1] == '*'){
                G.add(ant, i+1);
                G.add(i+1, ant);
            } else if(i+1 < strlen(expreg) && expreg[i+1] == '+'){
                G.add(ant, i+1);
                G.add(i+1, ant);
            }
        }
        if(expreg[i]=='(' || expreg[i] == '*' || expreg[i] == ')' ){
            G.add(i, i+1);           
        }
    }
    return;
}

int colchete(char *letra, int *j){
    
    bool conjunto = false;
    bool intervalo = false;
    bool complemento = false;

    if(letra[*j+1] == '^'){
        complemento = true;
    }
    
    for(int i = *j+1; i<strlen(letra); i++){
        if(letra[i] == '-'){        
            intervalo = true;
        }
        if(letra[i] == ']') break;
        *j = i+1;
    }

    if(!intervalo) conjunto = true;

    if(conjunto && complemento) cout<< "caso do conjunto e complemento" << endl;
    else if(intervalo && complemento) cout<< "caso do intervalo e complemento" << endl;
    else if(conjunto) cout<< "caso do conjunto" << endl;
    else if(intervalo) cout<< "caso do intervalo" << endl;

    if(conjunto && complemento) return 2;
    else if(conjunto && intervalo) return 3;
    else if(conjunto) return 0;
    else if(intervalo) return 1;

}

bool reconhece(Grafo G, char *pal, char *letra){
    bool *atingidos = new bool[G.size()];
    for (int i = 0; i<G.size(); i++) atingidos[i] = false;

    G.dfsR(0, atingidos);
    //cout<< G.size()<< " gsize " << endl;
    for(int i = 0; i<strlen(pal); i++){

        bool *prox = new bool[G.size()];
        for(int j = 0; j<G.size(); j++) prox[j] = false;
        
        for(int j = 0; j<G.size(); j++){
            //concatenação
            if(atingidos[j] && letra[j] == pal[i]){
                cout << i << " da palavra ( " << pal[i] << " ) tem caminho para " << j << " da regex: " << letra[j] << endl;
                //cout << "j " << j << " caracter: "<< letra[j]<< " i " << i << " palavra: " << pal[i] << endl;
                prox[j+1] = true;   
            //coringa          
            } else if(atingidos[j] && letra[j] == '.'){
                cout << i << " da palavra ( " << pal[i] << " ) tem caminho para " << j << " da regex: " << letra[j] << endl;
                prox[j+1] = true;
            //colchetes
            } else if(atingidos[j] && letra[j] == '['){
                int a = j;
                int caso = colchete(letra, &j);

                //conjunto
                if(caso == 0){
                    for(a; a<j; a++){
                        if(letra[a] == pal[i]) prox[j+1] = true;
                    }
                //intervalo
                } else if(caso == 1){
                
                //conjunto com complemento
                } else if(caso == 2){
                    for(a; a<j; a++){
                        if(letra[a] != pal[i]) prox[j+1] = true;
                    }
                //intervalo com complemento
                } else { //caso == 3

                }
                //conjunto = 0
                //intervalo = 1
                //conjunto com complemento = 2
                //intervalo com complemento = 3
            }
        }

        bool *marked = new bool[G.size()];
        for(int j = 0; j<G.size(); j++) atingidos[j] = false;
        for(int j = 0; j<G.size(); j++){
            if(prox[j]){
                for(int k = 0; k<G.size(); k++) marked[k] = false;
                G.dfsR(j, marked);
                for(int k = 0; k<G.size(); k++){
                    if(marked[k])
                    atingidos[k] = true;
                }
            }
        }
    }

    for(int i = 0; i<G.size(); i++){
        //cout<< atingidos[i] << endl;
    }

    return atingidos[G.size()-1];
}

int main(){
    /*
    char exp[] = "A*B(C|D)*";
    char palavra[] = "AB";
    */

    //https://stackoverflow.com/questions/42022735/warning-unknown-escape-sequence


    char exp[] = "A*B";
    char palavra[] = "A";
    
    Grafo grafo(strlen(exp)+1);
    
    regex(grafo, exp);
    
    for(int i = 0; i<grafo.size(); i++){
        //grafo.bfs(i);
    }

    bool aceita = reconhece(grafo, palavra, exp);

    if(aceita) cout << "S" << endl;
    else cout << "N" << endl;

    return 0;
}