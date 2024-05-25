/*
    nome: Sabrina Araujo da Silva
    nUSP: 12566182
*/

#include <iostream>
#include <stdio.h>
#include <sstream>  //muda de string para int
#include <vector>   //vetor ordenado
#include <string.h> //separar as palavras do texto
#include <cstring> //separar palavras em tokens
#include <queue> //para testar RB, depois tirar!!
using namespace std;

const int trie_size = 52; //numero de filhos de um no na trie
enum COLOR {RED, BLACK}; //cores dos nos na arvore rubro negra

//item para vetor ordenado
class Item{
    private:
        string key;
        int val;
    
    public:
        Item(string key, int val){
            this->key = key;
            this->val = val;
        }

        string chave(){
            return key;
        }

        int valor(){
            return val;
        }

        attChave(string k){
            key = k;
        }

        attVal(int v){
            val = v;
        }
};

//no para arvore binaria
class No{
    private:
        No *esquerdo;
        No *direito;
        string key;
        int val;

    public:
        No(string key, int val){
            this->key = key;
            this->val = val;
            esquerdo = NULL;
            direito = NULL;
        }

        string chave(){
            return key;
        }

        int valor(){
            return val;
        }

        attVal(int v){
            val = v;
        }

        No* esq(){
            return esquerdo;
        }

        No* dir(){
            return direito;
        }

        attEsq(No *no){
            esquerdo = no;
        }

        attDir(No *no){
            direito = no;
        }
};

//no da arvore rubro negra
class NoRB{
    public:
        string key;
        int val;
        COLOR cor;
        NoRB *esquerdo;
        NoRB *direito;
        NoRB *pai;

        NoRB(string key, int val){
            this->key = key;
            this->val = val;
            esquerdo = NULL;
            direito = NULL;
            pai = NULL;
            cor = RED;
        }

        bool naEsquerda(){
            return this == pai->esquerdo;
        }

        bool filhoRed(){
            return (esquerdo != NULL and esquerdo->cor == RED) or
                (direito != NULL and direito->cor == RED);
        }

        NoRB *tio(){
            if(pai == NULL || pai->pai == NULL) return NULL;
            if(pai->naEsquerda()) return pai->pai->direito;
            else return pai->pai->esquerdo;
        }

        NoRB *irmao(){
            if(pai == NULL) return NULL;
            if(naEsquerda()) return pai->direito;
            return pai->esquerdo;
        }

        void paraBaixo(NoRB *no){
            if(pai != NULL){
                if(naEsquerda()) pai->esquerdo = no;
                else pai->direito = no;
            }
            no->pai = pai;
            pai = no;
        }
};

// devemos ordenar as palarvas em ordem alfabetica e o valor significa quantas vezes a palavra ja apareceu no texto

//vetor dinanmico ordenado
class VO{
    private:
        vector<Item> ts;
        int size = 0;

    public:
        void add(string key, int val){
            int r = rank(key);
            if(r < size && ts[r].chave() == key){
                int v = ts[r].valor();
                ts[r].attVal(v+1);
                return;
            }

            Item *novo_item = new Item(key, val);
            ts.push_back(*novo_item);

            for(int j = size; j > r; j--){
                ts[j] = ts[j-1];
            }
            ts[r].attChave(key);
            ts[r].attVal(val);

            size++;
            return;
        }

        //quantas vezes a palavra s apareceu no texto ate o momento
        int value(string key){
            int r = rank(key);
            if(r < size && ts[r].chave() == key) return ts[r].valor();
            return -1;
        } 

        //quantas palavras sao menores que s
        int rank(string key){
            int comeco = 0;
            int fim = size - 1;
            while(comeco <= fim){
                int meio = (comeco + fim)/2;
                if(ts[meio].chave() == key) return meio;
                if(ts[meio].chave() < key) comeco = meio + 1;
                else fim = meio - 1;
            }
            return comeco;
        }   

        //qual a k-esima chave da tabela
        string select(int k){
            string ch = ts[k].chave();
            return ch;
        }   

        void imprime(){
            for(int i = 0; i<size; i++){
                Item auxItem = ts[i];
                string auxStr = auxItem.chave();
                cout<< auxStr << endl;
            }
            return;
        }
};

//arvore de busca binária
class ABB{
    private:
        No *raiz;

