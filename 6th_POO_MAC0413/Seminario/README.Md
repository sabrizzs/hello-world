## Padrões para Mapeamento Objeto-Relacional 

Exemplos recomendados: Repository, DAO, ActiveRecord, DataMapper

### Breve resumo/Apresentação do que é o Mapeamento Objeto-Relacional;

O Mapeamento Objeto-Relacional (MOR) é uma técnica usada na criação de uma "ponte" entre programas orientados a objetos e bancos de dados relacionais.

Em outras palavras, você pode enxergar o MOR como a camada que conecta a programação orientada a objetos (POO) a bancos de dados relacionais.

Ao interagir com um banco de dados usando linguagens de programação orientada a objetos, você precisará realizar diversas operações, como criar, ler, atualizar e excluir dados de um banco de dados. Por design, você utiliza SQL para realizar essas operações em bancos de dados relacionais.

Embora o uso de SQL para esse fim não seja necessariamente uma má ideia, as ferramentas MOR ajudam a simplificar a interação entre bancos de dados relacionais e diferentes linguagens de programação orientada a objetos.

### O contexto de como o MOR é aplicado no mercado

Um MOR (Mapeamento Objeto-Relacional) traduz informações sobre os estados e códigos criados por programas orientados a objetos, tornando mais compreensíveis essas estruturas que, frequentemente, podem ser difíceis de entender. 

Ele cria um mapeamento estruturado que explica como objetos estão relacionados a diferentes tabelas de dados, sem necessidade de entender detalhes específicos sobre como os dados estão estruturados. Em outras palavras, o MOR cria um modelo lógico do programa com um alto nível de abstração, ou seja, sem especificar os detalhes subjacentes do código.

Quando a aplicação faz alterações nos objetos de dados, o banco de dados relacional insere, atualiza, cria ou exclui dados em resposta a essas alterações. Isso ocorre porque o MOR converte dados entre tabelas e gera o código SQL necessário para que o banco de dados responda às mudanças na aplicação e gerencie as atividades de dados.

O MOR gerencia os detalhes de mapeamento entre um conjunto de objetos e bancos de dados relacionais subjacentes, repositórios XML ou outras fontes e destinos de dados. 

### Quais problemas pretende solucionar;

#### Algumas das vantagens de usar uma ferramenta MOR:

- Acelera o tempo e reduz o custo de desenvolvimento: O uso de uma ferramenta MOR pode acelerar o processo de desenvolvimento, permitindo que equipes de programadores trabalhem mais rapidamente na criação de aplicativos, pois elimina a necessidade de escrever consultas SQL complexas manualmente.

- Lida com a lógica necessária para interagir com bancos de dados: Uma ferramenta MOR cuida da maioria das operações de banco de dados, incluindo a criação, leitura, atualização e exclusão de registros. Isso permite que os desenvolvedores se concentrem mais na lógica de seus aplicativos.

- Reduz a quantidade de código necessário: O uso de ferramentas MOR geralmente requer menos código em comparação com o uso de SQL direto. Isso simplifica o desenvolvimento e a manutenção do código, tornando-o mais enxuto e legível.

- Melhora a segurança: As ferramentas MOR são projetadas para mitigar riscos de ataques de injeção de SQL, uma vez que elas geralmente geram consultas parametrizadas que são menos suscetíveis a ataques de injeção de SQL. A injeção SQL ocorre quando um invasor insere comandos SQL maliciosos em campos de entrada de uma aplicação.

Referências:

https://www.freecodecamp.org/news/what-is-an-orm-the-meaning-of-object-relational-mapping-database-tools/

https://www.theserverside.com/definition/object-relational-mapping-ORM
