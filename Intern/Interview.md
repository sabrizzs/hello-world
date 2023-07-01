## Business Analyst

### Online assessment

- Tasks from Excel
	- vlookups
 	- sumif
	- pivot tables
	- charts
- SQL
	- three queries with join/where/order by/group by clauses
- Question regarding your previous experience dealing with data
- Some logical questions
- 3 questions about Leadership Principles
	- live answer on camera
 - Phone screen
 - ETL
 - Data warehousing
 - Machine learning
 - Cloud computing
 - EDA

###
   
 - Past experience with business analytics

### Virtual Interview
- STAR
- Generally if you are hired they will answer you in one business day if you dont get the email in one day then you are most likely not getting hired
- Why Amazon? (your motivations)
	- Amazon is looking for people who have an investment in the company beyond just a paycheck.
 	- "I admire that Amazon values customer obsession. I believe that putting the customer first leads to better product and software."
  	- https://www.educative.io/blog/why-amazon-interview-question
- https://www.tryexponent.com/blog/how-to-nail-amazons-behavioral-interview-questions

## Excel

### vlookups/procv

Procura um valor e retorna um valor correspondente na mesma linha, mas a partir de uma coluna diferente.

Exemplo de uso

	VLOOKUP("Tarefa E"; [Nome da tarefa]1:Feito5; 2; falso)

Sintaxe

	VLOOKUP(search_value lookup_table column_num [ match_type ])

- search_value — O valor a ser procurado, que deve estar na primeira coluna da lookup_table.

- lookup_table — O intervalo de células em que procurar, contendo o search_value (na coluna mais à esquerda) e o valor de retorno.

- column_num — Um número que representa a posição da coluna (em lookup_table) do valor a retornar, com a coluna mais à esquerda de lookup_table na posição 1.

- match_type —[opcional] O padrão é verdadeiro. Especifica se deve encontrar uma correspondência exata (falso) ou uma correspondência aproximada (verdadeiro).

### sumif/somase

A sintaxe da função SOMASE é a seguinte:

	SOMASE(intervalo; critérios; [intervalo_soma])

- intervalo: é o intervalo de células que você deseja verificar em relação aos critérios.
- critérios: é a condição que define quais células no intervalo serão somadas.
- intervalo_soma (opcional): é o intervalo de células que você deseja somar se o critério for atendido. Se não for especificado, o intervalo será usado para somar.

Por exemplo, se você tiver uma lista de valores em uma coluna A e quiser somar apenas os valores maiores que 10, você pode usar a função SOMASE da seguinte maneira:

	=SOMASE(A1:A10;">10")

## SQL

### JOIN

Supondo que temos duas tabelas: "Clientes" e "Pedidos". A tabela "Pedidos" possui uma chave estrangeira "id_cliente" que referencia a chave primária "id" da tabela "Clientes".

	SELECT Pedidos.id_pedido, Pedidos.data_pedido, Clientes.nome_cliente
	FROM Pedidos
	JOIN Clientes ON Pedidos.id_cliente = Clientes.id;

### WHERE

Supondo que temos uma tabela chamada "Produtos" com uma coluna "preco" que armazena o preço de cada produto.

	SELECT nome_produto, preco
	FROM Produtos
	WHERE preco > 50;


### ORDER BY and GROUP BY

	Supondo que temos uma tabela chamada "Vendas" com as colunas "id_produto", "quantidade_vendida" e "data_venda".

	SELECT id_produto, SUM(quantidade_vendida) AS total_quantidade_vendida
	FROM Vendas
	GROUP BY id_produto
	ORDER BY total_quantidade_vendida DESC;


## ETL

ETL (Extract, Transform, Load) é um processo utilizado na área de tecnologia da informação para **integrar, limpar e transformar dados de várias fontes diferentes em um formato adequado para análise**, armazenamento e uso em um sistema de destino, como um data warehouse ou um data lake. 

- Extração (Extract): Nesta etapa, os dados são obtidos a partir de várias fontes de dados, como bancos de dados, arquivos, APIs, sistemas legados, entre outros. A extração envolve identificar, selecionar e recuperar os dados relevantes para o processo.

- Transformação (Transform): Nesta etapa, os dados extraídos são transformados e limpos para atender aos requisitos do sistema de destino. Isso pode envolver tarefas como filtrar, reformatar, converter tipos de dados, combinar dados de várias fontes, enriquecer os dados com informações adicionais e aplicar regras de negócios ou cálculos para criar novos campos ou métricas.

- Carga (Load): Nesta etapa, os dados transformados são carregados no sistema de destino, como um data warehouse, um data lake ou um banco de dados. Isso pode incluir a criação ou atualização de tabelas, a definição de relacionamentos entre os dados e a validação da integridade dos dados.

## Data Warehousing (armazenamento de dados)

Data warehousing refere-se ao processo de **criar e gerenciar um repositório centralizado de dados de várias fontes**, projetado especificamente para suportar análises e tomada de decisões. 

## EDA

EDA é a sigla para Exploratory Data Analysis, que em português significa Análise Exploratória de Dados. É uma abordagem analítica utilizada na área de ciência de dados e estatística para **explorar e entender os dados antes de realizar análises mais avançadas** ou construir modelos preditivos.

Alguns dos principais objetivos da EDA são:

- Sumarização de dados: Resumir os dados de forma descritiva, como média, mediana, desvio padrão, mínimos e máximos, para entender sua distribuição e variação.

- Identificação de outliers: Detectar valores atípicos ou discrepantes que podem indicar erros ou fenômenos incomuns nos dados.

- Análise de correlação: Investigar a relação entre as variáveis e identificar padrões de associação através de técnicas estatísticas, como coeficiente de correlação.

- Visualização de dados: Utilizar gráficos e visualizações para explorar as características e padrões dos dados, como histogramas, gráficos de dispersão, box plots, entre outros.

- Identificação de insights: Descobrir padrões interessantes, relações causais potenciais ou anomalias nos dados que podem levar a novas perguntas de pesquisa ou direcionar análises futuras.