        No* put(No* raiz, string key, int val){
            if(raiz == NULL){
                No *nova_raiz = new No(key, val);
                raiz = nova_raiz;
                return raiz;
            }
            if(raiz->chave() == key){
                int a = raiz->valor();
                raiz->attVal(a+1);
                return raiz;
            }
            else if(raiz->chave() > key){
                raiz->attEsq(put(raiz->esq(), key, val));
            }
            else{
                raiz->attDir(put(raiz->dir(), key, val));
            }
            return raiz;
        }

        int getValue(No* no, string key){
            if(no == NULL) return -1; //nullptr
            if(no->chave() == key) return no->valor();
            if(no->chave() > key){
                return getValue(no->esq(), key);
            }
            return getValue(no->dir(), key);
        }

        int getRank(No* no, string key){
            if(no == NULL) return 0;
            if(no->chave() <= key){
                return 1 + getRank(no->esq(), key) + getRank(no->dir(), key);
            } else return getRank(no->esq(), key);
        }

        No* getSelect(No* no, int k, int *count){
            if(no == NULL) return NULL;

            No* esqu = getSelect(no->esq(), k, count);

            if(esqu != NULL) return esqu;

            *count = *count + 1;
            if(*count == k) return no;

            return getSelect(no->dir(), k, count);
        }

    public:
        ABB(){
            raiz = NULL;
        }

        void add(string key, int val){
            raiz = put(raiz, key, val);
        }

        int value(string key){
            return getValue(raiz, key);
        }

        int rank(string key){
            int r = getRank(raiz, key) - 1;
            return r;
        }

        string select(int k){
            int count = 0;
            No* no = getSelect(raiz, k, &count);
            return no->chave();
        }

        No* retRaiz(){
            return raiz;
        }

        void imprime(No* no){
            if(no != NULL){
                imprime(no->esq());
                cout << no->chave() << " ";
                imprime(no->dir());
            }
	    }

};

//treaps
class TR{ //MUDAR PRA RECEBER KEY E VALUE
    private:
        bool final_palavra;
        TR* caractere[trie_size];

    public:
        TR(){
            this->final_palavra = false;
            for(int i = 0; i < trie_size; i++){
                this->caractere[i] = NULL;
            }
        }

        void add(string key, int val){
            TR* atual = this;
            for(int i = 0; i < key.length(); i++){
                if(atual->caractere[key[i]] == NULL){
                    atual->caractere[key[i]] = new TR();
                }
                atual = atual->caractere[key[i]];
            }
            atual->final_palavra = true;
        }

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
    private:
        NoRB *raiz;

        void rotacaoEsq(NoRB *no){
            NoRB *novoPai = no->direito;
            if(no == raiz) raiz = novoPai;
            no->paraBaixo(novoPai);
            no->direito = novoPai->esquerdo;
            if(novoPai->esquerdo != NULL){
                novoPai->esquerdo->pai = no;
            }
            novoPai->esquerdo = no;
        }

        void rotacaoDir(NoRB *no){
            NoRB *novoPai = no->esquerdo;
            if(no == raiz) raiz = novoPai;
            no->paraBaixo(novoPai);
            no->esquerdo = novoPai->direito;
            if(novoPai->direito != NULL){
                novoPai->direito->pai = no;
            }
            novoPai->direito = no;
        }

        void mudaCor(NoRB *no1, NoRB *no2){
            COLOR temp;
            temp = no1->cor;
            no1->cor = no2->cor;
            no2->cor = temp;
        }

        //arruma pai vermelho com filho vermelho
        void redRed(NoRB *no){
            if(no == raiz){
                no->cor = BLACK;
                return;
            }

            NoRB *pai = no->pai;
            NoRB *avo = pai->pai;
            NoRB *tio = no->tio();
            
            if(pai->cor != BLACK){
                if(tio != NULL && tio->cor == RED){
                    pai->cor = BLACK;
                    tio->cor = BLACK;
                    avo->cor = RED;
                    redRed(avo);
                } else {
                    
                    if(pai->naEsquerda()){
                        
                        if(no->naEsquerda()){
                            mudaCor(pai, avo);
                        } else {
                            rotacaoEsq(pai);
                            mudaCor(no, avo);
                        }
                        rotacaoDir(avo);
                    } else {
                        
                        if(no->naEsquerda()){
                            
                            rotacaoDir(pai);
                            mudaCor(no, avo);
                        } else {
                            
                            mudaCor(pai, avo);
                        }
                        rotacaoEsq(avo);
                    }
                }
            }
        }

