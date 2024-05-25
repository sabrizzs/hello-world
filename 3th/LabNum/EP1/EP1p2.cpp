#include <iostream>
#include <cmath>
#include <complex>
#include <stdio.h>  
#include <stdlib.h> 
using namespace std;

/*  
    Alunas: Luísa Menezes da Costa (nºUSP 12676491)
            Sabrina Araújo da Silva (nºUSP 12566182)
    Parte 2: 
    Método de Newton
    Algoritmo que gera uma imagem que ilustra as bacias de convergência de uma função.
*/

//ponteiro para uma funcao double que aceita double e int como parametro
typedef double (*fct_ptr)(double, int);

//funcao I = x^6 - 1
double funcaoi(double x, int param){
    // se param == 0 calcula a funcao, se != 0 calcula a derivada
    if(param) return 6*pow(x, 5);
    else return pow(x, 6) - 1; 
}

//funcao II = x^3 - 1
double funcaoii(double x, int param){
    if(param) return 2*pow(x, 2);
    else return pow(x, 3) - 1;
}

//funcao III = x^3 - 7
double funcaoiii(double x, int param){
    if(param) return 3*pow(x, 2);
    else return pow(x, 3)-7;
}

//calcula o valor da função f aplicada em x
double evalf(double x, fct_ptr funcao){
    return funcao(x, 0);
}

//calcula o valor da derivada da função f aplicada em x
double evalDf(double x, fct_ptr funcao){
    return funcao(x, 1);
}

//aplica o método de Newton para achar uma raiz da função f (com primeira derivada f0), partindo do ponto x0.
bool newton(double xo, double tol, double it, fct_ptr funcao, double *raiz){
    //xo = aproximacao inicial, tol = tolerancia, it = numero de iteracoes
    int k = 0;
    while(k < it){
        double x = xo - (evalf(xo, funcao)/evalDf(xo, funcao));
        if(abs(x-xo) < tol || abs(x-xo)/abs(x) < tol || abs(evalf(x, funcao)) < tol){
            *raiz = x;
            return true;
        }
        k += 1;
        xo = x;
    }
    cout<< "O metodo de Newton para achar uma raiz da função f falhou apos "<< it << " iteracoes.\n";
    return false;
}

void gnuplot(){
    int x = 0, y = 0;
    FILE *fp = NULL;
    FILE *gnupipe = NULL;
    char *gnuCommands[] = {"set title \"Bacias de convergencia\"", "plot 'pontos.txt'  using 1:2:(arg($3+$4*{0,1})) '(%lf,%lf) (%lf,%lf)' palette"};

    fp = fopen("data.tmp", "w");
    if(fp == NULL) {
        perror ("Erro: ");
        getchar();
        exit (1);
    }
    gnupipe = popen("gnuplot -persistent", "w");

    for (int i = 0; i < 11; i++){
        fprintf(fp, "%d %d\n", x, y);
        x++; y++;
    }
    fclose(fp);

    for(int i = 0; i < 2; i++){
        fprintf(gnupipe, "%s\n", gnuCommands[i]);
    }

    fclose(gnupipe);
    return;
}

//acha as bacias de convergência da função f no domínio [l1, u1]x[l2, u2] e gera um arquivo output.txt que contém os dados para a geração da imagem das bacias
void newton_basins(double l, double u, double p, fct_ptr funcao){
    FILE *pontos;
    pontos = fopen ( "pontos.txt", "w" );
    if(pontos == NULL) {
        perror ("Erro: "); //<- para comprocar é com perror e não com printf
        getchar();
        exit (1);
    }

    //newton para cada um dos pontos
    for(int y = 1; y <= p; y++){
        double zy = y * (u - (-u))/(p-1) + (-u);        //parte imaginaria
        for(int x = 1; x <= p; x++){
            double zx = x * (l - (-l))/(p-1) + (-l);    //parte real
            std::complex<double> complex(zx, zy);       //cria um numero complexo com zx e zy
            double raiz;
            newton(abs(complex), 0.0001, 1000, funcao, &raiz);      //calcula newton p/ o ponto
            fprintf(pontos, "(%f,%f) (%f,%f)\n", zy, zx, zy, zx);   //imprime no arquivo
        }
    }

    fclose(pontos);
    gnuplot();
    return;
}

void parteii(){
    cout<< "Parte 2: Metodo de Newton\nAlgoritmo que gera uma imagem que ilustra as bacias de convergencia de uma funcao f.";
    double l = 2, u = 2;    //domínio
    double p = 150;         //pontos

    //iniciar a função abaixo com o 4º argumento sendo umas das 3 funções: funcaoi, funcaoii ou funcaoiii                    
    newton_basins(l, u, p, funcaoi);
    return;
}

int main(){
    parteii();
    return 0;
}