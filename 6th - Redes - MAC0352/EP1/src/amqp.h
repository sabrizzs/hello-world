#ifndef AMQP_H
#define AMQP_H

#include <stdint.h>

// Estrutura das mensagens

// Mensagem de conexão: primeira mensagem enviada após a conexão TCP ser estabelecida
typedef struct {
    char protocol_name[8];
    uint8_t major_version;
    uint8_t minor_version;
} AMQPConnectionMessage;

// Mensagem de declaração de fila: criação de nova fila no servidor
typedef struct {
    uint16_t channel;
    uint32_t frame_size;
    uint16_t class_id;
} AMQPQueueDeclareMessage;

// Mensagem de publicação: usada para enviar uma mensagem para uma fila específica
typedef struct {
    uint16_t channel;
    uint32_t frame_size;
    uint16_t class_id;
} AMQPPublishMessage;


// Protótipos das funções relacionadas ao AMQP
void initializeAMQPConnection(AMQPConnectionMessage *connection);
void initializeAMQPQueueDeclare(AMQPQueueDeclareMessage *queueDeclare);
void initializeAMQPPublish(AMQPPublishMessage *publish);


//typedef struct publish_packet{

// Função para processar o comando "amqp-publish"
void amqp_publish_command(char *recvline) {
    printf("Processing amqp-publish command\n");
    AMQPConnectionMessage connectionMessage;
    initializeAMQPConnection(&connectionMessage);
}

//void amqp_consume_command(const char *command); 

//void amqp_declare_queue_command(const char *command); 

#endif // AMQP_H
