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

# Normalização de Banco de Dados

https://www.ime.usp.br/~jef/bd09.pdf

# Transações

Transações: https://www.ime.usp.br/~jef/bd10.pdf

Seriabilidade: https://edisciplinas.usp.br/pluginfile.php/7737480/mod_resource/content/1/Seriabilidade.pdf

# Temas que (talvez) não serão cobrados na P2

- Abstração de Especialização

- Forma Normal Geral e Abstração de Generalização

- Introdução ao uso do SGBD com interface Web

- Teorema da Seriação

- Gerenciamento de Recuperação

- Árvores B, B+

