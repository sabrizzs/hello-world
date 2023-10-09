Sabrina Araújo da Silva
NUSP: 12566182

## AMELIA: Advanced Message Queueing Protocol by Sabrina Araujo

Este é um servidor AMQP (Advanced Message Queuing Protocol) básico implementado em C. Ele suporta operações como conexão, abertura de canal, criação de filas, publicação e consumo de mensagens. 

## Estrutura e arquivos

- `main.c`: Contém o loop principal do servidor de mensagens.
- `amqp.c`: Contém a implementação das funções relacionadas ao protocolo AMQP.
- `packets.c`: Contém pacotes de dados do protocolo AMQP.
- `amqp.h`: Cabeçalho com declarações de funções relacionadas ao protocolo AMQP.
- `packets.h`: Cabeçalho com definições de pacotes do protocolo AMQP.
- `Makefile`: Um arquivo Makefile para compilar o programa.

## Compilação e Execução

### Compilação

Execute o comando make na raiz do projeto para compilar o programa.

```bash

make

```

### Execução

Após compilar, execute o servidor AMQP usando o comando:

``` bash

./main <Porta>

```
O servidor estará pronto para aceitar conexões de clientes AMQP.

As conexões AMQP podem ser feitas utilizando os comandos amqp-declare-queue, amqp-publish e amqp-consume.
