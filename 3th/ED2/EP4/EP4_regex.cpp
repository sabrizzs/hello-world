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
                    ant = pilha.top();
                    pilha.pop();
                    G.add(ant, otopo+1);
                    cout << "aa" << endl;
                    G.add(otopo, i);
                    cout << otopo<< " " <<i << endl;
                } else {
                    ant = otopo; /* era '(' */                    
                }
                //ant = otopo;

               
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

bool reconhece(Grafo G, char *pal){
    bool *atingidos = new bool[G.size()];
    for (int i = 0; i<G.size(); i++) atingidos[i] = false;
    G.dfsR(0, atingidos);

    for(int i = 0; i<strlen(pal); i++){

        bool *prox = new bool[G.size()];
        for(int j = 0; j<G.size(); j++) prox[j] = false;
        cout << "criou o bool[]" << endl;

        for(int j = 0; j<G.size(); j++){
            if(atingidos[j]){
                cout << "atingidos eh true" << endl;
                prox[j+1]=true;
            }
        }

        bool *marked = new bool[G.size()];
        cout << "chegou aqui 1" << endl;
        for(int j = 0; j<G.size(); j++) atingidos[j] = false;
        cout << "chegou aqui 2" << endl;
        for(int j = 0; j<G.size(); j++){
            if(prox[j]){
                for(int k = 0; k<G.size(); k++) marked[k] = false;
                cout << "chegou aqui 3" << endl;
                cout << j << endl;
                G.dfsR(j, marked);
                cout << "chegou aqui 4" << endl;
                for(int k = 0; k<G.size(); k++){
                    cout << "chegou aqui 5" << endl;
                    if(marked[k])
                    atingidos[k] = true;
                }
            }
        }
    }
    cout << "chegou aqui 6" << endl;
    return atingidos[G.size()-1];
}

int main(){
    char exp[] = "A*B(C|D)*";
    char palavra[] = "A";

    Grafo grafo(strlen(exp));

    regex(grafo, exp);

    //bool aceita = reconhece(grafo, palavra);

    //cout << aceita << endl;

    return 0;
}