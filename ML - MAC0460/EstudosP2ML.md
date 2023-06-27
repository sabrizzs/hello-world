# Machine Learning

- Aulas da Nina: https://edisciplinas.usp.br/course/view.php?id=86532
- Aulas do livro Learning from Data: https://edisciplinas.usp.br/course/view.php?id=73852

- Learning From Data, Mostafa: https://edisciplinas.usp.br/pluginfile.php/7566295/mod_resource/content/1/learningrf.pdf
- Python Machine Learning, Sebastian

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

- 
