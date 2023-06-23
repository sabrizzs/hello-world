# P2 - LABJEF

Assuntos cobrados:
- Consultas: álgebra relacional, cálculo relacional e SQL
- Normalização
- Transações 
- Seriabilidade (?)

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

- CREATE SCHEMA – Comando utilizado para criar esquemas de aplicações.
- O esquema permite agrupar as tabelas, restrições, visões, domínios e outros construtores (como concessão de autoridade) que descrevem o esquema.
  
Por exemplo:

	CREATE SCHEMA COMPANHIA AUTHORIZATION MAC0426;

O comando CREATE SCHEMA está sendo usado para criar um esquema chamado "COMPANHIA" e atribuir a autoridade ou permissões ao usuário "MAC0426" para acessar e modificar os objetos dentro desse esquema. 

### Criação de Domínios

- CREATE DOMAIN - utilizado para criar domínios de atributos, ou seja, para definir tipos de dados personalizados que podem ser usados em colunas de tabelas.
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

