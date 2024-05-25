#include <iostream>
#include <stdio.h>
#include <stack>
using namespace std;

int m; int n; //dimensoes da matriz
int posx; int posy; //posição atual

/*int tabuleiro[3][20] =    {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}*/
/*char tabuleiro[5][3] =    {{'0','0','0'},
                            {'0','1','0'},
                            {'1','0','1'},
                            {'0','0','0'},
                            {'1','0','1'}};*/
char tabuleiro[3][11] = {{'0','0','0','1','0','1','0','0','0','0','0'},
                        {'0','1','0','0','0','0','1','1','1','1','1'},
                        {'1','1','1','1','0','1','1','1','1','1','1'}};

/*{{'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},*/

const char pecas[4][9][5][5] = {
/*{ //peça F
{{'*','F','F','*','*'},
 {'F','F','*','*','*'},
 {'*','F','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'F','F','*','*','*'},
 {'*','F','F','*','*'},
 {'*','F','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {{'*','F','*','*','*'},
 {'F','F','F','*','*'},
 {'*','*','F','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {{'*','F','*','*','*'},
 {'F','F','F','*','*'},
 {'F','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {{'*','F','*','*','*'},
 {'*','F','F','*','*'},
 {'F','F','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {{'*','F','*','*','*'},
 {'F','F','*','*','*'},
 {'*','F','F','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {{'F','*','*','*','*'},
 {'F','F','F','*','*'},
 {'*','F','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {{'*','*','F','*','*'},
 {'F','F','F','*','*'},
 {'*','F','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
},*/
{ //peça I
{{'I','*','*','*','*'},
 {'I','*','*','*','*'},
 {'I','*','*','*','*'},
 {'I','*','*','*','*'},
 {'I','*','*','*','*'}},
{{'I','I','I','I','I'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
},
{ //peça U
{{'U','*','U','*','*'},
 {'U','U','U','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}}, //
{{'U','U','U','*','*'},
 {'U','*','U','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'} //indica que está no final das possíveis rotações da peça
},
{ //peça X
{{'*','X','*','*','*'},
 {'X','X','X','*','*'},
 {'*','X','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
},
{ //peça Y
{{'*','Y','*','*','*'},
 {'Y','Y','*','*','*'},
 {'*','Y','*','*','*'},
 {'*','Y','*','*','*'},
 {'*','*','*','*','*'}},
{{'Y','*','*','*','*'},
 {'Y','Y','*','*','*'},
 {'Y','*','*','*','*'},
 {'Y','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','Y','*','*','*'},
 {'Y','Y','Y','Y','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','*','Y','*','*'},
 {'Y','Y','Y','Y','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'Y','*','*','*','*'},
 {'Y','*','*','*','*'},
 {'Y','Y','*','*','*'},
 {'Y','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','Y','*','*','*'},
 {'*','Y','*','*','*'},
 {'Y','Y','*','*','*'},
 {'*','Y','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
}
};

stack<char> st; //pilha de peças
stack<char> rot; //pilha de rotações

void imprime(){ //imprime o tabuleiro
    cout<< "Matriz\n";
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout<< tabuleiro[i][j];
        }
        cout<< "\n";
    }
    return;
}

void criaTab(int m, int n, char tab){ //o usuário insere a matriz
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            //cin>> tab[i][j];
            //scanf(" %c", *tab[i][j]);
        }
    }
    return;
}

void valido(){ //procura uma posicao valida a partir da pos atual e retorna para posx e posy
    for(int i = posy; i < n; i++){
        for(int j = posx; j < m; j++){
            if(tabuleiro[j][i] == '0'){
                posx = j;
                posy = i;
                return;
            }
        }
    }
}

char letra(int ind){ //encontra letra da peça
    for(int q = 0; q < 5; q++){
        for(int j = 0; j < 5; j++){
            if(pecas[ind][0][q][j] != '*') return pecas[ind][0][q][j];
        }
    }
}

bool rotacao(int ind, int i){ //verifica se a rotação dada encaixa no tabuleiro
    int primeira = 1;
    for(int q = 0; q < 5; q++){
        for(int j = 0; j < 5; j++){
            if(pecas[ind][i][j][q] != '*'){
                if(primeira){ //ajusta a posição inicial para encaixar a peça
                    posx = posx - j;
                    posy = posy - q;
                    primeira = 0;
                }
                if(posx + j >= m || posy + q >= n){ //a peça não cabe no tabuleiro
                    cout<< "Nao encaixa 1\n";
                    return false;
                } else if(tabuleiro[posx+j][posy+q] != '0'){ //a peça não encaixa nessa posição no tabuleiro
                    cout<< "Nao encaixou 2 \n"<< pecas[ind][0][0][0]<< posx << j << "here" << posy << q << endl;
                    return false;
                }
            }
        }
    }
    cout<< "Encaixou " << pecas[ind][0][0][0] << endl;
    return true;
}

void pecaTab(int ind, int i){ //encaixa a peça no tabuleiro (matriz)
    for(int q = 0; q < 5; q++){
        for(int j = 0; j < 5; j++){
            if(pecas[ind][i][q][j] != '*'){
                tabuleiro[posx+q][posy+j] = pecas[ind][i][q][j];
            }
        }
    }
    valido();
    st.push(ind);
    rot.push(i);
    cout<< "posx " << posx << " posy " << posy << endl;
    imprime();
    return;
}

bool encaixa(int ind, int rot){  //verifica se uma dada peça encaixa na pos atual em todas as rotações
    valido();
    for(int i = rot; i < 8; i++){
        if(pecas[ind][i][0][0] == 'S') return false;
        if(rotacao(ind, i)){    //função rotacao() para ver se a rotacao encaixa
            pecaTab(ind, i);    //função pecaTab() para encaixar a peça no tabuleiro
            return true;
        }
    }
    return false;
}

void desencaixa(int ind, int *i){ //desencaixa peça do tabuleiro
    st.pop();
    *i = rot.top();
    rot.pop();
    char peca = letra(ind);

    cout<< "Desencaixou " << pecas[ind][0][0][0] << endl;

    for(int q = 0; q < m; q++){
        for(int j = 0; j < n; j++){
            if(tabuleiro[q][j] == peca) tabuleiro[q][j] = '0';
        }
    }
    imprime();
}

void pentaminos(int npecas){
    int cont = 0;
    int encaixadas[npecas];
    int inicio = 0;
    int rot = 0;

    for(int i = 0; i < npecas; i++) encaixadas[i] = 0; //inicia array de peças que foram encaixadas
    valido(); //procura primeira casa válida no tabuleiro

    while(cont < npecas){ //enquanto existe uma peça para encaixar 
        bool encaixou = false;
        while(!encaixou){
            for(int i = inicio; i < npecas; i++){ 
                cout<< "encaixadas " << i << endl;
                if(encaixadas[i] == 0 && encaixa(i, rot) && cont < npecas){ 
                    cont++;
                    cout<< "Valor de count " << cont << endl;
                    encaixadas[i] = 1;
                    encaixou = true;
                }

                if(inicio != 0){
                    cout<< "inicio diferente de zero" << endl;
                    inicio = 0;
                    i = -1;
                }
                cout<< "valor de I " << i << endl;
                rot = 0;
            }
        }   
        
        //backtracking
        if(cont < npecas && encaixou == false){
            if(!st.empty()){
                int ind = st.top();
                desencaixa(ind, &rot);

                encaixadas[ind] = 0;
                inicio = ind;
                if(rot < 9){
                    rot++;
                } else {
                    inicio++;
                }
                cont--;
            } else {
                cout<< "Impossivel\n";
                return;
            }
        }

        encaixou = false;
    }
    return;
}

int main(){
    int npecas = 3; //numero de peças
    m = 3; n = 11;

    pentaminos(npecas);
    imprime();

    return 0;
} 