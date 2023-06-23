# P2 - LABJEF MAC0350

Assuntos cobrados:
- Consultas: álgebra relacional, cálculo relacional e SQL
- Normalização
- Transações 
- Seriabilidade (?)

Aqui está o sumário para o arquivo Markdown fornecido:

# Sumário

- [SQL](#sql)
  - [Conceitos](#conceitos)
  - [Tipos de dados](#tipos-de-dados)
  - [DDL](#ddl)
    - [Criação do Esquema](#criação-do-esquema)
    - [Criação de Domínios](#criação-de-domínios)
    - [Criação de Tabelas](#criação-de-tabelas)
    - [Alteração de Tabela](#alteração-de-tabela)
  - [DML](#dml)
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

## DML

- A linguagem de manipulação de dados (DML) é usada para manipular os dados dentro da base de dados.
- Os comandos DML são usados para inserir, atualizar, excluir e consultar dados na instância do banco de dados. 





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

