#include <string.h>
#include <stdio.h>

#include "amqp.h"
#include "packets.h"

void AMQPConnection(int connfd, unsigned char classValue, unsigned char methodValue) {
    switch (classValue) {
        case CONNECTION:
            switch (methodValue){
                case CONNECTION_START_OK:
                    printf("Cliente enviou o método CONNECTION_START_OK\n");
                    printf("Servidor enviou o método CONNECTION_TUNE\n");
                    write(connfd, PACKET_CONNECTION_TUNE, PACKET_CONNECTION_TUNE_SIZE - 1);
                    break;
                case CONNECTION_TUNE_OK:
                    printf("Cliente enviou o método CONNECTION_TUNE_OK\n");
                    printf("Cliente enviou o método CONNECTION_OPEN\n");
                    printf("Servidor enviou o método CONNECTION_OPEN_OK\n");
                    write(connfd, PACKET_CONNECTION_OPEN_OK, PACKET_CONNECTION_OPEN_OK_SIZE - 1);
                    break;
                case CONNECTION_CLOSE:
                    printf("Cliente enviou o método CONNECTION_CLOSE\n");
                    printf("Servidor enviou o método CONNECTION_CLOSE_OK\n");
                    write(connfd, PACKET_CONNECTION_CLOSE_OK, PACKET_CONNECTION_CLOSE_OK_SIZE - 1);
                    break;
                default:
                    printf("Método desconhecido\n");
                    break;
            }
            break;
        case CHANNEL:
            switch (methodValue){
                case CHANNEL_OPEN:
                    printf("Cliente enviou o método CHANNEL_OPEN\n");
                    printf("Servidor enviou o método CHANNEL_OPEN_OK\n");
                    write(connfd, PACKET_CHANNEL_OPEN_OK, PACKET_CHANNEL_OPEN_OK_SIZE - 1);
                    break;
                case CHANNEL_CLOSE:
                    printf("Cliente enviou o método CHANNEL_CLOSE\n");
                    printf("Servidor enviou o método CHANNEL_CLOSE_OK\n");
                    write(connfd, PACKET_CHANNEL_CLOSE_OK, PACKET_CHANNEL_CLOSE_OK_SIZE - 1);
                    break;
                default:
                    printf("Método desconhecido\n");
                    break;
            }
            break;
        case QUEUE:
            switch(methodValue){
                case QUEUE_DECLARE:
                    printf("Cliente enviou o método QUEUE_DECLARE\n");
                    printf("Servidor enviou o método QUEUE_DECLARE_OK\n");
                    write(connfd, PACKET_QUEUE_DECLARE_OK, PACKET_QUEUE_DECLARE_OK_SIZE - 1);
                    break;
                default:
                    printf("Método desconhecido\n");
                    break;
            }
            break;
        case BASIC:
            switch(methodValue){
                case BASIC_PUBLISH:
                    printf("Cliente enviou o método BASIC_PUBLISH\n");
                    break;
                case BASIC_QOS:
                    printf("Cliente enviou o método BASIC_QOS\n");
                    printf("Servidor enviou o método BASIC_QOS_OK\n");
                    write(connfd, PACKET_BASIC_QOS_OK, PACKET_BASIC_QOS_OK_SIZE - 1);
                    break;
                case BASIC_CONSUME:
                    printf("Cliente enviou o método BASIC_CONUME\n");
                    printf("Servidor enviou o método BASIC_CONSUME_OK\n");
                    write(connfd, PACKET_BASIC_CONSUME_OK, PACKET_BASIC_CONSUME_OK_SIZE - 1);
                    printf("Servidor enviou o método BASIC_DELIVER\n");
                    write(connfd, PACKET_BASIC_DELIVER, PACKET_BASIC_DELIVER_SIZE - 1);
                    break;
                case BASIC_ACK:
                    printf("Cliente enviou o método BASIC_ACK\n");
                    break;
                default:
                    printf("Método desconhecido\n");
                    break;
            }
            break;
        default:
            printf("Servidor enviou o método CONNECTION_START\n");
            write(connfd, PACKET_CONNECTION_START, PACKET_CONNECTION_START_SIZE - 1);
            break;
    }
}
