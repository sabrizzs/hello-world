/*
    nome: Sabrina Araujo da Silva
    nUSP: 12566182
*/

#include <iostream>
#include <stdio.h>
#include <sstream>  //muda de string para int
#include <vector>   //vetor ordenado
#include <string.h> //separar as palavras do texto
#include <cstring>
using namespace std;

//usar o esquema de passar a funcao como parametro para receber da linha de comando qual implementação devo usar :))

//para usar nas árvores
class No{
    private:
        No *esq;
        No *dir;
        int chave;

    public:
        No(int chave){
            this->chave = chave;
            esq = NULL;
            dir = NULL;
        }

        int retChave(){
            return chave;
        }

        No* retEsq(){
            return esq;
        }

        No* retDir(){
            return dir;
        }

        void attEsq(No *no){
            esq = no;
        }

        void attDir(No *no){
            dir = no;
        }
};

class Item{
    private:
        string key;
        int val;
    
    public:
        Item(string key, int val){
            this->key = key;
            this->val = val;
        }

        string retKey(){
            return key;
        }

        int retVal(){
            return val;
        }

        attVal(int k){
            val = k;
        }
};

/*definir o que e Key
struct Key{
    string key;
};

//definir o que e Item
struct Item{
    int val;
};*/

// devemos ordenar as palarvas em ordem alfabetica e o valor significa quantas vezes a palavra ja apareceu no texto

//vetor dinanmico ordenado
//https://www.geeksforgeeks.org/vector-in-cpp-stl/
class VO{
    private:
        vector<string> keys;
        vector<int> vals;
        vector<Item> ts;
        int size = 0;

    public:
        VO (){
            cout<< "criou um vetor ordenado\n";
        }

        void add(string key, int val){
            Item *novo_item = new Item(key, val);
            ts.push_back(*novo_item);
            cout<< "ADICIONOU\n";
            size++;
            return;
        }

        int value(string key); //quantas vezes a palavra s apareceu no texto ate o momento

        int rank(string key);   //quantas palavras sao menores que s

        string select(int k);   //qual a k-esima chave da tabela

        void imprime(){
            for(int i = 0; i<size; i++){
                Item auxItem = ts[i];
                string auxStr = auxItem.retKey();
                cout<< auxStr << endl;
            }
            return;
        }
};

//https://gist.github.com/marcoscastro/f287ebbe0fa7efe31998
//arvore de busca binária
class ABB{
    public:
        void add(string key, int val);

        int value(string key);

        int rank(string key);

        string select(int k);
};

//treaps
class TR{
    public:
        void add(string key, int val);

        int value(string key);

        int rank(string key);

        string select(int k);
};

//arvores 2-3
class ADT{
    public:
        void add(string key, int val);

        int value(string key);

        int rank(string key);

        string select(int k);
};

//arvores rubro-negras
class ARN{
    public:
        void add(string key, int val);

        int value(string key);

        int rank(string key);

        string select(int k);
};

//converte string para int para auxiliar com as instrucoes
void converte(string str, int *num){
    stringstream ss;  
    ss << str;  
    ss >> *num;
    return;
}

//funcoes para receber instrucoes em cada implementacao
void fVO(int q, string instrucoes[]){
    VO ts;
    int i = 0;
    while(i < q*2){
        string inst = instrucoes[i];
        string var = instrucoes[i+1];

        int num;
        if(inst == "1" || inst == "4"){ //converte a instrucao de string para int
            converte(var, &num);
        }

        if(inst == "1"){
            ts.add("sabrina",1);
            cout<< "adiciona as proximas "<<num<<" palavras do texto a tabela de simbolos\n";
        }
        else if(inst == "2"){
            cout<< "quantas vezes a palavra "<<var<<" apareceu no texto ate o momento - operacao value(s)\n";
        }
        else if(inst ==  "3"){
            cout<< "quantas palavras sao menores que "<<var<<" - operacao rank(s)\n";
        }
        else if(inst == "4"){
            cout<< "qual a "<<num<< " chave da tabela - operacao select(k)\n";
        }
        else cout<< "Instrução não encontrada.\n";
        i = i + 2;
    }
    //ts.imprime();
    return;
}

void fABB(int q, string instrucoes[]){
    ABB ts;
    int i = 0;
    while(i < q*2){
        string inst = instrucoes[i];
        string var = instrucoes[i+1];

        int num;
        if(inst == "1" || inst == "4"){ //converte a instrucao de string para int
            converte(var, &num);
        }

        if(inst == "1"){
            cout<< "adiciona as proximas "<<num<<" palavras do texto a tabela de simbolos\n";
        }
        else if(inst == "2"){
            cout<< "quantas vezes a palavra "<<var<<" apareceu no texto ate o momento - operacao value(s)\n";
        }
        else if(inst ==  "3"){
            cout<< "quantas palavras sao menores que "<<var<<" - operacao rank(s)\n";
        }
        else if(inst == "4"){
            cout<< "qual a "<<num<< " chave da tabela - operacao select(k)\n";
        }
        else cout<< "Instrução não encontrada.\n";
        i = i + 2;
    }
    return;
}

