#include <iostream>
#include <stdio.h>
#include <math.h>
#include <random>   //para calcular a distribuição uniforme
#include <time.h>   //seed
using namespace std;

/*
Alunas: Sabrina Araújo da Silva (nºUSP 12566182)
        Samantha Miyahira (nº USP 11797261)
*/

////////////// PARTE 1 //////////////

void parte1(){
    // Parte 1: Calculo do valor do trabalho por interpolacao de Lagrange
  
    // inicializamos os vetores que contem os pares ordenados a serem interpolados
    float X[7] = {0, 5, 10, 15, 20, 25, 30};
    float y[7] = {0.0, 1.5297, 9.512, 8.7025, 2.8087, 1.0881, 0.3537};
    
    // calculando os coeficientes do polinomio de newton
    // p(x) = c0 + c1(x-x0) + c2(x-x0)(x-x1) + c3(x-x0)(x-x1)(x-x2) + c4(x-x0)(x-x1)(x-x2)(x-x3) + c5(x-x0)(x-x1)(x-x2)(x-x3)(x-x4) + c6(x-x0)(x-x1)(x-x2)(x-x3)(x-x4)(x-x5)
    float x0 = X[0];
    float x1 = X[1];
    float x2 = X[2];
    float x3 = X[3];
    float x4 = X[4];
    float x5 = X[5];
    float x6 = X[6];

    float c0 = 0;
    float c1 = -c0 + y[1]/(x1-x0);
    float c2 = (y[2]-c0-c1*(x2-x0))/((x2-x0)*(x2-x1)); 
    float c3 = (y[3]-c0-c1*(x3-x0)-c2*(x3-x0)*(x3-x1))/((x3-x0)*(x3-x1)*(x3-x2));
    float c4 = (y[4]-c0-c1*(x4-x0)-c2*(x4-x0)*(x4-x1)-c3*(x4-x0)*(x4-x1)*(x4-x2))/((x4-x0)*(x4-x1)*(x4-x2)*(x4-x3));
    float c5 = (y[5]-c0-c1*(x5-x0)-c2*(x5-x0)*(x5-x1)-c3*(x5-x0)*(x5-x1)*(x5-x2)-c4*(x5-x0)*(x5-x1)*(x5-x2)*(x5-x3))/((x5-x0)*(x5-x1)*(x5-x2)*(x5-x3)*(x5-x4));
    float c6 = (y[6]-c0-c1*(x6-x0)-c2*(x6-x0)*(x6-x1)-c3*(x6-x0)*(x6-x1)*(x6-x2)-c4*(x6-x0)*(x6-x1)*(x6-x2)*(x6-x3)-c5*(x6-x0)*(x6-x1)*(x6-x2)*(x6-x3)*(x6-x4))/((x6-x0)*(x6-x1)*(x6-x2)*(x6-x3)*(x6-x4)*(x6-x5));
    
    //interpolando os pontos
    float p[7];
    for(int i=0;i<7;i++){
        float x=X[i];
        p[i] = c0 + c1*(x-x0) + c2*(x-x0)*(x-x1) + c3*(x-x0)*(x-x1)*(x-x2) + c4*(x-x0)*(x-x1)*(x-x2)*(x-x3) + c5*(x-x0)*(x-x1)*(x-x2)*(x-x3)*(x-x4) + c6*(x-x0)*(x-x1)*(x-x2)*(x-x3)*(x-x4)*(x-x5);
    }

    for (int j=0; j<7; j++){
        cout << "O valor de p(" << j << ") = " << p[j] << endl;
    }
    
    /* (iia) Aproximacao do valor do trabalho usando regra do trapezio composta */
    float b = X[6];
    float a = X[0];
    int r=6;
    float h = (b-a)/r; //dividido pelo numero de subintervalos (n-1)
    float somatorio = (h/2)*y[0];//eh zero
    for (int i=1;i<r;i++){
        somatorio += h*y[i];
    }
    somatorio += (h/2)*y[6];
    
    cout << "Aproximando pela regra do trapezio composta, o valor do trabalho equivale a " << somatorio << "\n" << endl;
    
    /* (iib) Aproximação por regra de Simpson composta */
    float sum1 = 0;
    float sum2 = 0;
    
    // primeiro somatorio = sum^{n-2}_{k=1} f(x_{2k-1})
    for (int i=1;i<=r/2;i++){
        if (2*i-1>=0){
            sum1 += y[2*i-1];
        }
    }
    sum1 *= 4;
    
    // segundo somatorio = sum^{n/2-1}_{k=1} f(x_{2k})
    for (int i=1;i<=((r/2)-1);i++){
        sum2 += y[2*i];
    }
    sum2 *= 2;
    
    float sn;
    sn = (h/3)*(y[0]+y[6]+sum1+sum2);
    
    cout << "Aproximando pela regra de simpson composta, o valor do trabalho equivale a " << sn << "\n" << endl;

    return;
}

////////////// PARTE 2 //////////////

//ponteiro para uma funcao float que aceita float como parametro
typedef float (*fct_ptr)(float);

//funcoes das integrais
float seno(float x){
    return sin(x);
}

float x3(float x){
    return x*x*x;
}

float ex(float x){
    return exp(-x);
}

//integral unidimensional
float uni(float a, float b, float n, fct_ptr funcao){
    mt19937 mt(time(NULL));
    
    float H = funcao(b);     //valor máximo

    float A;                 //area do retangulo
    if(isnan((b-a)*H))A = 1; //evitando a multiplicação de infinito por 0 (indeterminação)
    else A = (b-a)*H;        

    //aproximando I a partir de números aleatórios com distribuição uniforme
    int contador = 0;
    for(int i = 0; i<n; i++){
        uniform_real_distribution<float> x1(a, b);
        float x = x1(mt);

        uniform_real_distribution<float> y1(a, H);
        float y = y1(mt);

        float f = funcao(x);
        if(y <= f) contador++;
    }
    float result = (float(contador)/n) * A;
    return result;
}

//integral multidimensional
float multi(int n){
    mt19937 mt(time(NULL));
    int pontos_circulo = 0;
    int pontos_quadrado = 0;
    float pi;

    //aproximando I a partir de números aleatórios com distribuição uniforme
    for(int i = 0; i < n; i++){
        uniform_real_distribution<float> x1(0.0, 1.0);
        float x = x1(mt);

        uniform_real_distribution<float> y1(0.0, 1.0);
        float y = y1(mt);
        
        float distancia = x*x+y*y;

        if(distancia <= 1) pontos_circulo++;
        pontos_quadrado++; 
    }
    pi = float(4*pontos_circulo)/pontos_quadrado;
    return pi;
}

void parte2(){
    // Parte 2: Integração por Monte Carlo
    float n = 1000000;

    //integrais unidimensionais
    float a = uni(0, 1, n, seno);
    cout << "Integral unidimensional de sin(): " << a << endl;

    float b = uni(3, 7, n, x3);
    cout << "Integral unidimensional de x^3(): " << b << endl;

    float infinito = std::numeric_limits<float>::infinity();
    float c = uni(0, infinito, n, ex);
    cout << "Integral unidimensional de e^-x(): " << c << "\n" << endl;

    //integrais multidimensionais
    cout << "Aproximacao do valor de pi: " << multi(n) << endl;
    
    return;
}

int main(){
    
    cout<< "Parte 1: Computando o trabalho\n" << endl;
    parte1();
    cout<< "Parte 2: Integracao por Monte Carlo\n" << endl;
    parte2();

    return 1;
}
