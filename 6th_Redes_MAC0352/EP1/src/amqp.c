#include <string.h>
#include <stdio.h>

#include "amqp.h"
#include "packets.h"

void processAMQPMessage() {
    printf("processAMQPMessage\n");
    return;
}

void AMQPConnection(int connfd, unsigned char classValue, unsigned char methodValue) {
    switch (classValue) {
        case CONNECTION:
            switch (methodValue){
                case CONNECTION_START:
                    printf("Servidor enviou o método CONNECTION_START\n");
                    write(connfd, PACKET_CONNECTION_START, PACKET_CONNECTION_START_SIZE - 1);
                    printf("teste\n");
                    break;
                case CONNECTION_START_OK:
                    printf("Cliente enviou o método CONNECTION_START_OK\n");
                    break;
                case CONNECTION_TUNE:
                    printf("Servidor enviou o método CONNECTION_TUNE\n");
                    write(connfd, PACKET_CONNECTION_TUNE, PACKET_CONNECTION_TUNE_SIZE - 1);
                    break;
                case CONNECTION_TUNE_OK:
                    printf("Cliente enviou o método CONNECTION_TUNE_OK\n");
                    break;
                case CONNECTION_OPEN:
                    printf("Cliente enviou o método CONNECTION_OPEN\n");
                    break;
                case CONNECTION_OPEN_OK:
                    printf("Servidor enviou o método CONNECTION_OPEN_OK\n");
                    write(connfd, PACKET_CONNECTION_OPEN_OK, PACKET_CONNECTION_OPEN_OK_SIZE - 1);
                    break;
                case CONNECTION_CLOSE:
                    printf("Cliente enviou o método CONNECTION_CLOSE\n");
                    break;
                case CONNECTION_CLOSE_OK:
                    printf("Servidor enviou o método CONNECTION_CLOSE_OK\n");
                    write(connfd, PACKET_CONNECTION_CLOSE_OK, PACKET_CONNECTION_CLOSE_OK_SIZE - 1);
                    break;
            }
            break;
        case CHANNEL:
            switch (methodValue){
                case CHANNEL_OPEN:
                    printf("Cliente enviou o método CHANNEL_OPEN\n");
                    break;
                case CHANNEL_OPEN_OK:
                    printf("Servidor enviou o método CHANNEL_OPEN_OK\n");
                    write(connfd, PACKET_CHANNEL_OPEN_OK, PACKET_CHANNEL_OPEN_OK_SIZE - 1);
                    break;
                case CHANNEL_CLOSE:
                    printf("Cliente enviou o método CHANNEL_CLOSE\n");
                    break;
                case CHANNEL_CLOSE_OK: 
                    printf("Servidor enviou o método CHANNEL_CLOSE_OK\n");
                    write(connfd, PACKET_CHANNEL_CLOSE_OK, PACKET_CHANNEL_CLOSE_OK_SIZE - 1);
                    break;
            }
            break;
        case QUEUE:
            switch(methodValue){
                case QUEUE_DECLARE:
                    printf("Cliente enviou o método QUEUE_DECLARE\n");
                    break;
                case QUEUE_DECLARE_OK:
                    printf("Servidor enviou o método QUEUE_DECLARE_OK\n");
                    write(connfd, PACKET_QUEUE_DECLARE_OK, PACKET_QUEUE_DECLARE_OK_SIZE - 1);
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
                    break;
                case BASIC_QOS_OK:
                    printf("Servidor enviou o método BASIC_QOS_OK\n");
                    //write();
                    break;
                case BASIC_CONSUME:
                    printf("Cliente enviou o método BASIC_CONUME\n");
                    break;
                case BASIC_CONSUME_OK:
                    printf("Servidor enviou o método BASIC_CONSUME_OK\n");
                    //write();
                    break;
                case BASIC_ACK:
                    printf("Cliente enviou o método BASIC_ACK\n");
                    break;
            }
            break;
    }
}
