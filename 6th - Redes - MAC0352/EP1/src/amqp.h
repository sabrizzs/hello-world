#ifndef AMQP_H
#define AMQP_H

// Inclua os headers necessários para o AMQP aqui

// Defina estruturas de dados relevantes para o AMQP, se necessário
// Exemplo: typedef struct AmqpMessage { ... } AmqpMessage;


void amqp_publish(const char *command); 

void amqp_consume(const char *command); 

void amqp_declare_queue(const char *command); 

#endif // AMQP_H