        NoRB *procura(string key){
            NoRB *temp = raiz;
            while(temp != NULL){
                if(key < temp->key){
                    if(temp->esquerdo == NULL) break;
                    else temp = temp->esquerdo;
                } else if(key == temp->key){
                    break;
                } else {
                    if(temp->direito == NULL) break;
                    else temp = temp->direito;
                }
            }
            return temp;
        }

        int getValue(NoRB* no, string key){
            if(no == NULL) return -1; //nullptr
            if(no->key == key) return no->val;
            if(no->key > key){
                return getValue(no->esquerdo, key);
            }
            return getValue(no->direito, key);
        }

        int getRank(NoRB* no, string key){
            if(no == NULL) return 0;
            if(no->key <= key){
                return 1 + getRank(no->esquerdo, key) + getRank(no->direito, key);
            } else return getRank(no->esquerdo, key);
        }

        NoRB* getSelect(NoRB* no, int k, int *count){
            if(no == NULL) return NULL;
            NoRB* esqu = getSelect(no->esquerdo, k, count);
            if(esqu != NULL) return esqu;
            *count = *count + 1;
            if(*count == k) return no;
            return getSelect(no->direito, k, count);
        }

        //FUNCOES PARA IMPRIMIR, DEPOIS TIRAR!!
        // prints level order for given node
        void levelOrder(NoRB *x) {
            //cout<< "TESTE 3" << endl;
            if (x == NULL)
            // return if node is null
            return;

            // queue for level order
            queue<NoRB *> q;
            NoRB *curr;

            // push x
            q.push(x);

            while (!q.empty()) {
                // while q is not empty
                // dequeue
                curr = q.front();
                q.pop();

                // print node value
                cout << curr->key << " ";

                // push children to queue
                if (curr->esquerdo != NULL)
                    q.push(curr->esquerdo);
                if (curr->direito != NULL)
                    q.push(curr->direito);
            }
        }

        // prints inorder recursively
        void inorder(NoRB *x) {
            //cout<< "TESTE 4" << endl;
            if (x == NULL) return;
            inorder(x->esquerdo);
            cout << x->key << " ";
            inorder(x->direito);
        }

    public:
        ARN(){
            raiz = NULL;
        }

        NoRB *retRaiz(){
            return raiz;
        }

        void add(string key, int val){
            NoRB *novoNo = new NoRB(key, val);
            if(raiz == NULL){
                novoNo->cor = BLACK;
                raiz = novoNo;
            } else {
                NoRB *temp = procura(key);
                if(temp->key == key){
                    temp->val = temp->val + 1;
                    return;
                }
                novoNo->pai = temp;
                if(key < temp->key) temp->esquerdo = novoNo;
                else temp->direito = novoNo;
                redRed(novoNo);
            }
        }

        int value(string key){
            return getValue(raiz, key);
        }

        int rank(string key){
            int r = getRank(raiz, key) - 1;
            return r;
        }

        string select(int k){
            int count = 0;
            NoRB* no = getSelect(raiz, k, &count);
            return no->key;
        }

        //FUNCOES PARA IMPRIMIR, DEPOIS TIRAR!!
        void printInOrder() {
            //cout<< "TESTE 2" << endl;
            cout << "Inorder: " << endl;
            if (raiz == NULL)
            cout << "Tree is empty" << endl;
            else
            inorder(raiz);
            cout << endl;
        }

        // prints level order of the tree
        void printLevelOrder() {
            //cout<< "TESTE 5" << endl;
            cout << "Level order: " << endl;
            if (raiz == NULL)
            cout << "Tree is empty" << endl;
            else
            levelOrder(raiz);
            cout << endl;
        }
};

//converte string para int para auxiliar com as instrucoes
void converte(string str, int *num){
    stringstream ss;  
    ss << str;  
    ss >> *num;
    return;
}

