#include <string.h>
#include <stdio.h>

#include "amqp.h"
#include "packets.h"

/*  
TO DO:

- free queues
- add message


- arrumar queue que esta desaparecendo com os dados dps da conexão fechar
    - declarar como extern
    - funções void
    - malloc
- publish
- consume
- mudar packet do rabbit
*/

queue queues;

void print(char *recvline, ssize_t length){
    printf("Dados recebidos do cliente (%zd bytes): ", length);
    for (ssize_t i = 0; i < length; i++) {
        printf("%02x ", (unsigned char)recvline[i]);
    }
    printf("\n");
}

void print_messages(int i){
    printf("  [M]:");
    for(int j = 0; j < MAXMESSAGENUMBER;j++){
        if(strcmp(queues.messages[i][j], '\0') != 0){
            printf("%s, ",queues.messages[i][j]);
        }
        else{
            printf("\n");
            break;
        }
    }
}

void print_consumers(int i){
    printf("  [C]:");
    for(int j = 0; j < MAXCONSUMERNUMBER;j++){
        if(queues.consumers[i][j] != 0){
            printf("%d, ",queues.consumers[i][j]);
        }
        else{
            printf("\n");
            break;
        }
    }
}

void print_queues() {
    printf("QUEUE:\n");
    for(int i = 0; i < MAXQUEUESIZE;i++){
        if(strcmp(queues.name[i], '\0') != 0){
            printf("%s\n",queues.name[i]);
            print_consumers(i);
            print_messages(i);
        }
        else{
            printf("\n");
            break; 
        }
    }
    printf("-------------\n");    
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
                    exit(0);
                    break;
                default:
                    printf("Método CONNECTION desconhecido\n");
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
                    printf("Método CHANNEL desconhecido\n");
                    break;
            }
            break;
        case QUEUE:
            switch(method_id){
                 case QUEUE_DECLARE:
                    printf("Cliente enviou o método QUEUE_DECLARE\n");
                    read(connfd, recvline, size);
                    printf("Servidor enviou o método QUEUE_DECLARE_OK\n");
                    queueMethod(connfd, recvline, size);
                    //write(connfd, PACKET_QUEUE_DECLARE_OK, PACKET_QUEUE_DECLARE_OK_SIZE - 1);
                    break;
                default:
                    printf("Método QUEUE desconhecido\n");
                    break;
            }
            break;
        case BASIC:
            switch(method_id){
                case BASIC_PUBLISH:
                    printf("Cliente enviou o método BASIC_PUBLISH\n");
                    publishMethod(connfd, recvline, size);
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
                    printf("Método BASIC desconhecido\n");
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
    //print(recvline, 11);
    if(n == 0) return 0;

    frame->type = (u_int8_t)recvline[0];
    frame->channel = ((u_int16_t)recvline[1] << 8) | (u_int16_t)recvline[2];
    frame->size = ((u_int32_t)recvline[3] << 24) | ((u_int32_t)recvline[4] << 16) | ((u_int32_t)recvline[5] << 8) | (u_int32_t)recvline[6];
    frame->class_id = ((u_int16_t)recvline[7] << 8) | (u_int16_t)recvline[8];
    frame->method_id = ((u_int16_t)recvline[9] << 8) | (u_int16_t)recvline[10];
    
    return 1;
}

/* Modificar */
/* Queue */
void queueMethod(int connfd, char *recvline, u_int32_t size){
    char queueName[MAXQUEUENAMESIZE];
    memcpy(queueName, recvline + 3, size);
    printf("Nome da fila: %s\n", queueName);
    addQueue(queueName);
    printf("Dados da fila: \n");
    print_queues();

    struct AMQPFrame frame;
    frame.type = 1;
    frame.channel = htons(1);
    frame.size = htonl(size + 1);
    frame.class_id = htons(50);
    frame.method_id = htons(11);

    char packet[MAXSIZE];
    int packetSize = 0;

    memcpy(packet + packetSize, (char *)&frame.type, sizeof(frame.type));
    packetSize += sizeof(frame.type);
    memcpy(packet + packetSize, (char *)&frame.channel, sizeof(frame.channel));
    packetSize += sizeof(frame.channel);
    memcpy(packet + packetSize, (char *)&frame.size, sizeof(frame.size));
    packetSize += sizeof(frame.size);
    memcpy(packet + packetSize, (char *)&frame.class_id, sizeof(frame.class_id));
    packetSize += sizeof(frame.class_id);
    memcpy(packet + packetSize, (char *)&frame.method_id, sizeof(frame.method_id));
    packetSize += sizeof(frame.method_id);

    u_int8_t len = strlen(queueName);
    u_int32_t v3 = htonl(0);
    memcpy(packet+packetSize,(char*)&(len),sizeof(len)); 
    packetSize+= sizeof(len);
    memcpy(packet+packetSize,queueName, len); 
    packetSize+= len;
    memcpy(packet+packetSize,(char*)&(v3),sizeof(v3)); 
    packetSize+= sizeof(v3);
    memcpy(packet+packetSize,(char*)&(v3),sizeof(v3)); 
    packetSize+= sizeof(v3);
    memcpy(packet+packetSize, "\xce",1); 
    packetSize+=1;

    write(connfd, packet, packetSize);
}

