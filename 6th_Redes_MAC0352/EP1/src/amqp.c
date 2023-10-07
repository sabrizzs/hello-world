#include "amqp.h"
#include "packets.h"

/*  
TO DO:

- publish
    - mensagem com um caractere estranho no final

antes da string
o hex byte anterior ao primeir9 caractere
eh o tamanho dela
eu leio esse hex byte e leio o buffer com base no valor q ele fornece

- mudar packet do rabbit

- fazer uma função que acha fila
- se algo der errado é pq to usando "" em vez de '\0'
*/

queue queues;

void print(char *recvline, ssize_t length){
    printf("Dados recebidos do cliente (%zd bytes): ", length);
    for (ssize_t i = 0; i < length; i++) {
        printf("%02x ", (unsigned char)recvline[i]);
    }
    printf("\n");
}

void print_queues() {
    printf("QUEUES ------\n");
    for(int i = 0; i < MAXQUEUESIZE; i++){
        if(strcmp(queues.name[i], "") != 0){
            printf(" Fila: %s\n", queues.name[i]);
            printf(" Consumers: ");
            for(int j = 0; j < MAXCONSUMERNUMBER; j++){
                if(queues.consumers[i][j] != 0){
                    printf("%d, ", queues.consumers[i][j]);
                } else {
                    break;
                }
            }
            printf("\n");
            printf(" Messages: ");
            for(int k = 0; k < MAXMESSAGENUMBER; k++){
                if(strcmp(queues.messages[i][k], "") != 0){
                    printf("%s, ", queues.messages[i][k]);
                } else {
                    break;
                }
            }
            printf("\n");
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
                    queueMethod(connfd, recvline, size);
                    printf("Servidor enviou o método QUEUE_DECLARE_OK\n");
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
                    printf("Servidor enviou o método BASIC_CONSUME_OK\n");
                    consumeMethod(connfd, recvline, size);
                    printf("Servidor enviou o método BASIC_DELIVER\n");
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

    /*
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
    */

    char packet[MAXSIZE];
    int packetSize = 0;
    queuePacket(queueName, packet, &packetSize, size);

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

    // read the queue name from the received data
    read(connfd, recvline, size - 3);
    memcpy(queueName, recvline + 4, size);
    printf("Nome da fila: %s\n", queueName);

    // read content header information (type, channel, length)
    read(connfd,recvline, 3); 
    read(connfd,recvline, 4); 
    u_int32_t length = ntohl(*((u_int32_t*)recvline));

    // read the content body
    read(connfd,recvline, length + 4);
    read(connfd,recvline, 4);//content body length
    length = ntohl(*((u_int32_t*)recvline));
    printf("Tamanho da mensagem: %d\n", length);

    // read the message data
    read(connfd, recvline, length + 1);
    memcpy(messageData, recvline, length);
    messageData[length] = '\0';
    printf("Mensagem: %s\n", messageData);

    addMessage(queueName, messageData);
    printf("Dados da fila: \n");
    print_queues();
}

void addMessage(const char *queueName, const char *message){

    // find the index of the specified queue
    int index = -1;
    for(int i = 0; i < MAXQUEUESIZE; i++){
        if(strcmp(queues.name[i], queueName) == 0) {
            index = i;
            printf("Fila '%s' encontrada no index %d.\n", queueName, index);
            break;
        }
    }

    if(index == -1){
        printf("Fila '%s' não encontrada.\n", queueName);
        return;
    }

    // find an empty slot in the queue's message array and add the message
    for(int i = 0; i < MAXMESSAGENUMBER; i++){
        if(strcmp(queues.messages[index][i], "") == 0) {
            memcpy(queues.messages[index][i], message, MAXMESSAGESIZE);
            printf("Mensagem adicionada à fila '%s'.\n", queueName);
            return;
        }
    }
    printf("A fila '%s' está cheia. Não é possível adicionar mais mensagens.\n", queueName);
}

/* Modificar */
/* Consume */
void consumeMethod(int connfd, char *recvline, u_int32_t size){
    char queueName[MAXQUEUENAMESIZE];
    
    // read the queue name from the client
    read(connfd, recvline, size - 3);
    memcpy(queueName, recvline + 3, size);
    printf("Nome da fila do consumer: %s\n", queueName);

    // add the consumer to the queue
    addConsumer(queueName, connfd);
    write(connfd, PACKET_BASIC_CONSUME_OK, PACKET_BASIC_CONSUME_OK_SIZE - 1);

    /* deliver message */
    char message[MAXMESSAGESIZE];

    /* check if the queue exists and has messages or consumers */
    int index = -1;
    for(int i = 0; i < MAXQUEUESIZE; i++){
        if (strcmp(queues.name[i], queueName) == 0) {
            index = i;
            break;
        }
    }
    if(index == -1){
        printf("Fila '%s' não encontrada na função consumeMethod.\n", queueName);
        return;
    }
    if(queues.consumers[index][0] == 0 || strcmp(queues.messages[index][0], "") == 0){
        printf("Não há consumidores ou mensagens na fila %s.\n", queueName);
        return;
    }

    /* get the consumer identifier from position 0 of the queue, as well as the message */
    int id = queues.consumers[index][0];
    memcpy(message, queues.messages[index][0], MAXMESSAGESIZE);
    printf("Consumer \"%d\" irá consumir a mensagem \"%s\".\n", id, message);

    /* move the consumer to the end of the queue */
    printf("Consumer \"%d\" irá para o final da fila \"%s\".\n", id, queueName);
    moveConsumer(index);
    print_queues();

    /* remove the message from the first position of the queue */
    printf("Mensagem \"%s\" da primeira posição da fila \"%s\" será removida.\n", message, queueName);
    removeMessage(index);
    print_queues();

    /* create a packet for the client */
    struct AMQPFrame frame;
    frame.type = 1;
    frame.channel = htons(0x1);
    frame.size = htonl(47 + strlen(queueName));
    frame.class_id = htons(60);
    frame.method_id = htons(60);

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

    char data[] = "\x1f\x61\x6d\x71\x2e\x63\x74\x61\x67\x2d\x55\x6e\x73\x75\x6f\x31\x58\x6c\x68\x46\x58\x41\x6e\x45\x68\x6f\x58\x76\x58\x68\x59\x41\x00\x00\x00\x00\x00\x00\x00\x01\x00";
    u_int8_t queueNameSize = strlen(queueName);

    memcpy(packet + packetSize, data, 42); 
    packetSize += 42;
    memcpy(packet + packetSize, (char*)&(queueNameSize), sizeof(queueNameSize));
    packetSize += sizeof(queueNameSize);
    memcpy(packet + packetSize, queueName, queueNameSize);
    packetSize += queueNameSize;
    memcpy(packet + packetSize, "\xce", 1);
    packetSize += 1;

    u_int8_t type = 2;
    u_int16_t channel = htons(1);
    u_int32_t length = htonl(15);
    u_int16_t class_id = htons(60);
    u_int16_t wt = htons(0);
    u_int16_t pf = htons(4096);
    u_int8_t dl = 1;

    u_int32_t left = (u_int32_t) (strlen(message) >> 32);
    u_int32_t right = (u_int32_t) (strlen(message) & 0xffff);    
    u_int32_t new_left = htonl(right);
    u_int32_t new_right = htonl(left);
    u_int64_t bl =  ((u_int64_t) new_left << 32) | ((u_int64_t) new_right);

    memcpy(packet + packetSize, (char*)&type, sizeof(type)); 
    packetSize += sizeof(type);
    memcpy(packet + packetSize, (char*)&channel, sizeof(channel)); 
    packetSize += sizeof(channel);
    memcpy(packet + packetSize, (char*)&length, sizeof(length)); 
    packetSize += sizeof(length);
    memcpy(packet + packetSize, (char*)&class_id, sizeof(class_id)); 
    packetSize += sizeof(class_id);
    memcpy(packet + packetSize, (char*)&wt, sizeof(wt)); 
    packetSize += sizeof(wt);
    memcpy(packet + packetSize, (char*)&bl, sizeof(bl)); 
    packetSize += sizeof(bl);
    memcpy(packet + packetSize, (char*)&pf, sizeof(pf)); 
    packetSize += sizeof(pf);
    memcpy(packet + packetSize, (char*)&dl, sizeof(dl)); 
    packetSize += sizeof(dl);
    memcpy(packet + packetSize, "\xce", 1); packetSize += 1;

    type = 3;
    length = htonl((u_int32_t)strlen(message));

    memcpy(packet + packetSize, (char*)&type, sizeof(type)); 
    packetSize += sizeof(type);
    memcpy(packet + packetSize, (char*)&channel, sizeof(channel)); 
    packetSize += sizeof(channel);
    memcpy(packet + packetSize, (char*)&length, sizeof(length)); 
    packetSize += sizeof(length);
    memcpy(packet + packetSize, message, strlen(message)); 
    packetSize += strlen(message);
    memcpy(packet + packetSize, "\xce", 1); 
    packetSize += 1;

    // send the constructed packet to the client
    write(connfd, packet, packetSize);
}

void addConsumer(const char *queueName, int connfd){

    // find the queue index based on its name
    int index = -1;
    for(int i = 0; i < MAXQUEUESIZE; i++){
        if (strcmp(queues.name[i], queueName) == 0) {
            index = i;
            printf("Fila '%s' encontrada no índice %d.\n", queueName, index);
            break;
        }
    }
    if(index == -1){
        printf("Fila '%s' não encontrada.\n", queueName);
        return;
    }

    printf("Connfd do consumer: %d\n", connfd);

    // add the consumer to the queue
    for(int i = 0; i < MAXCONSUMERNUMBER; i++){
        if (queues.consumers[index][i] == 0) {
            queues.consumers[index][i] = connfd;
            printf("Consumer %d adicionado à fila '%s'.\n", connfd, queueName);
            return;
        }
    }
    printf("A fila '%s' está cheia de consumidores.\n", queueName);
}

void moveConsumer(int index){
    int firstConsumer = queues.consumers[index][0];
    for(int i = 0; i < MAXCONSUMERNUMBER - 1; i++){
        if(queues.consumers[index][i + 1] != 0){
            queues.consumers[index][i] = queues.consumers[index][i + 1];
        }else{
            // place the first consumer at the end of the queue
            queues.consumers[index][i] = firstConsumer;
            printf("Consumer com connfd \"%d\" movido para o final da fila.\n", firstConsumer);
            return;
        }
    }
    printf("Não foi possível mover o consumer \"%d\" para o final da fila.\n", firstConsumer);
}

/* dando errado */
void removeMessage(int index){
    // clear the message at the front of the queue
    //memcpy(queues.messages[index][0], '\0', sizeof(char));
    memset(queues.messages[index][0], 0, MAXMESSAGESIZE);
    for(int i = 0; i < MAXMESSAGENUMBER - 1; i++) {
        if(strcmp(queues.messages[index][i + 1], "") != 0){
            memcpy(queues.messages[index][i],queues.messages[index][i + 1], strlen(queues.messages[index][i + 1]));
            //memcpy(queues.messages[index][i + 1], "", sizeof(char));
            memset(queues.messages[index][i + 1], 0, MAXMESSAGESIZE);
        } else {
            return;
        }
    }
}
