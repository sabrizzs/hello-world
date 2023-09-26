### Tópicos para entender

- AMQP
- RabbitMQ
- amqp-publish
- amqp-consume
- amqp-declare-queue
- pacote debian amqp-tools
- comunicação entre cliente e servidor AMQP
- sistema publish-subscribe

### Termos

- SERVIDOR DE ECO:
  
Um servidor de eco, também conhecido como "echo server", é um tipo de servidor de rede que recebe mensagens ou dados de um cliente e simplesmente os retorna ao cliente sem realizar nenhum processamento adicional. O propósito principal de um servidor de eco é verificar a conectividade e a funcionalidade da rede, bem como testar o comportamento de transmissão de dados entre um cliente e um servidor.

1. O cliente estabelece uma conexão com o servidor de eco.
2. O cliente envia uma mensagem ou dados para o servidor.
3. O servidor recebe os dados e, em vez de realizar algum processamento ou lógica específica, ele simplesmente envia os mesmos dados de volta ao cliente.
4. O cliente recebe os dados retornados do servidor.
5. O cliente pode verificar se os dados retornados correspondem aos dados que ele enviou, confirmando assim que a comunicação com o servidor está funcionando corretamente.

- SOCKETS:

Um socket é uma abstração de software que representa uma interface de comunicação de rede, permitindo que programas em um computador se comuniquem com programas em outros computadores por meio de uma rede, seja ela local (LAN) ou a internet.

- AMQP:

O AMQP é um protocolo de comunicação em rede, tal qual o HTTP, que permite que aplicações se comuniquem. 

O AMQP tem muitas vantagens, mas duas são mais importantes: produzir um padrão aberto para protocolos de mensageria e permitir a interoperabilidade entre muitas tecnologias e plataformas.

Existem muitos sistemas rodando em muitos Sistemas Operacionais, que são desenvolvidos com múltiplas linguagens de programação, rodando em várias arquiteturas de hardware e máquinas virtuais. AMQP não só torna a integração dentre esses vários sistemas diferentes possível, como também permite que produtos diferentes que implementem este protocolo possam trocar informações.

1. O produtor se conecta ao servidor AMQP e envia uma mensagem para uma fila ou troca especificada.
2. O servidor AMQP recebe a mensagem e a armazena temporariamente.
3. Se houver consumidores interessados na fila ou troca associada, o servidor AMQP encaminhará a mensagem para a fila de destino ou diretamente para os consumidores, com base nas regras de roteamento definidas.
4. Os consumidores se conectam ao servidor AMQP, se inscrevem nas filas de interesse e aguardam a entrega de mensagens.
5. Quando uma mensagem é entregue a um consumidor, ele a processa conforme necessário.
6. O servidor AMQP garante que as mensagens sejam entregues com segurança e confiabilidade, mesmo em caso de falha de rede ou de um dos componentes do sistema.

- TCP:

TCP, ou Transmission Control Protocol (Protocolo de Controle de Transmissão), é um dos principais protocolos de comunicação da Internet e é parte integrante da pilha de protocolos TCP/IP, que é a base da comunicação de rede global. O TCP é responsável por fornecer uma comunicação confiável, orientada à conexão e baseada em stream (fluxo) entre dispositivos em uma rede.

- UTILITÁRIOS AMQP:

Testar com Loopback: lo. Caso seja necessário, filtrar com amqp.

Os utilitários amqp-publish, amqp-consume e amqp-declare-queue são ferramentas que fazem parte do conjunto de utilitários AMQP (Advanced Message Queuing Protocol) e são frequentemente usados para interagir com servidores AMQP, como o RabbitMQ. Cada um desses utilitários tem uma função específica:

1. amqp-publish:

Função: O amqp-publish é usado para publicar (enviar) mensagens para uma fila (ou exchange) em um servidor AMQP.
Uso típico: amqp-publish -r myqueue -b Hello

2. amqp-consume:

Função: O amqp-consume é usado para consumir (receber) mensagens de uma fila em um servidor AMQP.
Uso típico: amqp-consume -A -e ...

3. amqp-declare-queue:

Função: O amqp-declare-queue é usado para declarar uma fila em um servidor AMQP.
Uso típico: amqp-declare-queue -d -q myqueue

### Informações de implementação

- **Declaração de Fila (Queue Declaration):**
  
Função para permitir que os clientes declarem filas.
Essa função deve receber os parâmetros relevantes para a declaração da fila, como o nome da fila e as opções de configuração.
Ela deve criar a fila no servidor e definir suas propriedades conforme especificado pelo cliente.

- **Publicação de Mensagem (Message Publishing):**
  
Função para permitir que os clientes publiquem mensagens em uma fila específica.
Essa função deve receber a mensagem do cliente, a fila de destino e quaisquer outros parâmetros relevantes.
Ela deve adicionar a mensagem à fila de destino para posterior entrega aos consumidores.

- **Inscrição em Fila (Queue Subscription):**
  
Função para permitir que os clientes se inscrevam em uma fila para receber mensagens.
Essa função deve associar o cliente à fila de destino, permitindo que ele receba mensagens dessa fila.
Se múltiplos clientes se inscreverem na mesma fila, você deve implementar um esquema de Round Robin para entregar mensagens alternadamente.

- **Entrega de Mensagens (Message Delivery):**
  
Função que gerencia a entrega de mensagens aos clientes inscritos em uma fila.
Ela deve garantir que as mensagens sejam entregues aos clientes inscritos de acordo com as políticas de entrega, como o esquema Round Robin mencionado.

- **Gerenciamento de Conexões (Connection Management):**
  
Funções para lidar com a abertura e fechamento de conexões de clientes.
Isso inclui a criação de novas conexões, o gerenciamento de conexões ativas e o tratamento de desconexões inesperadas.

- **Implementação de Políticas de Troca (Exchange Policies):**
  
Se necessário, funções para implementar políticas de troca que determinam como as mensagens são roteadas entre filas.

<<<<<<< Updated upstream
- Cada mensagem tem um header:


=======
##############

- **Definir a Estrutura de Mensagens AMQP:** Você precisará criar estruturas de dados para representar os diferentes tipos de mensagens AMQP, como mensagens de conexão, mensagens de declaração de filas, mensagens de publicação e assim por diante. Essas estruturas de dados devem ser usadas para serializar e desserializar as mensagens.

- **Negociação de Conexão:** Implemente a lógica para a negociação de conexão AMQP. Isso inclui o aperto de mão inicial, onde o servidor e o cliente concordam com a versão do protocolo a ser usada.

- **Gerenciamento de Canais:** O protocolo AMQP permite que várias operações ocorram em canais separados. Implemente a lógica para criar, selecionar e fechar canais.

- **Declaração de Filas:** Implemente a capacidade de o cliente declarar filas, definindo seus atributos, como nome, durabilidade, argumentos, etc.

- **Publicação de Mensagens:** Implemente a capacidade de o cliente publicar mensagens em filas.

- **Consumo de Mensagens:** Implemente a capacidade de o cliente consumir mensagens de filas e entregar essas mensagens aos consumidores registrados.
>>>>>>> Stashed changes