void* allocateSharedMemory(size_t size){
    void* memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if (memory == MAP_FAILED) {
        fprintf(stderr, "Couldn't malloc shared memory.\n");
        exit(errno);
    }
    return memory;
}

void freeSharedMemory(void* memory, size_t size){
    int err = munmap(memory, size);
    if (err == -1) {
        fprintf(stderr, "Couldn't free shared memory.\n");
        exit(errno);
    }
}

void initializeQueuesData(){
    queues.name = allocateSharedMemory(MAXQUEUESIZE * sizeof(char*));
    queues.messages = allocateSharedMemory(MAXQUEUESIZE * sizeof(char**));
    queues.consumers = allocateSharedMemory(MAXQUEUESIZE * sizeof(int*));

    for (int i = 0; i < MAXQUEUESIZE; i++) {
        queues.name[i] = allocateSharedMemory(MAXQUEUENAMESIZE * sizeof(char));
        queues.name[i][0] = 0;
        queues.messages[i] = allocateSharedMemory(MAXMESSAGENUMBER * sizeof(char*));
        queues.consumers[i] = allocateSharedMemory(MAXCONSUMERNUMBER * sizeof(int));

        for (int j = 0; j < MAXMESSAGENUMBER; j++) {
            queues.messages[i][j] = allocateSharedMemory(MAXMESSAGESIZE * sizeof(char));
            queues.messages[i][j][0] = 0;
            queues.consumers[i][j] = 0;
        }
    }
}

void freeQueuesData(){
    for (int i = 0; i < MAXQUEUESIZE; i++){
        for(int j = 0; j < MAXMESSAGENUMBER; j++){
            freeSharedMemory(queues.messages[i][j], MAXMESSAGESIZE * sizeof(char));
        }
        freeSharedMemory(queues.messages[i], MAXMESSAGENUMBER * sizeof(char*));
        freeSharedMemory(queues.name[i], MAXQUEUENAMESIZE * sizeof(char));
        freeSharedMemory(queues.consumers[i], MAXCONSUMERNUMBER * sizeof(int*));
    }
    freeSharedMemory(queues.name, MAXQUEUESIZE * sizeof(char*));
    freeSharedMemory(queues.messages, MAXQUEUESIZE * sizeof(char**));
    freeSharedMemory(queues.consumers, MAXQUEUESIZE * sizeof(int*));
}

void addQueue(const char *queueName){
    for (int i = 0; i < MAXQUEUESIZE; i++) {
        if (strcmp(queues.name[i], queueName) == 0) {
            printf("A fila '%s' já existe.\n", queueName);
            return;
        } else if (strcmp(queues.name[i], "") == 0) {
            memcpy(queues.name[i], queueName, strlen(queueName));
            printf("Fila '%s' adicionada.\n", queueName);
            return; 
        }
    }
    printf("Não foi possível adicionar a fila. Limite de filas atingido.\n");
}



/* Publish */
void publishMethod(int connfd, char *recvline, u_int32_t size){
    char queueName[MAXQUEUENAMESIZE];
    char messageData[MAXMESSAGESIZE];

    read(connfd, recvline, size - 3);
    memcpy(queueName, recvline + 4, size);
    printf("Nome da fila: %s\n", queueName);

    read(connfd,recvline, 3); //content header type + channel
    read(connfd,recvline, 4); //content header lenght 4 hex bytes
    u_int32_t length = ntohl(*((u_int32_t*)recvline));

    read(connfd,recvline, length + 4);
    read(connfd,recvline, 4);//content body length
    length = ntohl(*((u_int32_t*)recvline));
  
    read(connfd,recvline, length + 1);
    memcpy(messageData, recvline, size);
    /* Mensagem com um caractere desconhecido no final */
    printf("Mensagem: %s\n", messageData);

    addMessage(queueName, messageData);
    printf("Dados da fila: \n");
    print_queues();
}

void addMessage(const char *queueName, const char *message){
    /*printf("Dados da fila: \n");
    print_queues();
    // Procura pela fila com o nome especificado
    for(int i = 0; i < MAXQUEUESIZE; i++){
        if(strcmp(queues.queues[i].name, queueName) == 0){
            printf("A fila '%s' foi encontrada.\n", queueName);
            // Verifica se a fila não está cheia de mensagens
            if(queues.queues[i].numMessages < MAXMESSAGENUMBER){
                printf("A fila '%s' não está cheia.\n", queueName);
                // Encontra a primeira posição vazia para a mensagem
                for(int j = 0; j < MAXMESSAGENUMBER; j++){
                    if(strcmp(queues.queues[i].messages[j].data, "") == 0){
                        // Copia a mensagem para a fila
                        strncpy(queues.queues[i].messages[j].data, message, MAXMESSAGESIZE - 1);
                        queues.queues[i].messages[j].data[MAXMESSAGESIZE - 1] = '\0';
                        queues.queues[i].numMessages++;
                        printf("Mensagem adicionada à fila '%s'.\n", queueName);
                        return;
                    }
                }
            }else{
                printf("A fila '%s' está cheia. Não é possível adicionar mais mensagens.\n", queueName);
                return;
            }
        }
    }*/

    //printf("A fila '%s' não foi encontrada. A mensagem não foi adicionada.\n", queueName);
}

/* Consume */