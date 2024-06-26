# Machine Learning

- Aulas da Nina: https://edisciplinas.usp.br/course/view.php?id=86532
- Aulas do livro Learning from Data: https://www.youtube.com/watch?v=mbyG85GZ0PI&list=PLD63A284B7615313A&ab_channel=caltech

- Learning From Data, Mostafa: https://edisciplinas.usp.br/pluginfile.php/7566295/mod_resource/content/1/learningrf.pdf
- Python Machine Learning, Sebastian

- SVM https://www.youtube.com/watch?v=eHsErlPJWUU&list=PLD63A284B7615313A&index=14&ab_channel=caltech

## Dúvidas

- É importante saber as contas do gradiente de Ein?
  - Descobri por conta própria que é importante para o algoritmo da regressão linear

## Conceitos anteriores

- Com um conjunto de hipóteses pequeno é esperado que a função alvo esteja distante, assim tem um bias grande (suposições simples).
- Se o conjunto for grande, o bias será pequeno ou nenhum (se ajusta melhor aos dados de treinamento), mas a variância dependerá da hipótese.
  - Variância: sensibilidade do modelo às variações nos dados de treinamento.
  - Bias: diferença sistemática entre as previsões do modelo e os valores reais da variável-alvo. 

## Learning curves

Como Ein e Eout varia com N:

