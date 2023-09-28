#include <string.h>
#include <stdio.h>

#include "amqp.h"
#include "packets.h"

void processAMQPMessage() {
    printf("processAMQPMessage\n");
    return;
}

void AMQPConnection(int connfd, unsigned char classValue, unsigned char methodValue) {
    printf("AMQPConnection function\n");
    printf("classValue: %x, methodValue: %x\n", classValue, methodValue);

    printf("Classes:\n");
    printf("CONNECTION: %x\n", CONNECTION);
    printf("CHANNEL: %x\n", CHANNEL);
    printf("QUEUE: %x\n", QUEUE);
    printf("BASIC: %x\n", BASIC);
    
    printf("\nMethods:\n");
    printf("CONNECTION_START: %x\n", CONNECTION_START);
    printf("CONNECTION_START_OK: %x\n", CONNECTION_START_OK);
    printf("CONNECTION_TUNE: %x\n", CONNECTION_TUNE);
    printf("CONNECTION_TUNE_OK: %x\n", CONNECTION_TUNE_OK);
    printf("CONNECTION_OPEN: %x\n", CONNECTION_OPEN);
    printf("CONNECTION_OPEN_OK: %x\n", CONNECTION_OPEN_OK);
    printf("CONNECTION_CLOSE: %x\n", CONNECTION_CLOSE);
    printf("CONNECTION_CLOSE_OK: %x\n", CONNECTION_CLOSE_OK);
    printf("CHANNEL_OPEN: %x\n", CHANNEL_OPEN);
    printf("CHANNEL_OPEN_OK: %x\n", CHANNEL_OPEN_OK);
    printf("CHANNEL_CLOSE: %x\n", CHANNEL_CLOSE);
    printf("CHANNEL_CLOSE_OK: %x\n", CHANNEL_CLOSE_OK);
    printf("QUEUE_DECLARE: %x\n", QUEUE_DECLARE);
    printf("QUEUE_DECLARE_OK: %x\n", QUEUE_DECLARE_OK);
    printf("BASIC_PUBLISH: %x\n", BASIC_PUBLISH);
    printf("BASIC_QOS: %x\n", BASIC_QOS);
    printf("BASIC_QOS_OK: %x\n", BASIC_QOS_OK);
    printf("BASIC_CONSUME: %x\n", BASIC_CONSUME);
    printf("BASIC_CONSUME_OK: %x\n", BASIC_CONSUME_OK);
    printf("BASIC_ACK: %x\n", BASIC_ACK);

    switch (classValue) {
        case CONNECTION:
            printf("case CONNECTION\n");
            switch (methodValue){
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
                default:
                    printf("Método desconhecido\n");
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
                default:
                    printf("Método desconhecido\n");
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
