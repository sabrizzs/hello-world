#ifndef AMQP_H
#define AMQP_H

#include <stdint.h>

/* Estrutura das mensagens */

/* Tipos de mensagens AMQP */
typedef enum {
    METHOD = 1,  // Mensagem de Método: afetam o estado do servidor (queue, exchange, publish, etc)
    HEADER = 2,
    CONTENT = 4, // Mensagem de Conteúdo: corpo real das mensagens
    HEARTBEAT = 8 // Mensagem de Heartbeat: mantém conexão ativa
} MessageType;

/* Protocol header */
typedef struct {
    char protocol_name[4];
    uint8_t major_id;
    uint8_t minor_id;
    uint8_t major_version;
    uint8_t minor_version;
} ProtocolHeader;

/* Message header */
typedef struct {
    uint8_t msg_type;
    uint16_t channel;
    uint32_t length;
} Message;

typedef struct {
    char * data;
    int size;
} Packet;


void initializeAMQPConnection(ProtocolHeader *connection);

void amqp_publish_command(char *recvline);

int protocolNegotiation(int clientSocket);

//void amqp_consume_command(const char *command); 

//void amqp_declare_queue_command(const char *command); 

#endif // AMQP_H
