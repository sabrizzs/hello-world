# EP3-MAC210

<h3>Integrantes:

Sabrina Araújo     NUSP: 12566182

Samantha Miyahira NUSP: 11797261


## Parte 1 : Computando Trabalho

### Interpolação por Newton

### Integração numérica utilizando a regra do trapézio composto

### Integração numérica utilizando a regra de Simpson composto



## Parte 2: Integração por Monte Carlo

### Integrais unidimensionais
A integração por Monte Carlo utilizada consiste em inscrever a função que desejamos integrar em uma forma geométrica, nesse caso um retângulo, e depois estimar a proporção entre área abaixo da curva da função e a área total da forma.

No algoritmo, calculamos o valor máximo H que a função pode ter e a partir disso obtemos a área do retângulo em que a função está inscrita. Então, geramos n pontos x ($x ∈ [a, b]$) e y ($y ∈ [0, H]$) dentro desse retângulo com distribuição uniforme em [0,1]. Para (x,y) gerado, se $y \leq  f(x)$, então o ponto está abaixo ou em $f(x)$ e somamos em um o número de pontos em/ou embaixo de $f(x)$ e o número de pontos no retângulo. Caso contrário, somente somamos o número de pontos no retângulo. Ao final da iteração, calculamos a proporção entre o número de pontos em/ou embaixo de $f(x)$ e o número de pontos no retângulo, e multiplicamos pela área do retângulo ((b-a)*H), assim, temos o valor aproximado da integral.

$\int_{a}^{b}f(x)dx \approx \frac{número de pontos em/ou embaixo de f(x)}{número de pontos no retângulo}(b-a)H$

Utilizando o método das integrais unidimensionais, com n = 1000000, obtivemos as aproximações:
1. $\int_{0}^{1}sin(x)dx \approx 0.459453$

![saída do programa](https://i.imgur.com/ZgN3Mlt.png)

2. $\int_{3}^{7}x^3dx \approx 573.526$

![image](https://i.imgur.com/qvKrIGK.png)

3. $\int_{0}^{\infty }e^-xdx \approx 1$

![image](https://i.imgur.com/EjUTv1U.png)

### Integrais multidimensionais
Para o caso de aproximar o valor de π, utilizamos o método das integrais multidimensionais. Similar à ideia das integrais unidimensionais, a ideia é gerar pontos (x,y), a partir de uma distribuição uniforme em [0,1], dentro de um quadrado no qual tem um círculo inscrito. Então, se $x^2+y^2 \leq 1$ o algoritmo incrementa o número de pontos dentro do círculo e o número de pontos dentro do quadrado, caso contrário, incrementa somente o número de pontos no quadrado.

Temos que: 
$\frac{area do circulo}{area do quadrado}=\frac{\pi r^2}{4r^2}=\frac{\pi}{4}$

Assim, estimamos $\pi$ por: 
$\frac{\pi}{4}=\frac{numero de pontos no circulo}{numero de pontos no quadrado}$

Utilizando o método das integrais multidimensionais, com n = 1000000, obtivemos a aproximação:

4. Aproximar o valor de π