![image](https://github.com/sabrizzs/hello-world/assets/93349105/fe1de401-b687-4eca-b8c7-00da2cab740e)

- Desempenho da aproximação apenas dentro da amostra
- Quanto maior o tamanho da amostra menor é o Eout
  - Com mais exemplos para aprender, é provável um melhor desempenho fora da amostra
- Quanto menor o tamanho da amostra menor o Ein
  -  Com menos exemplos há sempre os mesmos recursos para ajustar, então se ajusta melhor
- Erro de generalização: diferença entre Eout e Ein

![image](https://github.com/sabrizzs/hello-world/assets/93349105/79d18d7e-c9cf-4b17-9864-d854bbc33ce8)

- Como a sua melhor hipótese aproxima o alvo

![image](https://github.com/sabrizzs/hello-world/assets/93349105/375f16f0-16f5-405b-9363-99c179bb726a)

- O número de exemplos necessários para atingir um certo desempenho é proporcional à dimensão VC.

- Linear classification
   - Perceptrons
- Linear regression
   - one step learning

![Alt text](image-18.png)

## Regressão Linear

capítulo 3, página 82 (Mostafa)
videoaula: https://youtu.be/FIbVs5GbBlQ?t=1299

- Regressão: saída com valor real.
- Função real: problema de regressão.

### Exemplo 

Digamos que você gostaria de relacionar o seu desempenho em diferentes tipos de disciplinas aos seus ganhos futuros. E você obteve um grau (nota) em cada uma delas. Após 10 anos após a graduação observamos a sua renda anual.

Assim, as entradas são os graus das disciplinas, no momento em que você se formou. A saída é quanto dinheiro você ganha por ano, 10 anos depois.

Pergunta: como estas variáveis afetam a saída?

Aplicando a regressão linear podemos analisar quais disciplinas foram mais importantes para o resultado 10 anos depois.

### Exemplo do crédito

- Classificação: aprovação de crédito (yes/no)
- Regressão: limite de crédito (depende da entrada)
- Input: x = dados do cliente
- Output da regressão linear: h(x)
  
![image](https://github.com/sabrizzs/hello-world/assets/93349105/58a4175f-c799-448d-af7e-57cd3606bdf5)

- É regressão pois a saída é real
- É regressão linear pois a forma em termos da entrada é linear
- Anteriormente lidamos com h(x) como sendo -1 e +1, agora não limitamos a saída e consideramos h(x) como um número real.
- É importante que seja linear e resulte em um vetor (algoritmo).

### Error

Em regressão linear usamos o erro quadrático

![image](https://github.com/sabrizzs/hello-world/assets/93349105/432cd9e3-5bc0-4792-82b9-24a5cce347a3)

- Antes o erro era binário (acertou ou não), a frequência era calculada para obter Ein e Eout.
- Agora medimos o "quão boa ou ruim a situação é".
- Medida de erro: erro quadrático.
- h depende de w.
- MSE (Mean Squared Error).

![image](https://github.com/sabrizzs/hello-world/assets/93349105/a611379f-b5c9-4b98-a9ef-e9f74d4b1b19)

- O algoritmo deve diminuir esse erro.

### Illustration of linear regression

- Exemplo das notas daqui 10 anos
- Nota geral = x
- Ganhos daqui 10 anos = y
- Regressão linear tenta produzir uma reta que tenta se ajustar aos dados de acordo com o erro quadrático

![image](https://github.com/sabrizzs/hello-world/assets/93349105/0c85c684-6564-4b63-9757-e16280d316dc)


- Threshold depende do w0 e inclinação depende do w1 (peso para o x).
- Soma dos erros em vermelho é a MSE
- Regressão linear pode ser aplicada a mais de uma dimensão:

![image](https://github.com/sabrizzs/hello-world/assets/93349105/17e0ae6c-9b78-4c13-a584-3b18481936c0)

- Em geral, quando se considera um espaço de dimensão superior, a "linha" não é realmente uma reta é um hiperplano, uma dimensão a menos que o espaço que está sendo trabalhado.

### Erro interno (Ein)

![Alt text](images/image-4.png)

- Expressão analítica que queremos minimizar
- Do Ein derivamos o algoritmo de regressão linear

![Alt text](images/image1.png)

- Como é uma regressão linear, o valor h(xn) é w transposto xn (função linear do xn).

![Alt text](images/image2.png)

- Forma vetorial:

![Alt text](images/image.png)

- Colocamos os vetores xn em uma matriz e os yn em um vetor
- O yi é a saída de cada vetor xi

![Alt text](images/image-1.png)

- X é uma matriz muito alta

#### Minimização do Ein

- Estamos apenas variando **w**, Ein depende de w
- Para tentar minimizar:
  - obtemos a derivada e igualamos a 0
  - derivada conhecida como **gradiente**

  ![Alt text](image.png)

  - gradiente é a derivada de vários Ein, todos de uma vez
  - vetor de 0, todas as derivadas são zero de uma vez
  - isto vai definir um ponto em que essa expressão atinge um mínimo

![Alt text](images/image-2.png)

- Para que os termos nos parenteses se cancelem e a derivada seja zero temos:

![Alt text](images/image-3.png)

- Ordenando essa igualdade temos o valor de w, que é o que procuramos

![Alt text](images/image-5.png)

### Learning Algorith da Regressão Linear - Adaline

![Alt text](images/image-6.png)

### Generalization issues
- Procurar o vetor w na regressão linear garante um Eout decente? A resposta é sim.
- Existe uma versão da regressão linear do VC generalization bound

![Alt text](images/image-9.png)

### Linear regression for classification

- A regressão linear aprende uma função real
- Funções binárias (funções de classificação) também são funções reais (-1 e +1 são números reais)
- Usamos regressão linear e verificamos se o conjunto de soluções está próximo do conjunto yn em questão de sinais positivo e negativo

![Alt text](images/image-8.png)

- O classificador final é obtido depois de um threshold

![Alt text](images/image-7.png)

- Perceptron é lento, pois usa um w aleatório até chegar à região de interesse para convergir
- Então podemos usar a regressão linear para obter os w's, que são razoáveis mas não estão realmente adaptados para classificação, mas são bons para iniciar

## Regressão Logística

videoaula: https://youtu.be/qSTHZvN8hzs?t=1442

### Comparando modelos lineares

- Ser linear significa que nós consideramos as suas entradas, calculamos um sinal s que é uma combinação linear da entrada com pesos, e então eu considero o s e efetuo uma operação nele.

![Alt text](images/image-10.png)

- A operação poderia ser a **classificação linear** (os perceptrons). 
  - A hipótese é uma decisão +1 ou -1 e essa decisão é um limiar direto do sinal com relação ao zero.

![Alt text](images/image-11.png)

![Alt text](images/image-12.png)

- Também poderia ser a **regressão logística** (Adaline). 
  - Não fazemos nada com o sinal, deixamos o valor original em número real

![Alt text](images/image-13.png)

- E agora temos a **regressão logística**. 
  - Consideramos o s e aplicamos uma não linearidade a ele. 
  - A não linearidade (teta) não é tão rígida quanto a classificação linear, é algo entre a classificação linear e a regressão linear
  - Devolve um valor real
  - A saída será interpretada como uma probabilidade

![Alt text](images/image-14.png)

### The logistic function Θ

stopped: https://youtu.be/qSTHZvN8hzs?t=1661

![Alt text](image-1.png)

- probabilidade 0 quanto mais a esquerda (negativo) e 1 quanto mais a direita (positivo), e metade caso for 0

![Alt text](image-2.png)

- se 's' for grande será próximo de 1, se for negativo será próximo de 0
- soft threshold: incerteza
- sigmoid

### Interpretação da probabilidade

![Alt text](image-3.png)

- exemplo: predição de ataques cardíacos, probabilidade de ter envolve vários fatores, não é sim ou não

### Probabilidade genuína

![Alt text](image-4.png)

- quero aprender f(x)

![Alt text](image-5.png)

![Alt text](image-6.png)

### Error measure

- y é -1 e 1
- verossimilhança
  - avaliar diferentes hipóteses de acordo com a verossimilhança de que elas sejam, na verdade, a função alvo que gerou os dados
- qual a probabilidade de gerar esses dados se a sua suposição for verdadeira? probabilidade pequena = solução ruim
- qual a probabilidade dos dados dada a hipótese
- dado o conjunto de dados, quão provável é essa hipótese?
- qual a probabilidade desse conjunto de dados, sob a suposição de que esta hipótese seja, de fato, o alvo?

![Alt text](image-8.png)
![Alt text](image-7.png)

- supondo que h seja a f, calcule a probabilidade e o resultado será a verossimilhança da hipótese dado um ponto (x,y)

### Fórmula da verosimilhança

- +b

![Alt text](image-9.png)

- Probabilidade de obter o DataSet: verossimilhança
- multiplica a verossimilhança individual por todo o dataset

![Alt text](image-10.png)

- o w reflete todo o dataset

### Maximizando a verossimilhança

- a maximização da verossimilhança se traduz para a minimização de uma medida de erro
- maximizamos em relação ao vetor wT
- fazemos várias contas estranhas e a verossimilhança é traduzida como o Ein

![Alt text](image-11.png) -> ![Alt text](image-12.png)

![Alt text](image-13.png)

- medida de erro entre a minha hipótese, que depende do w, aplicada ao xn e ao yn
- maximizar a verossimilhança é como minimizar o erro dentro da amostra (Ein)
- o w é a pontuação de risco, se for muito positivo é muito provável, se for negativo é muito improvável
  - conclusão com base no valor de yn
  - se wT é positivo e yn for +1, então a expressão (-yn wT xn) é muito negativa, portanto 'e' será muito pequeno e a contribuição para o erro é pequena, as previsões estão certas
  - se o sinal for direfente: se wT for muito positivo e yn for -1, ou o contrário, a exponencial será positiva e o erro será enorme

### Learning algorithm

- como posso minimizar o Ein?
- solução iterativa
- medida de erro para a regressão logística:

![Alt text](image-14.png)

- função convexa tem um mínimo
- gradiente descendente: método geral para otimização não linear
- inicia em um ponto w(0)
- dá um passo (pequeno) e tenta achar uma melhoria
- queremos achar o mínimo Ein através da escolha apropriada do w
- n + coeficiente de aprendizagem: varia do quão perto está do mínimo

![Alt text](image-15.png)
![Alt text](image-16.png)

- retorna pesos w

## SVM - Support Vector Machines

videoaula: https://www.youtube.com/watch?v=eHsErlPJWUU&list=PLD63A284B7615313A&index=14&ab_channel=caltech

- método de classificação mais bem sucedido em ML
- conjunto de dados linearmente separável
- existe vantagem de escolher uma linha ou outra?
- margem de erro nas retas, queremos obter a melhor

![Alt text](image-19.png)

- qual 'w' maximiza a margem?

- vamos analisar as dicotomias e as suas margens

![Alt text](image-20.png)

- margens maiores implicam menos dicotomias possíveis, restringimos a função de crescimento, resulta em uma dimensão VC menor.

### Encontrando w com uma margem grande

- margem: distância do ponto até o plano (hiperplano)
- duas técnicas preliminares:
  - normalizar w
  - equação do plano é: wTx + b = 0

- w é ortogonal a cada vetor do plano, portanto é ortogonal ao plano
- distância entre xn e o plano

![Alt text](image-22.png)

![Alt text](image-23.png)

### Problema da otimização

![Alt text](image-24.png)

- trocamos a fórmula para não usar o min

![Alt text](image-26.png)

- obteremos o plano de separação com a melhor margem possível ao maximizar
- estamos tentando minimizar wTw (w^2) e a restrição é Ein

### Programa quadrático

- os alphas minizimizam a função

![Alt text](image-27.png)

- o programa quadrático devolve um vetor de alphas
- os alphas são >= 0
- o vetor de alphas que estão exatamente na borda da margem é chamado de vetor suporte

![Alt text](image-28.png)

![Alt text](image-29.png)

![Alt text](image-30.png)

- os alphas que não estão na borda tem alpha = 0

- com o vetor de alphas obtemos o vetor w

![Alt text](image-31.png)

- agora podemos encontrar b (bias)
  - consideramos qualquer vetor de suporte e para qualquer um temos a equação válida:

  ![Alt text](image-32.png)

