#ifndef AMQP_H
#define AMQP_H

#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>

#define MAXQUEUENAMESIZE 100
#define MAXQUEUESIZE 100
#define MAXMESSAGESIZE 100
#define MAXCONSUMERNUMBER 100
#define MAXMESSAGENUMBER 100

#define MAXSIZE 4096

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

struct AMQPFrame{
    u_int8_t type;
    u_int16_t channel;
    u_int32_t size;
    u_int16_t class_id;
    u_int16_t method_id;
};
/*
struct message{
    char data[MAXMESSAGESIZE];
    int consumers[MAXCONSUMERNUMBER];
    int numConsumers;
};

struct queue{
    char name[MAXQUEUENAMESIZE];
    struct message messages[MAXMESSAGENUMBER];
    int numMessages;
};

struct queues{
    struct queue queues[MAXQUEUESIZE];
    int numQueues;
};
*/

typedef struct queue{
    char** name;
    char*** messages;
    int** consumers;
    int numConsumers;
    int numMessages;
    int numQueues;
} queue;

extern queue queues;

void print(char *recvline, ssize_t length);

void print_queues();

void AMQPConnection(int connfd, char *recvline, u_int32_t size, u_int16_t class_id, u_int16_t method_id);

int sendProtocolHeader(int connfd, char *recvline);

int readAMQPFrame(int connfd, char *recvline, struct AMQPFrame *frame);

void queueMethod(int connfd, char *recvline, u_int32_t size);

void* allocateSharedMemory(size_t size);

void initializeQueuesData();

void freeQueuesData();

void addQueue(const char *queue_name);

void publishMethod(int connfd, char *recvline, u_int32_t size);

void addMessage(const char *queueName, const char *message);

#endif // AMQP_H
