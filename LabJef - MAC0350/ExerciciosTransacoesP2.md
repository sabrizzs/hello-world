# Conceitos

# Exercícios

## GATE | GATE-CS-2014-(Set-3) | Question 65

Considere as três transações T1, T2 e T3 e os escalonamentos S1 e S2 descritos abaixo:

	T1: r1(X); r1(Z); w1(X); w1(Z)
	T2: r2(Y); r2(Z); w2(Z)
	T3: r3(Y); r3(X); w3(Y)
	S1: r1(X); r3(Y); r3(X); r2(Y); r2(Z); w3(Y); w2(Z); r1(Z); w1(X); w1(Z)
	S2: r1(X); r3(Y); r2(Y); r3(X); r1(Z); r2(Z); w3(Y); w1(X); w2(Z); w1(Z)

Qual das seguintes afirmações sobre os esquemas é VERDADEIRA?
(A) Apenas S1 é seriável.
(B) Apenas S2 é seriável.
(C) Ambos S1 e S2 são seriáveis.
(D) Nem S1 nem S2 são seriáveis.

Resposta: (A)

Explicação: Para serialização de conflito de um escalonamento, devemos verificar as operações de conflito, que são leitura-gravação, gravação-leitura e gravação-gravação entre cada par de transações e, com base nesses conflitos, faça um gráfico de precedência, se o gráfico contiver um ciclo, não é um cronograma seriável.

Para fazer um grafo de precedência: se Read(X) em Ti é seguido por Write(X) em Tj (daí um conflito), então desenhamos uma aresta de Ti para Tj (Ti -> Tj)

Se fizermos um gráfico de precedência para S1 e S2 , obteremos arestas direcionadas para S1 como T2->T1, T2->T3, T3->T1 e para S2 como T2->T1, T2->T3, T3->T1, T1->T2. Em S1 não há ciclo, mas S2 tem um ciclo. Portanto, apenas S1 é seriável.

Nota: A ordem serial para S1 é T2 -> T3 -> T1.

## P2 - 2019

Considere as três transações T1, T2 e T3 e os escalonamentos S1 e S2 descritos abaixo:

T1: r1(X); r1(Z); w1(X);

T2: r2(Z); r2(Y); w2(Z); w2(Y);

T3: r3(X); r3(Y); w3(Y);

S1: r1(X); r2(Z); r1(Z); r3(X); r3(Y); w1(X); w3(Y); r2(Y); w2(Z); w2(Y);

S2: r1(X); r2(Z); r3(X); r1(Z); r2(Y); r3(Y); w1(X); w2(Z) w3(Y); w2(Y);

a) Os escalonamentos S1 e S2 são seriáveis? Justifique. Se for o caso, determine os respectivos escalonamentos seriais.

b) Usando o algoritmo de bloqueio em duas fases para escalonar as transações T2, T3, T1 (nesta ordem), qual seria a sequência dos recursos bloqueados e qual se4ria o primeiro recurso a ser desbloqueado?
