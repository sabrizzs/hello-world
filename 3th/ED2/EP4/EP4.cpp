/*
    nome: Sabrina Araujo da Silva
    nUSP: 12566182
*/

#include "grafo.h"
#include <iostream>
#include <stack>
#include <string>   //strlen
#include <cstring>  //auxiliar para a entrada
#include <vector>   //guarda palavras
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
                G.add(i+1, ant);
            }
        }
        if(expreg[i]=='(' || expreg[i] == '*' || expreg[i] == ')' || expreg[i] == '+'){
            G.add(i, i+1);           
        }
    }
    return;
}

//quando tem um colchete na expressão regular a função determina o caso que está dentro dos colchetes
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

    if(conjunto && complemento) return 2;
    else if(intervalo && complemento) return 3;
    else if(conjunto) return 0;
    else if(intervalo) return 1;
}

//verifica se a palavra é reconhecida pela expressão regular
bool reconhece(Grafo G, char *pal, char *letra){
    bool *atingidos = new bool[G.size()];
    for (int i = 0; i<G.size(); i++) atingidos[i] = false;

    G.dfsR(0, atingidos);
    for(int i = 0; i<strlen(pal); i++){
        bool *prox = new bool[G.size()];
        for(int j = 0; j<G.size(); j++) prox[j] = false;
        for(int j = 0; j<G.size(); j++){
            //concatenação
            if(atingidos[j] && letra[j] == pal[i]){
                prox[j+1] = true;
            //alternativa
            } else if(atingidos[j] && letra[j] == '\\'){
                if(letra[j+1] == pal[i]){
                    prox[j+2] = true;
                }       
            //coringa          
            } else if(atingidos[j] && letra[j] == '.'){
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
                    char aux = letra[a+1];
                    int inicio, fim;
                    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
                    char alfabetoM[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    char numero[] = "0123456789";

                    if(isdigit(aux)){
                        for(int b = 0; b<=10; b++){
                            if(numero[b] == letra[a+1]) inicio = b;
                            if(numero[b] == letra[a+3]) fim = b;
                        }
                        for(int b = inicio; b<=fim; b++){
                            if(numero[b] == pal[i]) prox[j+1] = true;
                        }
                    } else {
                        for(int b = 0; b<=26; b++){
                            if(alfabeto[b] == letra[a+1] || alfabetoM[b] == letra[a+1]) inicio = b;
                            if(alfabeto[b] == letra[a+3] || alfabetoM[b] == letra[a+3]) fim = b;
                        }
                        for(int b = inicio; b<=fim; b++){
                            if(alfabeto[b] == pal[i] || alfabetoM[b] == pal[i]) prox[j+1] = true;
                        }
                    }
                //conjunto com complemento
                } else if(caso == 2){
                    for(a; a<j; a++){
                        if(letra[a] != pal[i]) prox[j+1] = true;
                    }
                //intervalo com complemento
                } else { //caso == 3
                    
                    char aux = letra[a+1];

                    int inicio, fim;
                    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
                    char alfabetoM[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    char numero[] = "0123456789";

                    if(isdigit(aux)){
                        for(int b = 0; b<=10; b++){
                            if(numero[b] != letra[a+1]) inicio = b;
                            if(numero[b] != letra[a+3]) fim = b;
                        }
                        for(int b = inicio; b<=fim; b++){
                            if(numero[b] != pal[i]) prox[j+1] = true;
                        }
                    } else {
                        for(int b = 0; b<=26; b++){
                            if(alfabeto[b] != letra[a+1] || alfabetoM[b] != letra[a+1]) inicio = b;
                            if(alfabeto[b] != letra[a+3] || alfabetoM[b] != letra[a+3]) fim = b;
                        }
                        for(int b = inicio; b<=fim; b++){
                            if(alfabeto[b] != pal[i] || alfabetoM[b] != pal[i]) prox[j+1] = true;
                        }
                    }
                }
            }
        }

        bool *marked = new bool[G.size()];
        for(int j = 0; j<G.size(); j++) atingidos[j] = false;
        for(int j = 0; j<G.size(); j++){
            if(prox[j]){
                for(int k = 0; k<G.size(); k++) marked[k] = false;
                G.dfsR(j, marked);
                for(int k = 0; k<G.size(); k++){
                    if(marked[k]) atingidos[k] = true;
                }
            }
        }
    }
    return atingidos[G.size()-1];
}



int main(){

    //recebe a expressao regular
    string entrada;
    cin >> entrada;
    int m = entrada.length();
    char exp[m+1];
    strcpy(exp, entrada.c_str());

    //verifica a palavra
    int n;
    cin >> n;                //numero de palavras
    vector<string> palavras; //armazena palavras
    for(int i = 0; i<n; i++){
        string a;
        cin >> a;
        palavras.push_back(a);
    }

    for(int i = 0; i<n; i++){
        int a = palavras[i].length();
        char palavra[a+1];
        strcpy(palavra, palavras[i].c_str());

        Grafo grafo(strlen(exp)+1); //cria grafo
        regex(grafo, exp);          //cria automato

        bool aceita = reconhece(grafo, palavra, exp); //verifica se a palavra é reconhecida
        if(aceita) cout << "S" << endl;
        else cout << "N" << endl;
    }

    return 0;
}