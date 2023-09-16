#include <string.h>
#include <stdio.h>

#include "amqp.h"

/* Cabeçalho do protocolo AMQP */
void initializeAMQPConnection(AMQPConnectionMessage *connection) {
    strcpy(connection->protocol_name, "AMQP");
    connection->major_id = 0;
    connection->minor_id = 0;
    connection->major_version = 9;
    connection->minor_version = 1;
}

/* Negociação do protocolo AMQP */
int protocolNegotiation(int clientSocket) {
    // Envia o cabeçalho de protocolo AMQP para o cliente
    AMQPConnectionMessage connectionMessage;
    initializeAMQPConnection(&connectionMessage);
    send(clientSocket, &connectionMessage, sizeof(AMQPConnectionMessage), 0);

    // Recebe o cabeçalho de protocolo do cliente
    AMQPConnectionMessage clientConnectionMessage;
    recv(clientSocket, &clientConnectionMessage, sizeof(AMQPConnectionMessage), 0);

    // Verificar a compatibilidade das versões
    if (strcmp(clientConnectionMessage.protocol_name, "AMQP") == 0 &&
        clientConnectionMessage.major_version == 0 &&
        clientConnectionMessage.minor_version == 9) {
        // As versões são compatíveis, a negociação foi bem-sucedida
        printf("As versões são compatíveis.");
        return 1;
    } else {
        // As versões não são compatíveis, encerrar a conexão
        printf("As versões não são compatíveis.");
        return 0;
    }
}


/* Inicializa uma mensagem de método para declarar fila */
void initializeAMQPQueueDeclare(AMQPMessageHeader *queueDeclare) {
    queueDeclare->channel = 1; // Canal AMQP
    queueDeclare->msg_type = 1; // Mensagem de método
    queueDeclare->length = 5; 
}

/* Processa o comando "amqp-publish" */
void amqp_publish_command(char *recvline) {
    printf("Processing amqp-publish command\n");
    AMQPConnectionMessage connectionMessage;
    initializeAMQPConnection(&connectionMessage);
}

