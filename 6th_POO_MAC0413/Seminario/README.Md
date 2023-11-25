## Padrões para Mapeamento Objeto-Relacional 

Exemplos recomendados: Repository, DAO, ActiveRecord, DataMapper

### Breve resumo/Apresentação do que é o Mapeamento Objeto-Relacional;

Em sistemas de softwares, nos deparamos com dois mundos diferentes: programas orientados a objetos, que organiza dados em entidades e suas inter-relações, e bancos de dados relacionais, que utiliza tabelas para armazenar dados e relações entre eles.

A estrutura do banco de dados relacional está longe de ser orientado a objetos, e por isso as técnicas MOR surgem para suprir a necessidade que os desenvolvedores têm de visualizar tudo como objetos para programarem com mais facilidade.

O Mapeamento Objeto-Relacional (MOR) é uma técnica de programação usada na criação de uma "ponte" entre programas orientados a objetos e bancos de dados relacionais.

Ao interagir com um banco de dados usando programação orientada a objetos, você precisará realizar diversas operações, como criar, ler, atualizar e excluir dados de um banco de dados. Por design, você utiliza SQL para realizar essas operações em bancos de dados relacionais.

Embora o uso de SQL para esse fim não seja necessariamente uma má ideia, as ferramentas MOR ajudam a simplificar a interação entre bancos de dados relacionais e programação orientada a objetos.

### O contexto de como o MOR é aplicado no mercado

Um MOR (Mapeamento Objeto-Relacional) traduz informações sobre os estados, entidades e relações criados por programas orientados a objetos e mapeia automaticamente para tabelas e registros no banco de dados, simplificando o processo de persistência de dados.

Ele cria um mapeamento estruturado que explica como objetos estão relacionados a diferentes tabelas de dados, sem necessidade de entender detalhes específicos sobre como os dados estão estruturados. 

O MOR converte dados entre tabelas e gera o código SQL necessário para que o banco de dados responda às mudanças na aplicação e gerencie as atividades de dados.

Quando a aplicação faz alterações nos objetos de dados, o banco de dados relacional insere, atualiza, cria ou exclui dados em resposta a essas alterações.
#### Resumo de como funciona

- As classes no código são mapeadas para tabelas no banco de dados, e as propriedades da classe são mapeadas para colunas na tabela.

- Relacionamentos entre objetos são mapeados usando chaves estrangeiras nas tabelas do banco de dados.

- Operações de consulta e persistência são realizadas usando métodos em objetos, e o MOR traduz essas operações para instruções SQL.

### Quais problemas pretende solucionar;

#### Algumas das vantagens de usar uma ferramenta MOR:

- Acelera o tempo e reduz o custo de desenvolvimento: O uso de uma ferramenta MOR pode acelerar o processo de desenvolvimento, permitindo que equipes de programadores trabalhem mais rapidamente na criação de aplicativos, pois elimina a necessidade de escrever consultas SQL complexas manualmente.

- Abstração da camada de banco de dados: Uma ferramenta MOR cuida da maioria das operações de banco de dados, incluindo a criação, leitura, atualização e exclusão de registros. Isso permite que os desenvolvedores se concentrem mais na lógica de seus aplicativos.

- Reduz a quantidade de código necessário: O uso de ferramentas MOR geralmente requer menos código em comparação com o uso de SQL direto. Isso simplifica o desenvolvimento e a manutenção do código, tornando-o mais enxuto e legível.

- Melhora a segurança: As ferramentas MOR são projetadas para mitigar riscos de ataques de injeção de SQL, uma vez que elas geralmente geram consultas parametrizadas que são menos suscetíveis a ataques de injeção de SQL. A injeção SQL ocorre quando um invasor insere comandos SQL maliciosos em campos de entrada de uma aplicação.

- Portabilidade do código: O código que utiliza MOR é, em sua maioria, independente do banco de dados, facilitando a migração entre diferentes sistemas de gerenciamento de banco de dados.

Referências:

https://www.freecodecamp.org/news/what-is-an-orm-the-meaning-of-object-relational-mapping-database-tools/

https://www.theserverside.com/definition/object-relational-mapping-ORM