//funcoes para receber instrucoes em cada implementacao
void fVO(int q, string instrucoes[], vector<string> palavras){
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
            for(int i = 0; i < num; i++){
                ts.add(palavras[i], 1);
            }
        }
        else if(inst == "2"){
            int a = ts.value(var);
            if(a == -1) cout<< "A palavra "<<var<<" apareceu no texto nenhuma vez ate o momento." << endl;
            else cout<< "A palavra "<<var<<" apareceu no texto "<<a<< " vez(es) ate o momento." << endl;
        }
        else if(inst ==  "3"){
            int b = ts.rank(var);
            cout<< b << " palavra(s) sao menores que "<<var<<"."<< endl;
        }
        else if(inst == "4"){
            string c = ts.select(num);
            cout<< "A "<<num<< "-esima chave da tabela eh "<<c<<"."<< endl;
        }
        else cout<< "Instrução não encontrada.\n";
        i = i + 2;
    }
    //ts.imprime();
    return;
}

void fABB(int q, string instrucoes[], vector<string> palavras){
    ABB ts;
    int i = 0;
    while(i < q*2){
        string inst = instrucoes[i];
        string var = instrucoes[i+1];

        int num;
        if(inst == "1" || inst == "4"){
            converte(var, &num);
        }

        if(inst == "1"){
            for(int i = 0; i < num; i++){
                ts.add(palavras[i], 1);
            }
        }
        else if(inst == "2"){
            int a = ts.value(var);
            if(a == -1) cout<< "A palavra "<<var<<" apareceu no texto nenhuma vez ate o momento." << endl;
            else cout<< "A palavra "<<var<<" apareceu no texto "<<a<< " vez(es) ate o momento." << endl;
        }
        else if(inst ==  "3"){
            int b = ts.rank(var);
            cout<< b << " palavra(s) sao menores que "<<var<<"."<< endl;
        }
        else if(inst == "4"){
            string c = ts.select(num+1);
            cout<< "A "<<num<< "-esima chave da tabela eh "<<c<<"."<< endl;
        }
        else cout<< "Instrução não encontrada.\n";
        i = i + 2;
    }
    ts.imprime(ts.retRaiz());
    return;
}

void fTR(int q, string instrucoes[], vector<string> palavras){
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

void fADT(int q, string instrucoes[], vector<string> palavras){
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

void fARN(int q, string instrucoes[], vector<string> palavras){
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
            for(int i = 0; i < num; i++){
                ts.add(palavras[i], 1);
            }
        }
        else if(inst == "2"){
            int a = ts.value(var);
            if(a == -1) cout<< "A palavra "<<var<<" apareceu no texto nenhuma vez ate o momento." << endl;
            else cout<< "A palavra "<<var<<" apareceu no texto "<<a<< " vez(es) ate o momento." << endl;
        }
        else if(inst ==  "3"){
            int b = ts.rank(var);
            cout<< b << " palavra(s) sao menores que "<<var<<"."<< endl;
        }
        else if(inst == "4"){
            string c = ts.select(num+1);
            cout<< "A "<<num<< "-esima chave da tabela eh "<<c<<"."<< endl;
        }
        else cout<< "Instrução não encontrada.\n";
        i = i + 2;
    }
    ts.printInOrder();
    return;
}

//separa as palavras do texto em um vetor
vector<string> arrayChar(string texto, int *size){
    vector<string> palavras;
    int n = texto.length();
    char char_array[n + 1];
    strcpy(char_array, texto.c_str()); //transforma string em um array de char

    char *pch;
    pch = strtok (char_array," ,.-!?");
    while (pch != NULL){
        string str = pch;
        palavras.push_back(str);
        *size = *size + 1;
        pch = strtok(NULL, " ,.-!?");
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

    cout<< "Insira o texto:\n";
    //cin>> texto;
    cin.ignore();
    getline(cin, texto);
    
    cout<< "Digite o numero de operacoes a serem realizadas na tabela de simbolos:\n";
    cin>> q;

    //separa as palavras do texto em um vetor
    int size = 0;
    palavras = arrayChar(texto, &size);
    for(int i = 0; i<size; i++){
        string s = palavras[i];
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
    if(estrutura == "VO") fVO(q, instrucoes, palavras);
    else if(estrutura == "ABB") fABB(q, instrucoes, palavras);
    else if(estrutura == "TR") fTR(q, instrucoes, palavras);
    else if(estrutura == "A23") fADT(q, instrucoes, palavras);
    else if(estrutura == "ARN") fARN(q, instrucoes, palavras);

    return 0;
}