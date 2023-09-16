#include "amqp.h"

// Implementação das funções das mensagens

void initializeAMQPConnection(AMQPConnectionMessage *connection) {
    strcpy(connection->protocol_name, "AMQP"); 
    connection->major_version = 0;
    connection->minor_version = 9;
}

void initializeAMQPQueueDeclare(AMQPQueueDeclareMessage *queueDeclare) {
    queueDeclare->channel = 1; // Canal AMQP
    queueDeclare->frame_size = 0; // Tamanho do quadro (frame)
    queueDeclare->class_id = 50; // ID da classe (declaração de fila)
}

void initializeAMQPPublish(AMQPPublishMessage *publish) {
    publish->channel = 1; // Canal AMQP
    publish->frame_size = 0; // Tamanho do quadro (frame)
    publish->class_id = 60; // ID da classe (publicação)
}

// Função para processar o comando "amqp-publish"
void amqp_publish_command(char *recvline) {
    printf("Processing amqp-publish command\n");
    AMQPConnectionMessage connectionMessage;
    initializeAMQPConnection(&connectionMessage);
    return;
}