void fTR(int q, string instrucoes[]){
    TR ts;
    int i = 0;
    while(i < q*2){
        string inst = instrucoes[i];
        string var = instrucoes[i+1];

        int num;
        if(inst == "1" || inst == "4"){ //converte a instrucao de string para int
            converte(var, &num);
        }

        if(inst == "1"){
            cout<< "adiciona as proximas "<<num<<" palavras do texto a tabela de simbolos\n";
        }
        else if(inst == "2"){
            cout<< "quantas vezes a palavra "<<var<<" apareceu no texto ate o momento - operacao value(s)\n";
        }
        else if(inst ==  "3"){
            cout<< "quantas palavras sao menores que "<<var<<" - operacao rank(s)\n";
        }
        else if(inst == "4"){
            cout<< "qual a "<<num<< " chave da tabela - operacao select(k)\n";
        }
        else cout<< "Instrução não encontrada.\n";
        i = i + 2;
    }
    return;
}

void fADT(int q, string instrucoes[]){
    ADT ts;
    int i = 0;
    while(i < q*2){
        string inst = instrucoes[i];
        string var = instrucoes[i+1];

        int num;
        if(inst == "1" || inst == "4"){ //converte a instrucao de string para int
            converte(var, &num);
        }

        if(inst == "1"){
            cout<< "adiciona as proximas "<<num<<" palavras do texto a tabela de simbolos\n";
        }
        else if(inst == "2"){
            cout<< "quantas vezes a palavra "<<var<<" apareceu no texto ate o momento - operacao value(s)\n";
        }
        else if(inst ==  "3"){
            cout<< "quantas palavras sao menores que "<<var<<" - operacao rank(s)\n";
        }
        else if(inst == "4"){
            cout<< "qual a "<<num<< " chave da tabela - operacao select(k)\n";
        }
        else cout<< "Instrução não encontrada.\n";
        i = i + 2;
    }
    return;
}

void fARN(int q, string instrucoes[]){
    ARN ts;
    int i = 0;
    while(i < q*2){
        string inst = instrucoes[i];
        string var = instrucoes[i+1];

        int num;
        if(inst == "1" || inst == "4"){ //converte a instrucao de string para int
            converte(var, &num);
        }

        if(inst == "1"){
            cout<< "adiciona as proximas "<<num<<" palavras do texto a tabela de simbolos\n";
        }
        else if(inst == "2"){
            cout<< "quantas vezes a palavra "<<var<<" apareceu no texto ate o momento - operacao value(s)\n";
        }
        else if(inst ==  "3"){
            cout<< "quantas palavras sao menores que "<<var<<" - operacao rank(s)\n";
        }
        else if(inst == "4"){
            cout<< "qual a "<<num<< " chave da tabela - operacao select(k)\n";
        }
        else cout<< "Instrução não encontrada.\n";
        i = i + 2;
    }
    return;
}

//separa as palavras do texto em um vetor
vector<string> arrayChar(string texto, int *size){
    vector<string> palavras;
    int n = texto.length();
    char char_array[n + 1];
    strcpy(char_array, texto.c_str()); //transforma string em um array de char

    char *pch;
    pch = strtok (char_array," ,.-");
    while (pch != NULL){
        printf ("%s\n",pch);
        string str = pch;
        palavras.push_back(str);
        *size = *size + 1;
        pch = strtok(NULL, " ,.-");
    }
    return palavras;
}

int main(){
    string estrutura;   //estrutura a ser testada
    int n;              //número de palavras do texto
    string texto;   
    int q;              //número de operações a serem realizadas
    vector<string> palavras;

    cout<< "Indique a estrutura a ser testada (VO, ABB, TR, A23, ARN):\n";
    cin>> estrutura;

    cout<< "Digite o numero de palavras do texto:\n";
    cin>> n;

    cout<< "Insira o texto:\n"; //dividir as palavras em uma função e mandar pra estrutura?
    cin>> texto;
    
    cout<< "Digite o numero de operacoes a serem realizadas na tabela de simbolos:\n";
    cin>> q;

    //PAREI AQUI, FUNCIONOU, COLOCAR PARA CADA FUNCAO (fVO) RECEBER O VETOR DE PALAVRAS//////////////////////////
    //separa as palavras do texto em um vetor
    int size = 0;
    palavras = arrayChar(texto, &size);
    for(int i = 0; i<size; i++){
        string s = palavras[i];
        cout<< s << endl;
    }

    string instrucoes[q*2];
    int count = 0;
    cout<< "Digite as instrucoes:\n";
    
    //armazena as instrucoes em uma lista
    while(count < q*2){
        string teste; string instrucao;
        cin>> teste >> instrucao;
        instrucoes[count] = teste;
        instrucoes[count+1] = instrucao;
        count = count + 2;
    }

    //cria objeto com a estrutura escolhida e realiza instruções
    if(estrutura == "VO") fVO(q, instrucoes);
    else if(estrutura == "ABB") fABB(q, instrucoes);
    else if(estrutura == "TR") fTR(q, instrucoes);
    else if(estrutura == "A23") fADT(q, instrucoes);
    else if(estrutura == "ARN") fARN(q, instrucoes);

    return 0;
}