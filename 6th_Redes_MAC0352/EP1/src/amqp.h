#ifndef AMQP_H
#define AMQP_H

/* Classes */
#define CONNECTION 0xa
#define CHANNEL 0x14
#define QUEUE 0x32
#define BASIC 0x3c

/* Methods */
#define CONNECTION_START 0xa
#define CONNECTION_START_OK 0xb
#define CONNECTION_TUNE 0x1e
#define CONNECTION_TUNE_OK 0x1f
#define CONNECTION_OPEN 0x28
#define CONNECTION_OPEN_OK 0x29
#define CONNECTION_CLOSE 0x32
#define CONNECTION_CLOSE_OK 0x33

#define CHANNEL_OPEN 0xa
#define CHANNEL_OPEN_OK 0xb
#define CHANNEL_CLOSE 0x28
#define CHANNEL_CLOSE_OK 0x29

#define QUEUE_DECLARE 0xa
#define QUEUE_DECLARE_OK 0xb

#define BASIC_PUBLISH 0x28
#define BASIC_QOS 0xa
#define BASIC_QOS_OK 0xb
#define BASIC_CONSUME 0x14
#define BASIC_CONSUME_OK 0x15
#define BASIC_ACK 0x50

/*enum amqp_class{
    CONNECTION = 0xa,
    CHANNEL = 0x14,
    QUEUE = 0x32,
    BASIC = 0x3c,
};

enum amqp_method{
    CONNECTION_START = 0xa,
    CONNECTION_START_OK = 0xb,
    CONNECTION_TUNE = 0x1e,
    CONNECTION_TUNE_OK = 0x1f,
    CONNECTION_OPEN = 0x28,
    CONNECTION_OPEN_OK = 0x29,
    CONNECTION_CLOSE = 0x32,
    CONNECTION_CLOSE_OK = 0x33,

    CHANNEL_OPEN = 0xa,
    CHANNEL_OPEN_OK = 0xb,
    CHANNEL_CLOSE = 0x28,
    CHANNEL_CLOSE_OK = 0x29,

    QUEUE_DECLARE = 0xa,
    QUEUE_DECLARE_OK = 0xb,

    BASIC_PUBLISH = 0x28,
    BASIC_QOS = 0xa,
    BASIC_QOS_OK = 0xb,
    BASIC_CONSUME = 0x14,
    BASIC_CONSUME_OK = 0x15,
    BASIC_ACK = 0x50,
};*/

void processAMQPMessage();

int AMQPConnection(int connfd, int state, int classValue, int methodValue);

#endif // AMQP_H
