#include <iostream>
#include <cmath>
using namespace std;

/* 
    Alunas: Luísa Menezes da Costa (nºUSP 12676491)
            Sabrina Araújo da Silva (nºUSP 12566182)

    Ao executar o código colocar um argumento na linha de comando para exibir
    os valores de xk até chegar na raiz da função. (ex: ./EP1 0)

    Parte 1:
    Método do ponto fixo para encontrar as 3 raízes da função
    O algoritmo recebe do usuário os valores dos erros e o x0 de cada função.
    f(x) = exp(x) - 2x^2
    Funções g(x) utilizadas:
    g1(x) = ln(2x^2)
    g2(x) = +sqrt(e^x/2)
    g3(x) = -sqrt(e^x/2)
*/

//verifica se |xk+1 - xk| < E1
bool erroi(double xki, double xk, double ei){
    if(fabs(xki-xk) < ei) return true;
    return false;
}

//verifica se |f(xk+1)| < E2
bool erroii(double xki, double eii){
    double f = fabs(exp(xki) - 2*pow(xki, 2));
    if(f < eii) return true;
    return false;
}

//funções g(x) encontradas
double gi(double x){
    double gi = log(2*pow(x, 2));
    return gi;
}

double gii(double x){
    double gii = sqrt(exp(x)/2);
    return gii;
}

double giii(double x){
    double giii = -sqrt(exp(x)/2);
    return giii;
}

//funções recursivas para achar as raizes das funções g(x)
double iteracaogi(double xk, double ei, double eii, bool print){
    double xki = gi(xk);
    if(print) cout<< xki << endl;
    if(erroi(xki, xk, ei) || erroii(xki, eii)) return xki;
    return iteracaogi(xki, ei, eii, print);
}

double iteracaogii(double xk, double ei, double eii, bool print){
    double xki = gii(xk);
    if(print) cout<< xki << endl;
    if(erroi(xki, xk, ei) || erroii(xki, eii)) return xki;
    return iteracaogii(xki, ei, eii, print);
}

double iteracaogiii(double xk, double ei, double eii, bool print){
    double xki = giii(xk);
    if(print) cout<< xki << endl;
    if(erroi(xki, xk, ei) || erroii(xki, eii)) return xki;
    return iteracaogiii(xki, ei, eii, print);
}

//recebe os valores dos erros e de x0 do usuário
void recebe(double *ei, double *eii, double *xoi, double *xoii, double intervaloi, double intervaloii){
    cout<< "Insira o E1 (erro 1):\n";
    cin>> *ei;
    cout<< "Insira o E2 (erro 2):\n";
    cin>> *eii;

    cout<< "Insira o valor de x0 para a g(x) = ln(2x^2) no intervalo x0 > " << intervaloi << ":\n";
    cin>> *xoi;
    while(*xoi <= intervaloi){
        cout<< "Valor de x0 incorreto. Por favor, insira x0 no intervalo x0 > " << intervaloi << ":\n";
        cin>> *xoi;
    }
    cout<< "Insira o valor de x0 para a g(x) = +- sqrt(e^x/2) no intervalo x0 < " << intervaloii << ":\n";
    cin>> *xoii;
    while(*xoii >= intervaloii){
        cout<< "Valor de x0 incorreto. Por favor, insira x0 no intervalo x0 < " << intervaloii << ":\n";
        cin>> *xoii;
    }
    return;
}

void partei(bool print){
    cout<< "Parte 1: Metodo de ponto fixo\nAlgoritmo que utiliza o metodo do ponto fixo para encontrar as 3 raizes da funcao f(x) = exp(x) - 2x^2.\n" << endl;
    double gi, gii, giii; 
    double ei, eii;
    double xoi, xoii;
    
    double intervaloi = 2.0;        //intervalo encontrado para a g1(x)
    double intervaloii = 2.079444;  //intervalo encontrado para a g2(x) e a g3(x)

    recebe(&ei, &eii, &xoi, &xoii, intervaloi, intervaloii); //recebe parametros do usuario

    //iteração para achar xk
    if(print) cout<< "Valores de x1...xk para a raiz 1:\n";
    double resulti = iteracaogi(xoi, ei, eii, print);
    cout<< "raiz 1: " <<resulti << endl;
    if(print) cout<< "Valores de x1...xk para a raiz 2:\n";
    double resultii = iteracaogii(xoii, ei, eii, print);
    cout<< "raiz 2: " <<resultii << endl;
    if(print) cout<< "Valores de x1...xk para a raiz 3:\n";
    double resultiii = iteracaogiii(xoii, ei, eii, print);
    cout<< "raiz 3: " <<resultiii << endl;
}

int main(int argc, char *argv[]){
    bool print;
    if(argc > 1){
        print = true;
    } else print = false;

    partei(print);
    return 0;
}

