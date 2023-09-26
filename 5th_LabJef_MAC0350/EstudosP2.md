# P2 - LABJEF MAC0350

Assuntos cobrados:
- Consultas: álgebra relacional, cálculo relacional e SQL
- Normalização
- Transações 
- Seriabilidade (?)

## Sumário

- [SQL](#sql)
  - [Conceitos](#conceitos)
  - [Tipos de dados](#tipos-de-dados)
  - [DDL](#ddl)
    - [Criação do Esquema](#criação-do-esquema)
    - [Criação de Domínios](#criação-de-domínios)
    - [Criação de Tabelas](#criação-de-tabelas)
    - [Alteração de Tabela](#alteração-de-tabela)
    - [Remoção de Tabela](#remoção-de-tabela)
    - [Remoção de Esquema](#remoção-de-esquema)
  - [DML](#dml)
    - [Inserção](#inserção)
    - [Alteração](#alteração)
    - [Remoção](#remoção)
    - [Consulta](#consulta)
    - [Consulta Simples](#consulta-simples)
    - [Consulta com um Join](#consulta-com-um-join)
    - [Consulta com dois Joins](#consulta-com-dois-joins)
  - [Qualificando um Atributo](#qualificando-um-atributo)
  - [ALIASES](#aliases)
  - [Cláusula WHERE não especificada](#clausula-where-nao-especificada)
  - [O Uso do *](#o-uso-do-*)
  - [Uso do DISTINCT](#uso-do-distinct)
  - [Operação de Conjunto](#operação-de-conjunto)
  - [Consultas Aninhadas](#consultas-aninhadas)
  - [Consultas Aninhadas Correlacionadas](#consultas-aninhadas-correlacionadas)
  - [Conjuntos Explícitos](#conjuntos-explícitos)
  - [Divisão em SQL](#divisão-em-sql)
  - [Valores Nulos em Consultas SQL](#valores-nulos-em-consultas-sql)
  - [Junção de Relações](#junção-de-relações)
  - [Funções Agregadas](#funções-agregadas)
  - [Agrupamento](#agrupamento)
  - [A Cláusula HAVING](#a-clausula-having)
  - [Comparação de Substrings](#comparação-de-substrings)
  - [Operações Aritméticas](#operações-aritméticas)
  - [Order By](#order-by)
- [Normalização de Banco de Dados](#normalização-de-banco-de-dados)
- [Transações](#transações)
- [Temas que (talvez) não serão cobrados na P2](#temas-que-talvez-não-serão-cobrados-na-p2)

# SQL

https://www.ime.usp.br/~jef/bd08.pdf

## Conceitos

- Linguagem declarativa – não-procedimental.
- Padrão industrial que atinge grande parte do mercado de SGBDs.
- Atrativo: pequena quantidade de comandos para realizar uma grande quantidade de operações necessárias para definição e manipulação de relações.
- Simplicidade.
- Grande poder de consulta.
- Padrão facilita migração.
- Dois conjuntos principais de comandos:
  - DDL – Data Definition Language: usada para especificar e definir a estrutura e o esquema da base de dados.
  - DML – Data Manipulation Language: usada para manipular os dados dentro da base de dados.

## Tipos de dados

Tipos de dados comumente usados em SQL:

- INTEGER: Um número inteiro.
- SMALLINT: Um número inteiro pequeno.
- DECIMAL(precision, scale): Um número decimal com precisão e escala especificadas. Precision é o número total de dígitos e scale é o número de dígitos após o ponto decimal.
- DOUBLE PRECISION | FLOAT | REAL: Números de ponto flutuante com diferentes níveis de precisão.
- CHAR(n): Uma sequência de caracteres de tamanho fixo, com comprimento especificado por n.
- VARCHAR(n): Uma sequência de caracteres de tamanho variável, com comprimento máximo especificado por n.
- BLOB: Um objeto binário grande que pode armazenar dados binários, como imagens ou arquivos.
- DATE: Uma data, no formato AAAA-MM-DD.
- TIME: Uma hora, no formato HH:MM:SS.
- TIMESTAMP: Uma combinação de data e hora, no formato AAAA-MM-DD HH:MM:SS.

## DDL

- A linguagem de definição de dados (DDL) é usada para especificar e definir a estrutura e o esquema da base de dados. 
- Os comandos DDL são usados para criar, modificar e excluir objetos de banco de dados, como tabelas, índices, restrições, visões, procedimentos armazenados, funções, entre outros.

Exemplos de comandos DDL (Data Definition Language) no SQL:

- CREATE SCHEMA: cria um novo esquema de banco de dados.
- CREATE TABLE: cria uma nova tabela no banco de dados.
- ALTER TABLE: modifica a estrutura de uma tabela existente.
- DROP TABLE: exclui uma tabela existente do banco de dados.
- CREATE DOMAIN: cria um novo domínio, que define um tipo de dado personalizado.
- DROP DOMAIN: exclui um domínio existente do banco de dados.
- CREATE VIEW: cria uma visão, que é uma representação virtual de uma ou mais tabelas.
- DROP VIEW: exclui uma visão existente do banco de dados.
- CREATE INDEX: cria um índice em uma ou mais colunas de uma tabela, para melhorar o desempenho das consultas.
- DROP INDEX: exclui um índice existente do banco de dados.

### Criação do Esquema

- **CREATE SCHEMA** – Comando utilizado para criar esquemas de aplicações.
- O esquema permite agrupar as tabelas, restrições, visões, domínios e outros construtores (como concessão de autoridade) que descrevem o esquema.
  
Por exemplo:

	CREATE SCHEMA COMPANHIA AUTHORIZATION MAC0426;

O comando CREATE SCHEMA está sendo usado para criar um esquema chamado "COMPANHIA" e atribuir a autoridade ou permissões ao usuário "MAC0426" para acessar e modificar os objetos dentro desse esquema. 

### Criação de Domínios

- **CREATE DOMAIN** - utilizado para criar domínios de atributos, ou seja, para definir tipos de dados personalizados que podem ser usados em colunas de tabelas.
- O uso de domínios pode facilitar a redefinição de tipos de dados utilizados por muitos atributos de um esquema, tornando o esquema mais legível e de fácil manutenção.

Sintaxe básica:

**CREATE DOMAIN nome AS tipo [restrições de coluna];**

- "nome" é o nome dado ao domínio que está sendo criado.
- "tipo" é o tipo de dado que o domínio irá representar, como CHAR, VARCHAR, INTEGER, etc.
- "restrições de coluna" são opcionais e podem ser adicionadas para impor restrições adicionais ao domínio, como tamanho máximo, valores padrão, restrições de nulos, entre outras.

Por exemplo:

	CREATE DOMAIN TIPO_NSS AS CHAR(9);

No exemplo dado, o comando CREATE DOMAIN está sendo usado para criar um domínio chamado "TIPO_NSS" com o tipo de dado CHAR(9) com 9 caracteres de comprimento.

- Pode-se definir um novo domínio com a especificação de uma restrição sobre o tipo de dados.
  
Por exemplo:

	CREATE DOMAIN TIPO_DEPNUM AS INTEGER

		CHECK (TIPO_DEPNUM > 0 AND TIPO_DEPNUM < 21);

No exemplo, o comando CREATE DOMAIN está sendo usado para criar um domínio chamado "TIPO_DEPNUM" com o tipo de dado INTEGER. Além disso, uma restrição está sendo adicionada através da cláusula CHECK. A restrição especifica que o valor do domínio "TIPO_DEPNUM" deve ser maior que 0 e menor que 21.

### Criação de Tabelas

- **CREATE TABLE** - cria uma tabela (tabela base), e define colunas e restrições.

Restrições de colunas:
- NOT NULL: especifica que a coluna não pode conter valores nulos.
- DEFAULT valor: define um valor padrão para a coluna quando nenhum valor é especificado durante a inserção.
- CHECK(condição): define uma condição que deve ser satisfeita para os valores da coluna.

Restrições de tabela:
- PRIMARY KEY (<atributos chave primária>): define a(s) coluna(s) como chave primária da tabela.
- UNIQUE (<atributos chave candidata>): especifica que os valores nas colunas devem ser únicos.
- FOREIGN KEY (<atributos chave estrangeira>)
	- REFERENCES tabelaRef [(<chave primária>)] [<ações>]: cria uma chave estrangeira que faz referência a uma tabela externa.

<ações>
- As cláusulas ON DELETE e ON UPDATE são usadas em conjunto com as ações CASCADE, SET NULL e SET DEFAULT.
- ON DELETE CASCADE: Quando uma linha na tabela referenciada é excluída, todas as linhas correspondentes na tabela atual também serão excluídas.
- ON DELETE SET NULL: Quando uma linha na tabela referenciada é excluída, o valor das colunas correspondentes na tabela atual será definido como NULL.
- ON DELETE SET DEFAULT: Quando uma linha na tabela referenciada é excluída, o valor das colunas correspondentes na tabela atual será definido como o valor padrão especificado.
- CHECK(condição): define uma condição que deve ser satisfeita para as tuplas da tabela.

Sintaxe básica:

	CREATE TABLE [esquema].tabela(
		atrib1 tipo [(tamanho)] [NOT NULL | DEFAULT valor]
			[CHECK (condição)],
		atrib2 tipo [(tamanho)] [NOT NULL | DEFAULT valor]
			[CHECK (condição)], 
   		...
   	);

Forma geral:

	CREATE TABLE [esquema].tabela (
		atrib1 tipo [(tamanho)] [NOT NULL | DEFAULT valor] [CHECK (condição)],
		atrib2 tipo [(tamanho)] [NOT NULL | DEFAULT valor] [CHECK (condição)], 
  		...
		[CONSTRAINT nome da restrição]
			PRIMARY KEY (<atributos chave primária>),
		[CONSTRAINT nome da restrição]
			UNIQUE (< atributos chave candidata>),
		[CONSTRAINT nome da restrição]
			FOREIGN KEY (<atributos chave estrangeira>)
				REFERENCES tabelaRef [(<chave primária>)]
					[ON DELETE CASCADE | SET NULL | SET DEFAULT]
					[ON UPDATE CASCADE | SET NULL | SET DEFAULT],
		[CONSTRAINT nome da restrição]
			CHECK (condição)
	);

Por exemplo:

EMPREGADO

PNOME MNOME SNOME NSS DATANASC ENDERECO SEXO SALARIO EMPREGADO NSSSUPER (ce) NDEP (ce)

	CREATE TABLE COMPANHIA.EMPREGADO (
		PNOME VARCHAR(15) NOT NULL,
		MNOME CHAR,
		SNOME VARCHAR(15) NOT NULL,
		NSS TIPO_NSS NOT NULL,
		DATANASC DATE,
		ENDERECO VARCHAR(30),
		SEXO CHAR,
		SALARIO DECIMAL(10,2),
		NSSSUPER CHAR(9),
		NDEP TIPO_DEPNUM NOT NULL,
		PRIMARY KEY (NSS),
		FOREIGN KEY (NSSSUPER) REFERENCES EMPREGADO(NSS),
		FOREIGN KEY (NDEP) REFERENCES DEPARTAMENTO(DNUMERO)
	);

### Alteração de Tabela

- **ALTER TABLE** – incluir/alterar/remover definições de colunas e restrições.

Sintaxe básica:

**ALTER TABLE tabela <ação>;**

<ação>:
- ADD novoAtrib tipo [<restrições de coluna>]
  	- Adiciona uma nova coluna chamada "novoAtrib" à tabela com o tipo de dado especificado. As restrições de coluna, se aplicáveis, também podem ser especificadas.
  	-  E o valor do novo atributo nas tuplas já existentes? Se não for especificada nenhuma cláusula default, então o valor será null. Assim, a cláusula NOT NULL não pode ser aplicada.
  	  
Por exemplo:

	ALTER TABLE COMPANHIA.EMPREGADO
		ADD FUNCAO VARCHAR(12);

- ADD [CONSTRAIN nome] <restrição de tabela>
	- Adiciona uma nova restrição à tabela. Essa restrição pode ser uma restrição de chave primária, chave estrangeira, restrição UNIQUE, restrição CHECK ou qualquer outra restrição definida pelo usuário. O nome da restrição é opcional.

- DROP atributo [CASCADE | RESTRICT]
	- Remove uma coluna específica da tabela. A opção CASCADE indica que todas as dependências da coluna também serão removidas, enquanto a opção RESTRICT impede a exclusão se houver dependências existentes.
	- CASCADE – todas as visões e restrições (constrains) que referenciam o atributo são removidas automaticamente.
	- RESTRICT – o atributo só é removido se não houver nenhuma visão ou restrição que o referencie.

Por exemplo:

	ALTER TABLE COMPANHIA.EMPREGADO
		DROP FUNCAO CASCADE;

- DROP CONSTRAINT nome
	- Remove uma restrição específica da tabela, identificada pelo seu nome.

### Remoção de Tabela

- **DROP TABLE** - exclui uma tabela do banco de dados.

Sintaxe básica:

**DROP TABLE tabela [CASCADE | RESTRICT];**

- CASCADE: todas as visões e restrições que referenciam a tabela são removidas automaticamente.
- RESTRICT: a tabela é removida somente se não for referenciada em nenhuma restrição ou visão.

Por exemplo:

	DROP TABLE COMPANHIA.DEPENDENTE CASCADE

No exemplo, o comando exclui a tabela "DEPENDENTE" do esquema "COMPANHIA", juntamente com todas as visões e restrições associadas a ela.

### Remoção de Esquema

- **DROP SCHEMA** - exclui um esquema do banco de dados.

Sintaxe básica:

**DROP SCHEMA esquema [CASCADE | RESTRICT]**

- CASCADE: todos os elementos do esquema são removidos automaticamente
- RESTRICT: o esquema só será removido se não existir os elementos

Por exemplo:

	DROP SCHEMA COMPANHIA CASCADE;

## DML

- A linguagem de manipulação de dados (DML) é usada para manipular os dados dentro da base de dados.
- Os comandos DML são usados para inserir, atualizar, excluir e consultar dados na instância do banco de dados. 

Exemplos de comandos DML (Data Manipulation Language) no SQL:
- INSERT: É usado para inserir novos registros em uma tabela.
- UPDATE: É usado para modificar os valores existentes em uma ou mais colunas de uma tabela.
- DELETE: É usado para excluir registros de uma tabela.
- SELECT: É usado para recuperar dados de uma ou mais tabelas.

### Inserção

- INSERT – insere uma ou mais tuplas em uma tabela.

Sintaxe básica:

	- Inserção de 1 tupla:

	INSERT INTO tabela [(atrib1,atrib2,...)]
		VALUES(valor1, valor2,...)

	- Inserção de múltiplas tuplas:
 
	INSERT INTO tabela [(atrib1,atrib2,...)]
		<comando SELECT>

Por exemplo, inserção de uma única tupla:

Inserir 3 tuplas na relação PROJETO:

PROJETO

PNOME PNUMERO PLOCALIZACAO PROJETO DNUM (ce)

	INSERT INTO PROJETO VALUES ('ProductX', '1', 'Bellaire', '5')
	INSERT INTO PROJETO VALUES ('ProductY', '2', 'Sugarland', '5')
	INSERT INTO PROJETO VALUES ('ProductZ', '3', 'Houston', '5')

O terceiro valor ‘5’ corresponde ao departamento 5. Logo, o departamento 5 deve existir na relação DEPARTAMENTO para que as inserções tenham sucesso; pois caso contrário, violaria a restrição de integridade referencial.

Por exemplo, inserção de múltiplas tuplas:

Popular uma tabela temporária DEPTS_INFO:

	CREATE TABLE DEPTS_INFO (
		DEPT_NAME VARCHAR(10),
		NO_OF_EMPS INTEGER,
		TOTAL_SAL INTEGER
	);

	INSERT INTO DEPTS_INFO (DEPT_NAME, NO_OF_EMPS, TOTAL_SAL)
		SELECT DNAME, COUNT (*), SUM (SALARY)
		FROM DEPARTMENT, EMPLOYEE
		WHERE DNUMBER=DNO
		GROUP BY DNAME;

### Alteração

- **UPDATE** – modifica o valor de um atributo em uma ou mais tuplas da tabela.

Sintaxe básica:

	UPDATE tabela SET
		atributo1 = <valor ou expressão>,
		atributo2 = <valor ou expressão>, ...
	WHERE <condição de localização>;

Por exemplo:

	UPDATE PROJETO
	SET PLOCALIZACAO = 'Bellaire', DNUM = 5
	WHERE PNUMERO=10;

O atributo PLOCALIZACAO é definido como 'Bellaire' e o atributo DNUM é definido como 5 na tupla em que o atributo PNUMERO é igual a 10.

### Remoção

- **DELETE** – remove uma ou mais tuplas da tabela.

Sintaxe básica:

	DELETE FROM tabela1 [FROM tabela2]
	[WHERE<condição de localização>];

Por exemplo:

	DELETE FROM EMPREGADO
	WHERE NSS='123456789’;
 
	DELETE FROM EMPREGADO
	WHERE DNUM IN
		(SELECT DNUMERO
		FROM DEPARTAMENTO
		WHERE DNOME='Research');
	DELETE FROM EMPLOYEE;

### Consulta

- **SELECT** – Comando de consulta. 

Forma geral:

	SELECT [ DISTINCT | ALL ] <lista de atributos>
	FROM<lista de tabelas>
	[ WHERE<condições> ]
 	[ GROUP BY atributo ]
	[ HAVING<condições> ]
	[ ORDER BY atributo [ ASC | DESC ] ];

Seleciona O QUE se deseja na tabela resultado:
- <lista de atributos> ou * (para todos os atributos)
- ALL – inclui tuplas duplicadas (é o default)
- DISTINCT – elimina tuplas duplicadas
- FROM – DE ONDE retirar os dados necessários
- WHERE – CONDIÇÕES de seleção dos resultados.

### Consulta Simples

Consulta 1 – Recuperar a data de aniversário e o endereço do empregado chamado 'John B. Smith'

Em SQL:

	SELECT DATANASC, ENDERECO
	FROM EMPREGADO
	WHERE PNOME='John' AND MNOME='B’ AND SNOME='Smith’;

Em Álgebra Relacional:

	EMP_SMITH ← σ PNOME='John' AND MNOME='B’ AND SNOME='Smith’ (EMPREGADO)
	RESULTADO ← π DATANASC, ENDERECO (EMP_SMITH)

Em Cálculo Relacional de Tuplas:

	{ e.DATANASC, e.ENDERECO | EMPREGADO(E) AND
		e.PNOME='John' AND e.MNOME='B’ AND e.SNOME='Smith’ }

Assim, uma consulta com apenas uma relação na cláusula FROM é similar a um par de operações SELECT-PROJECT da Álgebra Relacional. A diferença é que podemos obter tuplas repetidas no resultado

### Consulta com um Join

Consulta 2 – Obter o nome e o endereço dos empregados que trabalham para o departamento de ‘Pesquisa’.

Em SQL:

	SELECT PNOME, ENDERECO
	FROM EMPREGADO, DEPARTAMENTO
	WHERE DNOME = ‘Pesquisa' AND DNUMERO=DNUM;

Em Álgebra Relacional:

	DEP_PESQUISA(DNUM) ← π DNUMERO (σ DNOME=‘Pesquisa’ (DEPARTAMENTO)
	RESULT ← π PNOME, ENDERECO (DEP_PESQUISA * EMPREGADO)

Em Cálculo Relacional de Tuplas: lculo Relacional de Tuplas:

	{ t.PNOME, t.ENDERECO | EMPREGADO( t ) AND ( ∃d ) (DEPARTAMENTO( d ) AND
		d.DNOME=‘Pesquisa’ AND d.DNUMERO=t.DNUM ) }

- Similar à seqüência SELECT-PROJECT-JOIN da Álgebra Relacional
- (DNOME=‘Pesquisa') é uma condição de seleção do operador SELECT da Álgebra Relacional)
- (DNUMERO=DNUM) é uma condição de junção do operador JOIN da Álgebra Relacional.

### Consulta com dois Joins

Consulta 3 - Para todo projeto localizado em 'Stafford', listar o número do projeto, o número do departamento responsável, o sobrenome, endereço e data de nascimento do gerente responsável pelo departamento. 

Em SQL:

	SELECT PNUMERO, DNUM, SNOME, DATANASC, ENDERECO
	FROM PROJETO, DEPARTAMENTO, EMPREGADO
	WHERE DNUM=DNUMERO AND GERNSS=SSN AND PLOCALIZACAO='Stafford‘;

Em Álgebra Relacional:

	STAFFORD_PROJS ← σ PLOCALIZAÇÃO = 'Stafford' (PROJETO)
	CONTR_DEPT ← (STAFFORD_PROJS x DNUM = DNUMERO DEPARTAMENTO)
	PROJ_DEPT_MGR ← (CONTR_DEPT x GERNSS = NSS EMPREGADO)
	RESULT ← π PNUMERO, DNUM, SNOME, ENDERECO, DATANASC (PROJ_DEPT_MGR) 

- Na consulta anterior, existem duas condições Join
- A condição Join DNUM=DNUMERO relaciona um projeto com o departamento que o controla
- A condição Join GERNSS=SSN relaciona o departamento com o empregado que o gerencia.

## Qualificando um atributo

- Em SQL podemos usar o mesmo nome para dois ou mais atributos, desde que os atributos estejam em relações diferentes.
- Uma consulta que referencia dois ou mais atributos com o mesmo nome deve qualificar o atributo com o nome da relação.

Por exemplo:

Em SQL:

	SELECT EMPREGADO.PNOME, PROJETO.PNOME
	FROM PROJETO, DEPARTAMENTO, EMPREGADO
	WHERE DNUM=DNUMERO AND GERNSS=SSN AND PLOCALIZACAO='Stafford‘;

## ALIASES

- Algumas consultas precisam referenciar duas vezes a mesma relação.
- Em alguns casos, pseudônimos (aliases) são atribuídos ao nome da relação.

Por exemplo:

Para cada empregado, recupere o nome do empregado e o nome de seu supervisor imediato.

Em SQL:

	SELECT E.PNOME, E.SNOME, S.PNOME, S.SNOME
	FROM EMPREGADO E S
	WHERE E.NSSSUPER=S.NSS;

- Na consulta anterior, E e S são chamados de aliases ou variáveis de tupla da relação EMPREGADO.
- Podemos pensar em E e S como duas cópias distintas de EMPREGADO: E representa os supervisionados e S representa os supervisores.
- Aliases podem ser usados em qualquer consulta SQL.
- Pode-se, também, usar a palavra-chave AS:

Em SQL:

	SELECT E.PNOME, E.SNOME, S.PNOME, S.SNOME
	FROM EMPREGADO AS E, EMPREGADO AS S
	WHERE E.NSSSUPER=S.NSS;

## Cláusula WHERE não especificada

- Uma cláusula WHERE não especificada indica ausência de uma condição.
- Assim, todas as tuplas dos relações da cláusula FROM serão selecionadas.
- Isso equivale a condição WHERE TRUE

Por exemplo:

Recupere o NSS de todos os empregados.

Em SQL:

	SELECT NSS
	FROM EMPREGADO;

Se mais de uma relação é especificada na cláusula FROM e não existir nenhuma condição de junção, então o resultado será o produto cartesiano.

Em SQL:

	SELECT NSS, DNOME
	FROM EMPREGADO, DEPARTAMENTO;

É extremamente importante não negligenciar a especificação de qualquer condição de seleção ou de junção na cláusula WHERE; sob a pena de gerar resultados incorretos e volumosos.

## O Uso do *

- Um * é usado para recuperar todos os valores de atributos da tupla selecionada.

Por exemplo:

Em SQL:

	SELECT *
	FROM EMPREGADO
	WHERE DNUM=5;
 
	SELECT *
	FROM EMPREGADO, DEPARTAMENTO
	WHERE DNOME='Research' AND DNUM=DNUMERO;

## Uso do DISTINCT

- A SQL não trata uma relação como um conjunto; tuplas duplicadas podem ocorrer.
- Para eliminar tuplas duplicadas no resultado de uma consulta, a palavra DISTINCT é usada.
- A primeira consulta abaixo pode gerar tuplas duplicadas, mas a segunda não:

Em SQL:

	SELECT SALARIO
	FROM EMPREGADO;
 
	SELECT DISTINCT SALARIO
	FROM EMPREGADO;

## Operação de Conjunto

- Algumas operações de conjunto foram incorporados à linguagem SQL.
- Existe uma operação de União e, em algumas versões da SQL, existem as operações de Subtração e Intersecção.
- As relações resultantes dessas operações são sempre conjunto de tuplas; tuplas duplicadas são eliminadas do resultado.
- O conjunto de operações aplicam-se somente às relações que são compatíveis na união.

Por exemplo:

Listar os números de projetos em que o empregado de sobrenome Smith trabalhe ou que sejam controlados por algum departamento gerenciado pelo empregado de sobrenome Smith:

Em SQL:

	( SELECT PNUMERO
	FROM PROJETO, DEPARTAMENTO, EMPREGADO
	WHERE DNUM=DNUMBER AND GERNSS=NSS AND SNOME='Smith‘ )
	UNION
 
	( SELECT PNUMERO
	FROM PROJETO, TRABALHA-PARA, EMPREGADO
	WHERE PNUMERO=PNO AND ENSS=NSS AND SNAME='Smith‘ );

A SQL também possui operações sobre multiconjuntos (conjuntos que permitem repetição de elementos)
- UNION ALL: Combina os resultados de duas consultas em um único conjunto, incluindo todas as ocorrências de cada elemento. 
- EXCEPT ALL: Retorna os elementos que estão presentes na primeira consulta, mas não estão na segunda consulta.
- INTERSECT ALL: Retorna os elementos que estão presentes tanto na primeira consulta quanto na segunda consulta.

## Consultas Aninhadas

- Uma consulta SELECT completa, chamada de consulta aninhada, pode ser especificada dentro da cláusula WHERE de uma outra consulta, chamada consulta externa.

Por exemplo:

Recupere o nome e o endereço de todos os empregados que trabalham para o departamento de Pesquisa.

Em SQL:

	SELECT PNAME, SNAME, ENDERECO
	FROM EMPREGADO
	WHERE DNUM IN ( SELECT DNUMERO
		FROM DEPARTAMENTO
		WHERE DNOME=‘Pesquisa' )

- A consulta externa seleciona tuplas de empregados se o valor de seu DNUM pertencer ao resultado da consulta aninhada
- O operador IN é equivalente ao operador pertence da teoria de conjuntos
- Em geral, podemos ter vários níveis de consultas aninhadas
- Uma referência a um atributo não qualificado estará se referindo a um atributo da relação declarada na consulta externa mais próxima
- Neste exemplo, a consulta aninhada não está correlacionado à consulta externa
- Se a condição WHERE de uma consulta aninhada referenciar um atributo de uma relação declarada na consulta externa, as consultas estarão correlacionadas

Por exemplo:

Recupere o nome de cada empregado que tenha um dependente com o mesmo nome do empregado.

Em SQL:

	SELECT E.PNOME, E.SNAME
	FROM EMPREGADO AS E
	WHERE E.NSS IN ( SELECT ENSS
		FROM DEPENDENTE
		WHERE ENSS=E.NSS AND E.PNOME=NOMEDEPENDENTE );

- Na consulta anterior, a consulta aninhada tinha um resultado diferente para cada tupla da consulta externa
- Consultas escritas com blocos SELECT-FROM-WHERE e que utilizem operadores de comparação e IN sempre podem ser expressas como uma consulta simples

Por exemplo, a mesma consulta pode ser escrita como:

Em SQL:

	SELECT E.PNOME, E.SNOME
	FROM EMPREGADO AS E, DEPENDENTE AS D
	WHERE E.NSS=D.ENSS AND E.PNOME=D.NOMEDEPENDENTE;

## Conjuntos Explícitos

É possível utilizar um conjunto de valores explicitamente enumerado na cláusula WHERE ao invés de utilizar uma consulta aninhada.

Por exemplo:

Recupere o NSS de todos os empregados que trabalham nos projetos de números 1, 2, ou 3.

Em SQL:

	SELECT DISTINCT ENSS
	FROM TRABALHA-PARA
	WHERE PNO IN (1, 2, 3);

## Divisão em SQL

Encontrar os nomes de empregados que trabalham em todos os projetos controlados pelo departamento 5

Em SQL:

	SELECTPNOME, SNOME
	FROM EMPREGADO
	WHERE ( ( SELECTPNO
		FROM TRABALHA-EM
		WHERE NSS=ENSS )
		CONTAINS
			( SELECTPNUMERO
		FROM PROJETO
		WHERE DNUM=5 ) );

- CONTAINS é equivalente ao operador de divisão da Álgebra Relacional. Infelizmente, a maioria das implementações da SQL não implementam CONTAINS.
- Para fazer essa consulta em SQL que não possua o operador CONTAINS devemos recorrer ao Cálculo Relacional de Tuplas e utilizar cláusulas EXISTS e NOT EXISTS:

Em Cálculo Relacional de Tuplas:

	{ e.PNOME, e.SNOME | EMPREGADO(e) AND
		(∀ x) ( ( PROJETO(x) AND x.DNUM=5 ) ⇒
			(∃ w) (TRABALHA-EM(w) AND
				w.ENSS=e.NSS AND
				x.PNUMERO=w.PNO) ) }

Ou, transformando o quantificador universal e a implicação temos:

Em Cálculo Relacional de Tuplas:

	{ e.PNOME, e.SNOME | EMPREGADO(e) AND
		NOT (∃ x) ( PROJETO(x) AND x.DNUM=5 AND
			NOT (∃ w) (TRABALHA-EM(w) AND
				w.ENSS=e.NSS AND
				x.PNUMERO=w.PNO) ) }

Em SQL:

	SELECT E.PNOME, E.SNOME
	FROM EMPREGADO AS E
	WHERE NOT EXISTS ( SELECT*
		FROM PROJETO X
		WHERE X.DNUM=5 AND
	NOT EXISTS ( SELECT*
		FROM TRABALHA-PARA W
		WHERE W.ENSS = E.NSS AND
		X.PNUMERO = W.PRNO ) );

## Valores Nulos em Consultas SQL

- A SQL permite que consultas verifiquem se um valor é nulo utilizando IS ou IS NOT

Por exemplo:

Recupere os nomes de todos os empregados que não possuem supervisores.

Em SQL:

	SELECT PNOME, SNOME
	FROM EMPREGADO
	WHERE NSSSUPER IS NULL;

## Junção de Relações

- Pode se especificar uma “junção de relações” na cláusula FROM.
- A junção de relações é uma relação como outra qualquer, mas é o resultado de uma junção.
- Permite que o usuário especifique tipos diferentes de junções ("theta" JOIN, NATURAL JOIN, LEFT OUTER JOIN, RIGHT OUTER JOIN, CROSS JOIN, etc).

Por exemplo:

Em SQL:

	SELECT PNOME, SNOME, ENDERECO
	FROM EMPREGADO, DEPARTAMENTO
	WHERE DNOME=‘Pesquisa' AND DNUMERO=DNUM;

Pode ser reescrito com ‘theta’ Join:

Em SQL:

	SELECT PNOME, SNOME, ENDERECO
	FROM EMPREGADO JOIN DEPARTAMENTO ON DNUMERO=DNUM
	WHERE DNOME=‘Pesquisa';

Por exemplo:

Em SQL:
	SELECT DNOME, DLOCALIZACAO
	FROM DEPARTAMENTO AS D, LOCAIS-DEPTO AS L;
	WHERE DNOME = ‘Pesquisa' AND D.DNUMERO = L.DNUMERO;

Pode ser reescrito com Natural Join:

Em SQL:

	SELECT DNOME, DLOCALIZACAO
	FROM DEPARTAMENTO NATURAL JOIN LOCAIS-DEPTO
	WHERE DNOME=‘Pesquisa';

Por exemplo:

Em SQL:

	SELECT E.PNOME, E.SNOME, S.PNOME, S.SNOME
	FROM EMPREGADO E S
	WHERE E.NSSSUPER=S.NSS;

Pode ser escrita como:

Em SQL:

	SELECT E.PNOME, E.SNOME, S.PNOME, S.SNOME
	FROM ( EMPREGADO AS E LEFT OUTER JOIN EMPREGADO AS S ON
	E.NSSSUPER=S.NSS );

PNOME de empregados que não possuem um supervisor também serão apresentados, porém com PNOME e SNOME do supervisor com valores nulos.

## Funções Agregadas

- A SQL possui as seguintes funções agregadas: COUNT, SUM, MAX, MIN e AVG

Por exemplo:

Encontrar o maior salário, o menor salário, e a média salarial de todos os empregados.

Em SQL:
	SELECT MAX(SALARIO), MIN(SALARIO), AVG(SALARIO)
	FROM EMPREGADO;

Algumas implementações da SQL não permitem mais de uma função agregada na cláusula SELECT.

Por exemplo:

Recuperar o total de empregados da companhia (Consulta A) e o número de empregados do departamento Pesquisa (Consulta B).

Em SQL (Consulta A):

	SELECT COUNT (*)
	FROM EMPREGADO;
 
Em SQL (Consulta B):

	SELECT COUNT (*)
	FROM EMPREGADO, DEPARTAMENTO
	WHERE DNUM=DNUMBER AND DNOME=‘Pesquisa’;

## Agrupamento

- Como na extensão da Álgebra Relacional, a SQL tem uma cláusula GROUP BY para especificar os atributos de agrupamento, que devem aparecer na cláusula SELECT.

Por exemplo:

Para cada departamento, recuperar o seu número, a quantidade de empregados que possui e a sua média salarial.

Em SQL:

	SELECT DNUM, COUNT (*), AVG (SALARIO)
	FROM EMPREGADO
	GROUP BY DNUM;

Por exemplo:

Para cada projeto, recuperar o número do projeto, seu nome e o número de empregados que trabalham no projeto.

Em SQL:

	SELECT PNUMERO, PNOME, COUNT (*)
	FROM PROJETO, TRABALHA-EM
	WHERE PNUMERO=PNO
	GROUP BY PNUMERO, PNOME;

Neste caso, o agrupamento e a função agregada são aplicadas após a junção das duas relações.

## A Cláusula HAVING

- Algumas vezes queremos recuperar os valores das funções agregadas que satisfaçam a certas condições
- A cláusula HAVING é usada para especificar essa condição

Por exemplo:

Para cada projeto em que trabalhem mais de dois empregados, recupere o número do projeto, o nome do projeto e o número de empregados que trabalham no projeto.

Em SQL

	SELECT PNUMERO, PNOME, COUNT SELECT COUNT(*)
	FROM PROJETO, TRABALHA-PARA
	WHERE PNUMERO=PNO
	GROUP BY PNUMERO, PNOME
	HAVING COUNT(*) > 2;

## Comparação de Substrings

- O operador de comparação LIKE é usado para comparar partes de uma string
- Os dois caracteres reservados são usados:
	- O '%' (ou '*‘ em algumas implementações) pesquisa um número arbitrário de caracteres
	- O '_‘ pesquisa um único caractere arbitrário.

Por exemplo:

Recupere todos os empregados que morem em Houston, Texas. Aqui, o valor do atributo endereço deve conter a substring 'Houston,TX'.

Em SQL

	SELECT PNOME, SNOME
	FROM EMPREGADO
	WHERE ENDERECO LIKE '%Houston,TX%’

Por exemplo:

Encontre todos os empregados que nasceram durante a década de 50.

Em SQL

	SELECT PNOME, SNOME
	FROM EMPREGADO
	WHERE DATANASC LIKE ‘________5_

- Se o caractere ‘%’ ou ‘_’ for necessário como um caractere normal de uma string, ele deve ser precedido por um caractere de escape.
	- A string ‘AB_CD%EF’ deve ser escrita como: ‘AB\_CD\%EF’.

## Operações Aritméticas

Os operadores aritméticos padrão +, -, * e / podem ser aplicados à valores numéricos como um resultado de uma consulta SQL.

Por exemplo:

Recupere todos os empregados (nome e sobrenome) e seus respectivos salários que trabalham no projeto ‘ProdutoX’ com um aumento de 10%.

Em SQL

	SELECT PNOME, SNOME, 1.1 * SALARIO
	FROM EMPREGADO, TRABALHA-EM, PROJETO
	WHERE NSS=ENSS AND PNO=PNUMERO AND PNOME='ProdutoX’;

## Order By

A cláusula ORDER BY é usada para ordenar tuplas resultantes de uma consulta com base nos valores de alguns atributos.

Por exemplo:

Recuperar a lista de empregados e dos projetos em que eles trabalhem, ordenados pelo departamento do empregado e cada departamento ordenado alfabeticamente pelo sobrenome do empregado.

Em SQL

	SELECT D.DNOME, E.SNOME, E.PNOME, P.PNOME
	FROM DEPARTAMENTO D, EMPREGADO E, TRABALHA-EM W, PROJETO P
	WHERE D.DNUMERO=E.DNUM AND E.NSS=W.ENSS AND W.PNO=P.PNUMERO
	ORDER BY D.DNOME, E.SNOME;

- A ordem padrão é ascendente, mas podemos utilizar a palavra-chave DESC para especificar que queremos a ordem descendente.
- A palavra-chave ASC pode ser usada para especificar explicitamente a ordem ascendente.

Por exemplo:

Em SQL

	SELECT D.DNOME, E.SNOME, E.PNOME, P.PNOME
	FROM DEPARTAMENTO D, EMPREGADO E, TRABALHA-EM W, PROJETO P
	WHERE D.DNUMERO=E.DNUM AND E.NSS=W.ENSS AND W.PNO=P.PNUMERO
	ORDER BY D.DNOME ASC, E.SNOME ASC;

# Normalização de Banco de Dados

https://www.ime.usp.br/~jef/bd09.pdf

## Abordagens de Projeto

- Top-down (análise)
	- O projeto de banco de dados começa com uma visão conceitual do sistema, geralmente representada por meio de diagramas de entidade-relacionamento (DER) ou modelos conceituais.
	- A partir desses diagramas, os atributos e relacionamentos são identificados e agrupados para formar as tabelas do banco de dados.
	- Essa abordagem é chamada de projeto por análise.

- Bottom-up (síntese)
	- O projeto de banco de dados é orientado pelos relacionamentos entre os atributos.
	- Abordagem Bottom-up analisa os atributos existentes e os relacionamentos entre eles. Com base nessa análise, as tabelas do banco de dados são construídas.
	- Essa abordagem é chamada de projeto pela síntese, pois envolve a síntese das tabelas a partir dos atributos existentes e seus relacionamentos.

- Nossa abordagem
	- Utilizar a abordagem Top-down para obter as relações
	- Utilizar a abordagem Bottom-up para melhorar a qualidade das relações obtidas anteriormente

## Guia informal

No guia informal para projetar um banco de dados relacional, o objetivo é criar "bons" esquemas de relações, avaliados em dois níveis: lógico e físico.

- No nível lógico, um bom esquema é aquele que é fácil de entender e permite formular consultas corretas.

- No nível físico, um bom esquema é aquele que permite que as tuplas sejam armazenadas e acessadas de maneira eficiente.

O projeto do banco de dados considera dois níveis de esquemas de relações: o **nível lógico**, que corresponde à visão do usuário, e o **nível de armazenamento**, que corresponde às relações base que são efetivamente armazenadas no banco de dados.

### Semântica de Atributos

**Guia 1**: Informalmente, cada tupla de uma relação deve representar uma entidade ou instância de relacionamento. Assim:

-  Atributos de entidades distintas não devem estar na mesma relação
- Apenas chaves-estrangeiras devem ser usadas para referenciar outras entidades
- Atributos de entidades e relacionamentos devem ser mantidos separadamente tanto quanto possível
- Dica: Projete um esquema que possa ser facilmente explicada. A semântica dos atributos deve ser de fácil interpretação.

Por exemplo:

O que é mais claro?

	Empregado(enome, nss, datanasc, endereço, dnumero)
	Projeto(pnome, pnumero, plocalizacao, dnum)
	Trabalha-em(nss, pnúmero, horas)

Ou

	EMP_PROJ (nss, pnúmero, horas, enome, pnome, plocalizacao)

Qual esquema necessita de maior espaço de armazenamento?

	Empregado(enome, nss, datanasc, endereço, dnumero)
	Projeto(pnome, pnumero, plocalizacao, dnum)
	Trabalha-em(nss, pnúmero, horas)

Ou 

	EMP_PROJ (nss, pnúmero, horas, enome, pnome, plocalizacao)

### Informação redundante em tuplas e Anomalias de Atualização

**Guia 2**: Projete um esquema que não sofra de anomalias de inserção, remoção e de atualização. Se existir alguma, então assegurese de que as aplicações levem tais anomalias em consideração 

- Informações redundantes desperdiçam o espaço de armazenamento
- A mistura atributos de várias entidades pode gerar problemas conhecidos como anomalias de atualização
	- Anomalias de inserção
	- Anomalias de remoção
	- Anomalias de modificação

 Por exemplo, anomalia de atualização

 Considere a relação:

 	EMP_PROJ (nss, pnúmero, horas, enome, pnome, plocalizacao)

Anomalia de Atualização: A mudança de nome do projeto de número 20 de ‘Faturamento’ para ‘Conta-Cliente’ provoca alterações em todos os empregados que trabalham nesse projeto

Anomalia de Inserção: Não se pode inserir um projeto a menos que um empregado esteja associado. Por outro lado, não se pode inserir um empregado a menos que ele esteja associado a um projeto.

Anomalia de Remoção: Quando um projeto é removido, todos os empregados que trabalham no projeto é removido. Alternativamente, se um empregado for o único empregado do projeto, a remoção desse empregado resultará na remoção do projeto correspondente

### Valores Nulos em Tuplas

**Guia 3**: Relações devem ser projetadas de forma que suas tuplas tenham a menor quantidade possível de valores nulos. Normalmente os atributos que possuem valores nulos podem ser colocados em relações separadas (com uma chave-primária).

Razões para os valores nulos:
- Valor não aplicável ou inválido
- Valor desconhecido (embora possa existir)
- Valor indisponível (embora se saiba que exista)

### Tuplas Espúrias

**Guia 4**: As relações devem ser projetadas para satisfazer a condição de junção sem perdas. Nenhuma tupla espúria deve ser gerada ao fazer um join natural de qualquer relação.

- Projetos incorretos de BDRs podem gerar resultados inválidos em certas operações Join
- A propriedade de “junção sem perdas” é usada para garantir resultados corretos em operações Join
- Existem duas propriedades importantes de decomposições:
	- Não-aditiva ou sem perdas (losslessness) do join correspondente
	- Preservação das dependências funcionais
- Note que a propriedade (a) é extremamente importante e não pode ser sacrificada. A propriedade (b) é menos restrito e pode ser sacrificada

## Dependências Funcionais

- Dependências funcionais (DFs) são usadas para medir formalmente a qualidade do projeto relacional
- As DFs e chaves são usadas para definir formas normais de relações
- As DFs são restrições que são derivadas do significado e do inter-relacionamento dos dados de atributos
- Um conjunto de atributos X determina funcionalmente um conjunto de atributos Y se o valor de X determinar um único valor Y

X->Y diz que se duas tuplas tiverem o mesmo valor para X, elas devem ter o mesmo valor para Y. Ou seja:
	Se X->Y então, para quaisquer tuplas t1 e t2 de r(R): 
 	Se t1[X] = t2[X], então t1[Y] = t2[Y]

Se K é uma chave de R, então K determina funcionalmente todos os atributos de R (uma vez que nós nunca teremos duas tuplas distintas com t1[K]=t2[K])

Importante:
- X->Y especifica uma restrição sobre todas as instâncias de r(R)
- As DFs são derivadas das restrições do mundo real e não de uma extensão específica da relação R

### Exemplos de Restrições de DF

O número do seguro social determina o nome do empregado

	NSS -> ENOME

O número do projeto determina o nome do projeto e a sua localização

	PNUMERO -> { PNOME, PLOCALIZACAO }

O nss de empregado e o número do projeto determinam as horas semanais que o empregado trabalha no projeto

	{ NSS, PNUMERO } -> HORAS 

### Regras de Inferência para DFs

- Regras de inferência de Armstrong:
	- RI1. (Reflexiva) Se Y é subconjunto de X, então X -> Y (Isso também é válido quando X=Y)
	- RI2. (Aumentativa) Se X -> Y, então XZ -> YZ (Notação: XZ significa X U Z)
	- RI3. (Transitiva) Se X -> Y e Y -> Z, então X -> Z
- RI1, RI2 e RI3 formam um conjunto completo de regras de inferência

Algumas regras de inferência úteis:
- (Decomposição) Se X -> YZ, então X -> Y e X -> Z
- (Aditiva) Se X -> Y e X -> Z, então X -> YZ
- (Pseudotransitiva) Se X -> Y e WY -> Z, então WX -> Z
- As três regras de inferência acima, bem como quaisquer outras regras de inferência, podem ser deduzidas a partir de RI1, RI2 e RI3 (propriedade de ser completa)

## Formas Normais com base em Chaves Primárias

### Normalização de Relações

- Normalização: Processo de decompor relações “ruins” dividindo seus atributos em relações menores 
- Forma Normal: Indica o nível de qualidade de uma relação

- 2FN, 3FN, BCNF baseiam-se em chaves e DFs de uma relação esquema
- 4FN e 5FN baseiam-se em chaves e dependências multivaloradas (não serão discutidas)

### Uso Prático das Formas Normais

- Na prática, a normalização é realizada para obter projetos de alta qualidade e atender às propriedades desejáveis
- Os projetistas de bancos de dados não precisam normalizar na maior forma normal possível.
- Desnormalização: processo de armazenar junções de relações de forma normal superior como uma relação base que está numa forma normal inferior

### Definição de Chaves e Atributos que Participam de Chaves

Revisão:
- Uma **superchave** de uma relação esquema R = {A1, A2, ...., An} é um conjunto de atributos S, subconjunto de R com a propriedade de que t1[S] ≠ t2[S] para qualquer extensão r(R)
- Uma superchave K é uma chave se K é uma **superchave mínima**
- Se uma relação esquema tiver mais de uma chave, cada chave será chamada de **chave-candidata**. Uma das chaves-candidatas é arbitrariamente escolhida para ser a chave-primária e as outras são chamadas de **chaves-secundárias**

- Um **atributo primo** (ou primário) é membro de alguma chave-candidata
- Um **atributo não-primo** é um atributo que não é primo – isto é, não é membro de qualquer chave-candidata

### Primeira Forma Normal

- Proíbe atributos compostos, atributos multivalorados e relações aninhadas. Ou seja, permite apenas atributos que sejam atômicos
- Considerado como sendo parte da definição de relação

### Segunda Forma Normal

- Utiliza conceitos de DFs e chave-primária
- Definições utilizadas:
	- **Atributo Primo** – atributo que é membro da chave primária K
	- **Dependência funcional total** – uma DF, Y->Z, onde a remoção de qualquer atributo de Y invalida a DF.
	- Exemplos:
 
	{ NSS, PNUMERO } -> HORAS é uma DF total, uma vez que NSS não determina HORAS e nem PNUMERO determina HORAS

	{ NSS, PNUMERO } -> ENOME não é uma DF total (é uma DF parcial) pois NSS -> ENOME

- Uma relação esquema R está na 2FN se estiver na 1FN e todos os atributos não-primos A de R forem totalmente dependentes da chaveprimária
- R pode ser decomposto em relações que estejam na 2 FN através do processo de normalização

### Terceira Forma Normal

Definição:
- Dependência funcional transitiva – uma DF X->Z pode ser derivada a partir de duas DFs X->Y e Y->Z.
- Exemplos:
	- Na figura anterior, NSS->NSSGER é uma DF transitiva pois NSS->DNUMERO e DNUMERO->NSSGER
	- NSS->ENOME não é transitiva pois não existe um conjunto e atributos X onde NSSN->X e X->ENOME

- Uma relação esquema R está na 3FN se ela estiver na 2FN e nenhum atributo não-primo, A, for transitivamente dependente da chave-primária
- R pode ser decomposto em relações que estejam na 3FN via o processo de normalização
- NOTA:
	- Em X->Y e Y->Z, sendo X a chave-primária, pode ser considerado um problema se, e somente se, Y não for uma chave-candidata. Quando Y é uma chave-candidata, não existe problema com a dependência transitiva
	- Por exemplo, considere EMP (NSS, Emp#, Salario ).
		- Aqui, NSS->Emp#->Salario e Emp# é uma chave-candidata

# Transações

https://www.ime.usp.br/~jef/bd10.pdf

## Modelo Transacional Clássico

- Transação é um programa que acessa dados.
- Sempre termina.
- Término com sucesso: confirmação (COMMIT)
	- Todas as operações são confirmadas e mantidas
- Término com falha: aborto (ABORT)
	- Todas as operações são desfeitas
- Transações confirmadas não podem ser abortadas e vice-versa.

## Propriedades ACID

Atomicidade

- Uma transação é atômica se:
	- Ou todas suas operações são confirmadas no banco de dados;
	- Ou todas suas operações são desfeitas.
		-o sistema deve voltar ao mesmo estado em que estava antes do início da transação.

Consistência

Isolamento

- A execução de uma transação não pode ser afetada por outras executando concorrentemente.
- Tudo deve se passar como se todos os recursos estivessem disponíveis.

Durabilidade

- Os efeitos de uma transação confirmada não podem ser desfeitos.

## Escalonamentos 

- As diversas operações de transações precisam ser executadas em alguma ordem
- Escalonamento = Ordem de execução

## Teoria da Seriação

- Trata das operações executadas
- Ignora o código da transação
- Operações consideradas
	- leitura: r[x] (valor lido não importa)
	- escrita: w[x] (valor escrito não importa)
	- confirmação: c
	- aborto: a
	- x: qualquer item de dado (dado, índice, dicionário, etc)

## Conflitos

- Transações Ti ≠ Tj concorrentes;
- Duas operações sobre o mesmo dado x conflitam se **uma delas é operação de escrita**.
- Pares conflitantes

	ri[x] < wj[x] wj[x] < ri[x]

	rj[x] < wi[x] wi[x] < rj[x]

	wi[x] < wj[x] wj[x] < wi[x]

- Não conflitam:
  
	ri[x] < rj[x] rj[x]< ri[x]

## Escalonamentos Equivalentes

- E1 é equivalente a E2:
	- E1 e E2 ordenam conflitos da mesma forma
- Exemplo:

	E1 = r1[x]; w1[y]; c1; r2[y]; r2[z]; w2[x]; c2

	E2 = r1[x]; r2[z]; w1[y]; r2[y]; c1; w2[x]; c2

	E3 = r1[x]; r2[z]; r2[y]; w1[y]; c1; w2[x]; c2

- E1 é equivalente a E2 mas não a E3

## Escalonamentos Seriáveis

- Um escalonamento é seriável se for equivalente a algum escalonamento serial.
- Dado E, podem existir mais de um e escalonamentos seriais equivalentes.
- Escalonamentos não seriáveis devem ser proibidos pelo Escalonador.

## Grafo da Seriação

- E é um escalonamento sobre T1, ... , Tn.
- Gs(E) é definido:
	- Nós: T1, ... , Tn.
	- Arestas dirigitas: Ti → Tj se existe x tal que:
		- pi[x] e qj[x] são operações conflitantes
		- pi[x] < qj[x] em E

## Teorema da Seriação

- Um escalonamento E é seriável se e somente se Gs(E) é acíclico.
- Por exemplo:
	- E1 é serial, Gs(E1) é acíclico
	- E2 é seriável, Gs(E2) é acíclico
	- E3 é seriável, Gs(E3) é acíclico

## O Protocolo de Bloqueios Bifásicos (BBF)

- Escalonamentos BBF são sempre seriáveis.
- pli[x] : bloqueio para executar pi[x]
- pui[x]: desbloqueio de pi[x]
- pli[x] < pi[x] < pui[x]
- pli[x] e qlj[x] conflitam se pi[x] e qj[x] conflitam.
- Ti requer pli[x] e obtém se não há Tj com qlj[x].
- Caso contrário, Ti é posta em espera.

## Regra das Duas Fases

- Após liberar um bloqueio, uma transação não pode mais obter nenhum outro bloqueio.

## BBF: Propriedades

- Pode gerar travamentos (deadlocks)
- Necessidade de monitoramento de travamentos.
- Uma vítima é escolhida, abortada e reiniciada.
- BBF é facilmente generalisável para transações distribuídas.
- Controle de travamento também é extensível no caso distribuído.
- BBF Estrito: bloqueios só liberados no fim.

# Seriabilidade

Seriabilidade: https://edisciplinas.usp.br/pluginfile.php/7737480/mod_resource/content/1/Seriabilidade.pdf

# Temas que (talvez) não serão cobrados na P2

- Abstração de Especialização

- Forma Normal Geral e Abstração de Generalização

- Introdução ao uso do SGBD com interface Web

- Teorema da Seriação

- Gerenciamento de Recuperação

- Árvores B, B+
