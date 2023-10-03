#include <string.h>
#include <stdio.h>

#include "amqp.h"
#include "packets.h"

/*  
TO DO:
- declarar nome da fila
- publish
- consume
- mudar packet do rabbit
*/

struct queue queues;

void print(char *recvline, ssize_t length) {
    printf("Dados recebidos do cliente (%zd bytes): ", length);
    for (ssize_t i = 0; i < length; i++) {
        printf("%02x ", (unsigned char)recvline[i]);
    }
    printf("\n");
}

void AMQPConnection(int connfd, char *recvline, u_int32_t size, u_int16_t class_id, u_int16_t method_id){
    switch (class_id) {
        case CONNECTION:
            switch (method_id){
                case CONNECTION_START_OK:
                    printf("Cliente enviou o método CONNECTION_START_OK\n");
                    read(connfd, recvline, size-3);
                    printf("Servidor enviou o método CONNECTION_TUNE\n");
                    write(connfd, PACKET_CONNECTION_TUNE, PACKET_CONNECTION_TUNE_SIZE - 1);
                    break;
                case CONNECTION_TUNE_OK:
                    printf("Cliente enviou o método CONNECTION_TUNE_OK\n");
                    read(connfd, recvline, size-3);
                    break;
                case CONNECTION_OPEN:
                    printf("Cliente enviou o método CONNECTION_OPEN\n");
                    read(connfd, recvline, size-3);
                    printf("Servidor enviou o método CONNECTION_OPEN_OK\n");
                    write(connfd, PACKET_CONNECTION_OPEN_OK, PACKET_CONNECTION_OPEN_OK_SIZE - 1);
                    break;
                case CONNECTION_CLOSE:
                    printf("Cliente enviou o método CONNECTION_CLOSE\n");
                    read(connfd, recvline, size-3);
                    printf("Servidor enviou o método CONNECTION_CLOSE_OK\n");
                    write(connfd, PACKET_CONNECTION_CLOSE_OK, PACKET_CONNECTION_CLOSE_OK_SIZE - 1);
                    break;
                default:
                    printf("Método desconhecido\n");
                    break;
            }
            break;
        case CHANNEL:
            switch (method_id){
                case CHANNEL_OPEN:
                    printf("Cliente enviou o método CHANNEL_OPEN\n");
                    read(connfd, recvline, size-3);
                    printf("Servidor enviou o método CHANNEL_OPEN_OK\n");
                    write(connfd, PACKET_CHANNEL_OPEN_OK, PACKET_CHANNEL_OPEN_OK_SIZE - 1);
                    break;
                case CHANNEL_CLOSE:
                    printf("Cliente enviou o método CHANNEL_CLOSE\n");
                    read(connfd, recvline, size-3);
                    printf("Servidor enviou o método CHANNEL_CLOSE_OK\n");
                    write(connfd, PACKET_CHANNEL_CLOSE_OK, PACKET_CHANNEL_CLOSE_OK_SIZE - 1);
                    break;
                default:
                    printf("Método desconhecido\n");
                    break;
            }
            break;
        case QUEUE:
            switch(method_id){
                 case QUEUE_DECLARE:
                    printf("Cliente enviou o método QUEUE_DECLARE\n");
                    read(connfd, recvline, size);
                    printf("Servidor enviou o método QUEUE_DECLARE_OK\n");
                    queueMethod(recvline, size);
                    write(connfd, PACKET_QUEUE_DECLARE_OK, PACKET_QUEUE_DECLARE_OK_SIZE - 1);
                    break;
                default:
                    printf("Método desconhecido\n");
                    break;
            }
            break;
        case BASIC:
            switch(method_id){
                case BASIC_PUBLISH:
                    printf("Cliente enviou o método BASIC_PUBLISH\n");
                    read(connfd, recvline, size-3);
                    break;
                case BASIC_QOS:
                    printf("Cliente enviou o método BASIC_QOS\n");
                    read(connfd, recvline, size-3);
                    printf("Servidor enviou o método BASIC_QOS_OK\n");
                    write(connfd, PACKET_BASIC_QOS_OK, PACKET_BASIC_QOS_OK_SIZE - 1);
                    break;
                case BASIC_CONSUME:
                    printf("Cliente enviou o método BASIC_CONUME\n");
                    read(connfd, recvline, size-3);
                    printf("Servidor enviou o método BASIC_CONSUME_OK\n");
                    write(connfd, PACKET_BASIC_CONSUME_OK, PACKET_BASIC_CONSUME_OK_SIZE - 1);
                    printf("Servidor enviou o método BASIC_DELIVER\n");
                    write(connfd, PACKET_BASIC_DELIVER, PACKET_BASIC_DELIVER_SIZE - 1);
                    break;
                case BASIC_ACK:
                    printf("Cliente enviou o método BASIC_ACK\n");
                    read(connfd, recvline, size-3);
                    break;
                default:
                    printf("Método desconhecido\n");
                    break;
            }
            break;
    }
}

int sendProtocolHeader(int connfd, char *recvline){
    printf("Cliente enviou o método CONNECTION_START\n");
    read(connfd, recvline, 8);
    print(recvline, 8);
    printf("Servidor enviou o método CONNECTION_START\n");
    write(connfd, PACKET_CONNECTION_START, PACKET_CONNECTION_START_SIZE - 1);
    return 1; 
}

int readAMQPFrame(int connfd, char *recvline, struct AMQPFrame *frame){
    ssize_t n = read(connfd, recvline, 11);
    print(recvline, 11);
    if(n == 0) return 0;

    frame->type = (u_int8_t)recvline[0];
    frame->channel = ((u_int16_t)recvline[1] << 8) | (u_int16_t)recvline[2];
    frame->size = ((u_int32_t)recvline[3] << 24) | ((u_int32_t)recvline[4] << 16) | ((u_int32_t)recvline[5] << 8) | (u_int32_t)recvline[6];
    frame->class_id = ((u_int16_t)recvline[7] << 8) | (u_int16_t)recvline[8];
    frame->method_id = ((u_int16_t)recvline[9] << 8) | (u_int16_t)recvline[10];
    
    return 1;
}

/* Queue */
void queueMethod(char *recvline, u_int32_t size){
    char queueName[MAXQUEUENAMESIZE];
    memcpy(queueName, recvline + 3, size);
    printf("Nome da fila: %s\n", queueName);
}

/* Publisher */

/* Consumer */