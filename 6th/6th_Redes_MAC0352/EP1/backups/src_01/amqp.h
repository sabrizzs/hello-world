#ifndef AMQP_H
#define AMQP_H

#include <stdint.h> //

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
#define BASIC_DELIVER 0x3c
#define BASIC_ACK 0x50

/*struct AMQPFrame{
    u_int8_t type;
    u_int16_t channel;
    u_int32_t size;
    u_int16_t class_id;
    u_int16_t method_id;
};

readAMQPFrame(int connfd)*/

void AMQPConnection(int connfd, unsigned char classValue, unsigned char methodValue);

#endif // AMQP_H
