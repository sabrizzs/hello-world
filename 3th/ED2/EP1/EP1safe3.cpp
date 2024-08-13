#include <iostream>
#include <stdio.h>
#include <stack>
using namespace std;

int m; int n; //dimensoes da matriz
int posx; int posy; //posição atual
int aposx; int aposy; //posicao anterior

/*char tabuleiro[3][20] =  {{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
                            {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
                            {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}};*/
char tabuleiro[6][10] =     {{'0','0','0','0','0','0','0','0','0','0'},
                             {'0','0','0','0','0','0','0','0','0','0'},
                             {'0','0','0','0','0','0','0','0','0','0'},
                             {'0','0','0','0','0','0','0','0','0','0'},
                             {'0','0','0','0','0','0','0','0','0','0'},
                             {'0','0','0','0','0','0','0','0','0','0'}};

/*{{'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},*/

const char pecas[12][9][5][5] = {
{ //peça F
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
},
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
{ //peça L
{{'L','*','*','*','*'},
 {'L','*','*','*','*'},
 {'L','*','*','*','*'},
 {'L','L','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','L','*','*','*'},
 {'*','L','*','*','*'},
 {'*','L','*','*','*'},
 {'L','L','*','*','*'},
 {'*','*','*','*','*'}},
{{'L','L','L','L','*'},
 {'L','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'L','L','L','L','*'},
 {'*','*','*','L','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'L','L','*','*','*'},
 {'*','L','*','*','*'},
 {'*','L','*','*','*'},
 {'*','L','*','*','*'},
 {'*','*','*','*','*'}},
{{'L','L','*','*','*'},
 {'L','*','*','*','*'},
 {'L','*','*','*','*'},
 {'L','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','*','*','L','*'},
 {'L','L','L','L','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'L','*','*','*','*'},
 {'L','L','L','L','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
},
{ //peça N
{{'N','N','*','*','*'},
 {'*','N','N','N','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','*','N','N','*'},
 {'N','N','N','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','N','*','*','*'},
 {'N','N','*','*','*'},
 {'N','*','*','*','*'},
 {'N','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'N','*','*','*','*'},
 {'N','N','*','*','*'},
 {'*','N','*','*','*'},
 {'*','N','*','*','*'},
 {'*','*','*','*','*'}},
{{'N','N','N','*','*'},
 {'*','*','N','N','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','N','N','N','*'},
 {'N','N','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','N','*','*','*'},
 {'*','N','*','*','*'},
 {'N','N','*','*','*'},
 {'N','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'N','*','*','*','*'},
 {'N','*','*','*','*'},
 {'N','N','*','*','*'},
 {'*','N','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
},
{ //peça P
{{'P','P','*','*','*'},
 {'P','P','*','*','*'},
 {'P','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'P','P','*','*','*'},
 {'P','P','*','*','*'},
 {'*','P','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'P','P','P','*','*'},
 {'*','P','P','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'P','P','P','*','*'},
 {'P','P','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'P','P','*','*','*'},
 {'P','P','P','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','P','P','*','*'},
 {'P','P','P','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'P','*','*','*','*'},
 {'P','P','*','*','*'},
 {'P','P','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','P','*','*','*'},
 {'P','P','*','*','*'},
 {'P','P','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
},
{ //peça T
{{'T','T','T','*','*'},
 {'*','T','*','*','*'},
 {'*','T','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'T','*','*','*','*'},
 {'T','T','T','*','*'},
 {'T','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','*','T','*','*'},
 {'T','T','T','*','*'},
 {'*','*','T','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','T','*','*','*'},
 {'*','T','*','*','*'},
 {'T','T','T','*','*'},
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
{{'U','U','*','*','*'},
 {'U','*','*','*','*'},
 {'U','U','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'U','U','U','*','*'},
 {'U','*','U','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'} //indica que está no final das possíveis rotações da peça
},
{ //peça V
{{'V','*','*','*','*'},
 {'V','*','*','*','*'},
 {'V','V','V','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','*','V','*','*'},
 {'*','*','V','*','*'},
 {'V','V','V','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'V','V','V','*','*'},
 {'V','*','*','*','*'},
 {'V','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'V','V','V','*','*'},
 {'*','*','V','*','*'},
 {'*','*','V','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
},
{ //peça W
{{'W','*','*','*','*'},
 {'W','W','*','*','*'},
 {'*','W','W','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','*','W','*','*'},
 {'*','W','W','*','*'},
 {'W','W','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','W','W','*','*'},
 {'W','W','*','*','*'},
 {'W','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'W','W','*','*','*'},
 {'*','W','W','*','*'},
 {'*','*','W','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
 {'S'}
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
},
{ //peça Z
{{'Z','Z','*','*','*'},
 {'*','Z','*','*','*'},
 {'*','Z','Z','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','Z','Z','*','*'},
 {'*','Z','*','*','*'},
 {'Z','Z','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'*','*','Z','*','*'},
 {'Z','Z','Z','*','*'},
 {'Z','*','*','*','*'},
 {'*','*','*','*','*'},
 {'*','*','*','*','*'}},
{{'Z','*','*','*','*'},
 {'Z','Z','Z','*','*'},
 {'*','*','Z','*','*'},
 {'*','*','*','*','*'},
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
    aposx = posx; aposy = posy;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
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
    valido();
    int primeira = 1;
    for(int q = 0; q < 5; q++){
        for(int j = 0; j < 5; j++){
            if(pecas[ind][i][j][q] != '*'){
                //cout<< "x inicial " << posx << " y inicial " << posy << endl;
                if(primeira){ //ajusta a posição inicial para encaixar a peça
                    posx = posx - j;
                    posy = posy - q;
                    primeira = 0;
                    //cout<< "ajustou x e y\n";
                }
                if(posx + j >= m || posy + q >= n){ //a peça não cabe no tabuleiro
                    //cout<< "Não encaixa 1\n";
                    return false;
                } else if(tabuleiro[posx+j][posy+q] != '0'){ //a peça não encaixa nessa posição no tabuleiro
                    //cout<<"Nao encaixou 2 \n"<< letra(ind)<<" no x "<<posx<<" e j "<< j << " no y "<<posy<<" com q "<< q << endl;
                    return false;
                }
            }
        }
    }
    //cout<< "Encaixou " << letra(ind) << endl;
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

    for(int q = 0; q < m; q++){
        for(int j = 0; j < n; j++){
            if(tabuleiro[q][j] == peca) tabuleiro[q][j] = '0';
        }
    }
    posx = aposx; posy = aposy;
    //cout<< "Desencaixou " << letra(ind) << endl;
    imprime();
}

bool disponivel(int encaixadas[], int *ult){ //verifica se há uma peça anterior para encaixar
    int peca = st.top();
    for(int i = 0; i < *ult; i++){
        if(encaixadas[i] == 0) *ult = 0; return true;
    }
    *ult = 0; 
    return false;
}

void pentaminos(int npecas){
    int cont = 0;
    int encaixadas[npecas];
    int inicio = 0;
    int rot = 0;
    int ult;

    for(int i = 0; i < npecas; i++) encaixadas[i] = 0; //inicia array de peças que foram encaixadas
    valido(); //procura primeira casa válida no tabuleiro

    while(cont < npecas){ //enquanto existe uma peça para encaixar
        
        for(int i = inicio; i < npecas; i++){
            //cout<< "encaixadas " << i << endl;
            //cout<< "GRAMADO " << rot << endl;
            //cout<< "LIVRO " << letra(i) << endl;
            //imprime();
            cout<< "Tentou encaixar " << letra(i) << endl;
            if(encaixadas[i] == 0 && encaixa(i, rot) && cont < npecas){ ////////////////////
                cont++;
                //cout<< "Valor de count " << cont << endl;
                encaixadas[i] = 1;
                ult = i;
                i = -1; //reinicia dps que encaixou uma peça
                if(inicio != 0){
                //cout<< "inicio diferente de zero" << endl;
                inicio = 0;
                i = -1;
                }
            } else ult = 0;

            
            //cout<< "valor de I " << i << endl;
            rot = 0;
        }
        
        //backtracking //PAREI AQUI BACKTRACKING COM PROBLEMA
        if(cont < npecas && !disponivel(encaixadas, &ult)){
            if(!st.empty()){
                int ind = st.top();
                desencaixa(ind, &rot);

                encaixadas[ind] = 0;
                inicio = ind;
                if(rot < 9){
                    rot++;
                    //cout<< "ROTACAO " << rot << endl;
                } 
                cont--;
            } else {
                cout<< "Impossivel!\n";
                return;
            }
        }

    }
    cout<< "Possivel!\n";
    return;
}

int main(){
    cout<< "Start!";
    int npecas = 12; //numero de peças
    m = 6; n = 10;

    pentaminos(npecas);
    imprime();

    return 0;
}