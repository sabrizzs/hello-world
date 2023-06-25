# Conceitos

## 1NF

- **Atributos atômicos**
- Sem repetição de grupos de atributos
- Cada coluna deve ter um nome único.
- A ordem das tuplas não importa.

## 2NF

- Deve satisfazer os requisitos da 1NF.
- **Todos os atributos não-chave devem depender completamente da chave primária.**
	- Por exemplo, se a chave primária é AB, os atributos devem ser do modo AB → C (completa) e não A → D (parcial).
	- Nesse caso, é necessário decompor a relação original.

## 3NF

- Deve satisfazer os requisitos da 2NF.
- **Não deve haver dependências transitivas**, ou seja, um atributo depende de outro atributo que, por sua vez, depende da chave primária
	- Por exemplo, se a chave primária é AB, não deve existir uma dependência transistiva do modo AB → C → D
	- Nesse caso, é necessário decompor a relação original.

## BCNF
 
- Maior forma normal.
- **Todas as dependências funcionais são determinadas pela chave candidata completa.**
	- Por exemplo, se a chave primária é AB, todas as dependências devem ser do modo AB → C, AB → D...

### Dependência funcional A → B

Por exemplo, na dependência funcional AB → C, os atributos AB são os atributos determinantes, enquanto o atributo C é o atributo determinado funcionalmente. Isso indica que o valor de C é determinado pelos valores de A e B.

### Atributos atômicos

Na relação R={A,B,C,D,E,F,G,H,I,J}, todos os atributos são atômicos, pois cada atributo representa uma única informação. Não há agrupamento de atributos ou conjuntos de valores.

Na segunda relação R={(A,B),C,D,E,F,G,H,I,J}, o atributo (A,B) é um conjunto de valores que representa uma informação composta. Nesse caso, a relação não atende ao requisito de atomicidade, pois o atributo (A,B) contém um grupo de atributos.

Portanto, a primeira relação R={A,B,C,D,E,F,G,H,I,J} está na primeira forma normal (1NF), enquanto a segunda relação R={(A,B),C,D,E,F,G,H,I,J} não está na 1NF devido à presença de um grupo de atributos.

###  Repetição de grupos de atributos

Vamos considerar a relação R={A, B, C, D, E, F, G, H, I, J} e supor que temos uma repetição de grupos de atributos. Um exemplo seria:

R = {(A, B, C, D, E, F), (A, B, C, D, E, G), (A, B, C, D, E, H), (A, B, C, D, E, I), (A, B, C, D, E, J)}

Nesse exemplo, podemos observar que os atributos A, B, C, D e E se repetem em todas as tuplas da relação, formando um grupo de atributos repetido.

# Exercícios

## exercicios-normalizacao.pdf

**1.Considere a relação R(A, B, C, D, E) com as seguintes dependências:**

	AB → C, CD → E, DE → B

**AB é Chave candidata? Se não, e ABD?**

Para determinar se AB é uma chave candidata, precisamos calcular o fechamento de AB (AB+). Se o fechamento de AB contiver todos os atributos da relação, então AB é uma chave candidata.

Para AB:

	AB+ = {AB}
	AB → C: o lado esquerdo (AB) está no conjunto atual (AB), então adicionamos C no conjunto.
 	AB+ = {ABC}
  	CD → E: o lado esquerdo não está no conjunto, não adiciona E.
   	DE → B: o lado esquerdo não está no conjunto, não adiciona B.

Como o fechamento não contém todos os atributos da relação, AB não é chave. 

Para ABD:

	ABD+ = {ABD}
 	AB → C: o lado esquerdo está no conjunto, adiciona C.
  	ABD+ = {ABCD}
   	CD → E: o lado esquerdo está no conjunto, adiciona E.
	ABD+ = {ABCDE}

Como o fechamento contém todos os atributos da relação, ABD é uma chave candidata.

Calculando o fechamento de AB:
AB+ = {A, B, C}

**2. Considere a relação R (A, B, C, D, E, F, G, H, I, J) e o conjunto de dependências F = { AB → C, A → DE, B → F, F → GH, D → IJ}. Qual a chave de R? Decomponha R na 2NF e depois na 3NF.**

AB+ = {ABCDEFGHIJ}, AB é chave pois contém todos os atributos da relação.

A relação R não está na segunda forma normal já que existem atibutos que depende de partes da chave, a saber, A → DE, B → F.

Para satisfazer a 2NF devemos então decompor R em três relações, ou seja, dividimos a relação original de forma que os atributos que dependem parcialmente da chave se transformem em chaves da própria relação: 

- R1(**A**, **B**, C)
- R2(**B**, F, G, H)
- R3(**A**, D, E, I, J)

Essas relações são com base em, respectivamente:

- AB → C
- B → F, F → GH
- A → DE, D → IJ

Agora nas três relações todos os atributos dependem totalmente da chave. 

Contundo R2 e R3 não satisfazem a 3NF, pois existem dependências transitivas: B → F e F → GH em R2 e A → D e D → IJ em R3, ou seja, um atributo depende de outro atributo que, por sua vez, depende da chave primária.

- Em R2, o atributo F depende funcionalmente do atributo B e, por sua vez, o atributo GH depende funcionalmente do atributo F. Essa cadeia de dependências funcionais **B → F → GH** é uma dependência transitiva.

- Em R3, o atributo D depende funcionalmente do atributo A e, por sua vez, os atributos IJ dependem funcionalmente do atributo D. Essa cadeia de dependências funcionais **A → D → IJ** é uma dependência transitiva.

Para resolver essas dependências transitivas devemos entao decompor R2 e R3 da seguinte forma:

- R21(**B**, F)
- R22(**F**, G, H)
- R31(**A**, D, E)
- R32(**D**, I, J)

Mais uma vez dividimos a relação original, mas agora de forma que os atributos que dependem da chave primária e possuem outros atributos se transformem em chaves da própria relação.

Não existem mais dependências transitivas nas relações resultantes portanto o esquema está normalizado.

## P2 - 2019

**3) Considere a relação genérica R={A,B,C,D,E,F,G,H,I,J} e o conjunto de dependencias funcionais F: AB -> C; A -> DE; B -> F; F -> GH; D -> IJ**

**a) Em que forma normal está a relação R? Justifique.**

**b) Considerando apenas as formas normais 1NF, 2NF, 3NF e BCNF, normaliza a relação R até a mais alta forma normal possível**






