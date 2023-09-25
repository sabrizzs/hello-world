#ifndef AMQP_H
#define AMQP_H

#define STATE_CONNECTION_START 0
#define STATE_CONNECTION_TUNE 1
#define STATE_CONNECTION_OPEN 2
#define STATE_CHANNEL_OPEN 3

void processAMQPMessage();

void startConnection(int connfd);

#endif // AMQP_H
