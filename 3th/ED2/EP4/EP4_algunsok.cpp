/*
    nome: Sabrina Araujo da Silva
    nUSP: 12566182
*/
#include "grafo.h"
#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

void regex(Grafo G, char *expreg){
    stack<int> pilha;
    for(int i = 0; i<strlen(expreg); i++){
        int ant = i;
        if(expreg[i]=='(' || expreg[i]=='|'){
            pilha.push(i);
        } else { /*caractere ou ) */
            if(expreg[i] == ')' ){
                int otopo = pilha.top();
                pilha.pop();
                if(expreg[otopo] == '|'){
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
            }
        }
        if(expreg[i]=='(' || expreg[i] == '*' || expreg[i] == ')' ){
            G.add(i, i+1);           
        }
    }
    return;
}

bool reconhece(Grafo G, char *pal, char *letra){
    bool *atingidos = new bool[G.size()];
    for (int i = 0; i<G.size(); i++) atingidos[i] = false;
    G.dfsR(0, atingidos);

    for(int i = 0; i<strlen(pal); i++){

        bool *prox = new bool[G.size()];
        for(int j = 0; j<G.size(); j++) prox[j] = false;

        for(int j = 0; j<G.size(); j++){
            
            if(atingidos[j] && letra[j] == pal[i]){
                cout << "j " << j << " caracter: "<< letra[j]<< " i " << i << " palavra: " << pal[i] << endl;
                prox[j+1]=true;                
            } else if(atingidos[j] && letra[j] == '.'){
                cout << "j " << j << " caracter: "<< letra[j]<< " i " << i << " palavra: " << pal[i] << endl;
                prox[j+1]=true; 
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
    return atingidos[G.size()-1];
}

int main(){
    /*
    char exp[] = "A*B(C|D)*";
    char palavra[] = "AB";
    */

    //https://stackoverflow.com/questions/42022735/warning-unknown-escape-sequence

    char exp[] = "(A*CG|A*TA|AAG*T)*";
    char palavra[] = "CAAGA";

    Grafo grafo(strlen(exp));

    regex(grafo, exp);

    bool aceita = reconhece(grafo, palavra, exp);

    if(aceita) cout << "S" << endl;
    else cout << "N" << endl;

    for(int i = 0; i<grafo.size(); i++){
        grafo.bfs(i);
    }

    return 0;
}