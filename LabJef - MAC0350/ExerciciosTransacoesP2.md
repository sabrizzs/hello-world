# Conceitos

# Exercícios

**Questão 1:** Considere as três transações T1, T2 e T3 e os escalonamentos S1, S2, S3 e S4 descritos abaixo:

	T1: r1(x); w1(x);

	T2: r2(x);

	T3: r3(x); w3(x);
	
	S1: r1(x); r3(x); w1(x); r2(x); w3(x);

	S2: r1(x); r3(x); w3(x); w1(x); r2(x);

	S3: r3(x); r2(x); w3(x); r1(x); w1(x);

	S4: r3(x); r2(x); r1(x); w3(x); w1(x);

Quais escalonamentos são seriáveis?

1. Escalonamento S1:

	S1: r1(x); r3(x); w1(x); r2(x); w3(x);

Conflitos:
- r1(x) -> w3(x)
	- A transação 1 está lendo x e a transação 3 está escrevendo w, causando conflito.
- r3(x) -> w1(x)
- w1(x) -> r2(x)
- r2(x) -> w3(x)
- w1(x) -> w3(x)

Conflitos são causados quando transações diferentes estão fazendo operações de 
- leitura-gravação
	- ri[x] < wj[x], rj[x] < wi[x]
- gravação-leitura
	- wj[x] < ri[x], wi[x] < rj[x]
- gravação-gravação
	- wi[x] < wj[x], wj[x] < wi[x]

Grafo de precedência:

![image](https://github.com/sabrizzs/hello-world/assets/93349105/28cb67cd-d94e-46da-bdbe-550d07890f07)

Para cada conflito, vemos qual transação conflita com qual e desenhamos uma aresta. Por exemplo, r1(x) -> w3(x) é um conflito da transação 1 com a transação 3, então criamos uma aresta de T1 para T3.

Existe um ciclo no grafo, portanto S1 não é seriável.

2. Escalonamento S2:

	S2: r1(x); r3(x); w3(x); w1(x); r2(x);

Conflitos:
- r1(x) -> w3(x)
- r3(x) -> w1(x)
- w3(x) -> w1(x)
- w1(x) -> r2(x)
- w3(x) -> r2(x)

Grafo de precedência:

![image](https://github.com/sabrizzs/hello-world/assets/93349105/5b481f18-b913-4de0-b998-ee70171b469a)

Existe um ciclo no grafo, portanto S2 não é seriável.

3. Escalonamento S3:

	S3: r3(x); r2(x); w3(x); r1(x); w1(x);

Conflitos:
- r3(x) -> w1(x)
- r2(x) -> w3(x)
- r2(x) -> w1(x)
- w3(x) -> r1(x)
- w3(x) -> w1(x)

Grafo de precedência:

![image](https://github.com/sabrizzs/hello-world/assets/93349105/302dc20d-9d00-4aa7-83ba-15dfdd7e6ba1)

Não existe um ciclo no grafo, portanto S3 é seriável.

Nota: A ordem serial para S3 é T2 -> T3 -> T1.

4. Escalonamento S4:

	S4: r3(x); r2(x); r1(x); w3(x); w1(x);

Conflitos:
- r3(x) -> w1(x)
- r2(x) -> w3(x)
- r2(x) -> w1(x)
- r1(x) -> w3(x)
- w3(x) -> w1(x)

Grafo de precedência:

![image](https://github.com/sabrizzs/hello-world/assets/93349105/b6cce0d3-15c5-479d-a268-bfccec863e6f)

Existe um ciclo no grafo, portanto S4 não é seriável.

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

1. Escalonamento S1:

	r1(X); r3(Y); r3(X); r2(Y); r2(Z); w3(Y); w2(Z); r1(Z); w1(X); w1(Z)

Conflitos:
- r3(X) -> w1(X)
- r2(Y) -> w3(Y)
- r2(Z) -> w1(Z)
- w2(Z) -> r1(Z)
- w2(Z) -> w1(Z)

Grafo de precdência:

![image](https://github.com/sabrizzs/hello-world/assets/93349105/7c580be6-065a-483d-9ffb-61c9da40dd7f)

Não existe ciclo no grafo, portanto S1 é seriável.

Nota: A ordem serial para S1 é T2 -> T3 -> T1.

2. Escalonamento S2:

	S2: r1(X); r3(Y); r2(Y); r3(X); r1(Z); r2(Z); w3(Y); w1(X); w2(Z); w1(Z)

Conflitos:
- r2(Y) -> w3(Y)
- r3(X) -> w1(X)
- r1(Z) -> w2(Z)
- r2(Z) -> w1(Z)
- w2(Z) -> w1(Z)

Grafo de precedência:

![image](https://github.com/sabrizzs/hello-world/assets/93349105/9f98999b-c901-448a-959a-7e931bfe5bda)

Há um ciclo no grafo, portanto S2 não é seriável.

Resposta: (A)

## P2 - 2019

Considere as três transações T1, T2 e T3 e os escalonamentos S1 e S2 descritos abaixo:

	T1: r1(X); r1(Z); w1(X);

	T2: r2(Z); r2(Y); w2(Z); w2(Y);

	T3: r3(X); r3(Y); w3(Y);

	S1: r1(X); r2(Z); r1(Z); r3(X); r3(Y); w1(X); w3(Y); r2(Y); w2(Z); w2(Y);

	S2: r1(X); r2(Z); r3(X); r1(Z); r2(Y); r3(Y); w1(X); w2(Z) w3(Y); w2(Y);

a) Os escalonamentos S1 e S2 são seriáveis? Justifique. Se for o caso, determine os respectivos escalonamentos seriais.

b) Usando o algoritmo de bloqueio em duas fases para escalonar as transações T2, T3, T1 (nesta ordem), qual seria a sequência dos recursos bloqueados e qual se4ria o primeiro recurso a ser desbloqueado?
