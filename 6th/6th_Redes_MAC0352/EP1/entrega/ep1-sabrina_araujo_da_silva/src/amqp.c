#include "amqp.h"
#include "packets.h"

queue queues;

void print(char *recvline, ssize_t length){
    printf("Data received from the client (%zd bytes): ", length);
    for (ssize_t i = 0; i < length; i++) {
        printf("%02x ", (unsigned char)recvline[i]);
    }
    printf("\n");
}

void print_queues() {
    printf("------ QUEUE ------\n");
    for(int i = 0; i < MAXQUEUESIZE; i++){
        if(strcmp(queues.name[i], "") != 0){
            printf(" Queue name: %s\n", queues.name[i]);
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
    printf("-------------------\n");    
}

void AMQPConnection(int connfd, char *recvline, u_int32_t size, u_int16_t class_id, u_int16_t method_id){
    switch (class_id) {
        case CONNECTION:
            switch (method_id){
                case CONNECTION_START_OK:
                    printf("[CLIENT] CONNECTION_START_OK\n");
                    read(connfd, recvline, size-3);
                    printf("[SERVER] CONNECTION_TUNE\n");
                    write(connfd, PACKET_CONNECTION_TUNE, PACKET_CONNECTION_TUNE_SIZE - 1);
                    break;
                case CONNECTION_TUNE_OK:
                    printf("[CLIENT] CONNECTION_TUNE_OK\n");
                    read(connfd, recvline, size-3);
                    break;
                case CONNECTION_OPEN:
                    printf("[CLIENT] CONNECTION_OPEN\n");
                    read(connfd, recvline, size-3);
                    printf("[SERVER] CONNECTION_OPEN_OK\n");
                    write(connfd, PACKET_CONNECTION_OPEN_OK, PACKET_CONNECTION_OPEN_OK_SIZE - 1);
                    break;
                case CONNECTION_CLOSE:
                    printf("[CLIENT] CONNECTION_CLOSE\n");
                    read(connfd, recvline, size-3);
                    printf("[SERVER] CONNECTION_CLOSE_OK\n");
                    write(connfd, PACKET_CONNECTION_CLOSE_OK, PACKET_CONNECTION_CLOSE_OK_SIZE - 1);
                    exit(0);
                    break;
                default:
                    printf("Unknown CONNECTION method\n");
                    break;
            }
            break;
        case CHANNEL:
            switch (method_id){
                case CHANNEL_OPEN:
                    printf("[CLIENT] CHANNEL_OPEN\n");
                    read(connfd, recvline, size-3);
                    printf("[SERVER] CHANNEL_OPEN_OK\n");
                    write(connfd, PACKET_CHANNEL_OPEN_OK, PACKET_CHANNEL_OPEN_OK_SIZE - 1);
                    break;
                case CHANNEL_CLOSE:
                    printf("[CLIENT] CHANNEL_CLOSE\n");
                    read(connfd, recvline, size-3);
                    printf("[SERVER] CHANNEL_CLOSE_OK\n");
                    write(connfd, PACKET_CHANNEL_CLOSE_OK, PACKET_CHANNEL_CLOSE_OK_SIZE - 1);
                    break;
                default:
                    printf("Unknown CHANNEL method\n");
                    break;
            }
            break;
        case QUEUE:
            switch(method_id){
                 case QUEUE_DECLARE:
                    printf("[CLIENT] QUEUE_DECLARE\n");
                    read(connfd, recvline, size);
                    queueMethod(connfd, recvline, size);
                    printf("[SERVER] QUEUE_DECLARE_OK\n");
                    break;
                default:
                    printf("Unknown QUEUE method\n");
                    break;
            }
            break;
        case BASIC:
            switch(method_id){
                case BASIC_PUBLISH:
                    printf("[CLIENT] BASIC_PUBLISH\n");
                    publishMethod(connfd, recvline, size);
                    break;
                case BASIC_QOS:
                    printf("[CLIENT] BASIC_QOS\n");
                    read(connfd, recvline, size-3);
                    printf("[SERVER] BASIC_QOS_OK\n");
                    write(connfd, PACKET_BASIC_QOS_OK, PACKET_BASIC_QOS_OK_SIZE - 1);
                    break;
                case BASIC_CONSUME:
                    printf("[CLIENT] BASIC_CONUME\n");
                    printf("[SERVER] BASIC_CONSUME_OK\n");
                    consumeMethod(connfd, recvline, size);
                    printf("[SERVER] BASIC_DELIVER\n");
                    break;
                case BASIC_ACK:
                    printf("[CLIENT] BASIC_ACK\n");
                    read(connfd, recvline, size-3);
                    break;
                default:
                    printf("Unknown BASIC method\n");
                    break;
            }
            break;
    }
}

int sendProtocolHeader(int connfd, char *recvline){
    printf("[CLIENT] CONNECTION_START\n");
    read(connfd, recvline, 8);
    printf("[SERVER] CONNECTION_START\n");
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

/* Queue */
void queueMethod(int connfd, char *recvline, u_int32_t size){
    /* extract the queue name from the received data */ 
    char queueName[MAXQUEUENAMESIZE];
    memcpy(queueName, recvline + 3, size);
    addQueue(queueName);

    /* create a packet to respond to the client */
    char packet[MAXSIZE];
    int packetSize = 0;
    queuePacket(queueName, packet, &packetSize, size);

    /* send the constructed packet back to the client */ 
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
    /* allocate shared memory for queues */ 
    queues.name = allocateSharedMemory(MAXQUEUESIZE * sizeof(char*));
    queues.messages = allocateSharedMemory(MAXQUEUESIZE * sizeof(char**));
    queues.consumers = allocateSharedMemory(MAXQUEUESIZE * sizeof(int*));

    for(int i = 0; i < MAXQUEUESIZE; i++){
        /* allocate shared memory for queue names, queue messages and queue consumers */ 
        queues.name[i] = allocateSharedMemory(MAXQUEUENAMESIZE * sizeof(char));
        queues.name[i][0] = 0;
        queues.messages[i] = allocateSharedMemory(MAXMESSAGENUMBER * sizeof(char*));
        queues.consumers[i] = allocateSharedMemory(MAXCONSUMERNUMBER * sizeof(int));

        for(int j = 0; j < MAXMESSAGENUMBER; j++){
            /* initialize each message and each consumer */ 
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
            printf("[X] Queue \"%s\" already exists.\n", queueName);
            return;
        } else if (strcmp(queues.name[i], "") == 0) {
            /* if an empty slot is found, copy the queue name */ 
            memcpy(queues.name[i], queueName, strlen(queueName));
            printf("[V] Queue \"%s\" added.\n", queueName);
            return; 
        }
    }
    printf("[X] Unable to add the queue \"%s\". Queue limit reached.\n", queueName);
}

int findQueueIndex(const char *queueName) {
    for (int i = 0; i < MAXQUEUESIZE; i++) {
        if (strcmp(queues.name[i], queueName) == 0) {
            return i;  /* queue found, return its index */ 
        }
    }
    printf("[X] Queue \"%s\" not found in the consumeMethod function.\n", queueName);
    return -1;
}

/* Publish */
void publishMethod(int connfd, char *recvline, u_int32_t size){
    char queueName[MAXQUEUENAMESIZE];
    char messageData[MAXMESSAGESIZE];
    u_int32_t length = 0;

    /* read the queue name from the received data */ 
    read(connfd, recvline, size - 3);
    memcpy(queueName, recvline + 4, size);

    printf("[INFO] Publisher's queue name: \"%s\".\n", queueName);

    /* read content header information (type, channel, length) */ 
    read(connfd, recvline, 7);
    length = ntohl(*((u_int32_t*) (recvline + 3))); //

    /* read the content body */ 
    read(connfd, recvline, length + 4);
    read(connfd, recvline, 4);//content body length
    length = ntohl(*((u_int32_t*) recvline));

    /* read the message data */ 
    read(connfd, recvline, length + 1);
    memcpy(messageData, recvline, length);
    messageData[length] = '\0';
    addMessage(queueName, messageData);
}

void addMessage(const char *queueName, const char *message){

    /* find the index of the specified queue */ 
    int index = findQueueIndex(queueName);
    if (index == -1) return;

    /* find an empty slot in the queue's message array and add the message */ 
    for(int i = 0; i < MAXMESSAGENUMBER; i++){
        if(strcmp(queues.messages[index][i], "") == 0) {
            memcpy(queues.messages[index][i], message, MAXMESSAGESIZE);
            printf("[V] Message \"%s\" added to the queue \"%s\".\n", message, queueName);
            return;
        }
    }
    printf("[X] The queue \"%s\" is full. Cannot add more messages.\n", queueName);
}

/* Consume */
void consumeMethod(int connfd, char *recvline, u_int32_t size){
    char queueName[MAXQUEUENAMESIZE];
    
    /* read the queue name from the client */ 
    read(connfd, recvline, size - 3);
    memcpy(queueName, recvline + 3, size);
    printf("[INFO] Consumer's queue name: \"%s\".\n", queueName);

    /* add the consumer to the queue */ 
    addConsumer(queueName, connfd);
    write(connfd, PACKET_BASIC_CONSUME_OK, PACKET_BASIC_CONSUME_OK_SIZE - 1);

    /* deliver message */
    char message[MAXMESSAGESIZE];

    /* check if the queue exists and has messages */
    int index = findQueueIndex(queueName);
    if (index == -1) return;

    if(strcmp(queues.messages[index][0], "") == 0){
        printf("[X] There are no messages in the queue \"%s\".\n", queueName);
        return;
    }

    /* get the message from position 0 of the queue */
    memcpy(message, queues.messages[index][0], MAXMESSAGESIZE);
    printf("[INFO] Consumer \"%d\" will consume the message \"%s\".\n", queues.consumers[index][0], message);
    /* move the consumer to the end of the queue */
    moveConsumer(index);
    printf("[V] Consumer \"%d\" moved to the end of the queue \"%s\".\n", queues.consumers[index][0], queueName);

    print_queues();

    /* remove the message from the first position of the queue */
    removeMessage(index);
    printf("[V] Message \"%s\" from the first position of the queue \"%s\" has been removed.\n", message, queueName);

    print_queues();

    char packet[MAXSIZE];
    int packetSize = 0;
    consumePacket(queueName, packet, &packetSize, message);

    /* send the constructed packet to the client */
    write(connfd, packet, packetSize);
}

void addConsumer(const char *queueName, int connfd){

    /* find the queue index based on its name */ 
    int index = findQueueIndex(queueName);
    if (index == -1) return;

    /* add the consumer to the queue */ 
    for(int i = 0; i < MAXCONSUMERNUMBER; i++){
        if (queues.consumers[index][i] == 0) {
            queues.consumers[index][i] = connfd;
            printf("[V] Consumer \"%d\" added to the queue \"%s\".\n", connfd, queueName);
            return;
        }
    }
    printf("[X] The queue \"%s\" is full of consumers.\n", queueName);
}

void moveConsumer(int index){
    /**
     * Moves the consumer to the end of the queue, implementing a round-robin distribution.
     * This function is used to manage the order in which multiple consumers receive messages
     * from a shared queue. Round-robin distribution ensures that each consumer takes its turn
     * to process messages.  
     **/

    int firstConsumer = queues.consumers[index][0];
    for(int i = 0; i < MAXCONSUMERNUMBER - 1; i++){
        if(queues.consumers[index][i + 1] != 0){
            queues.consumers[index][i] = queues.consumers[index][i + 1];
        }else{
            queues.consumers[index][i] = firstConsumer;
            return;
        }
    }
    printf("[X] Unable to move consumer \"%d\" to the end of the queue.\n", firstConsumer);
}

void removeMessage(int index){
    /* clear the message at the front of the queue */ 
    memset(queues.messages[index][0], 0, MAXMESSAGESIZE);
    for(int i = 0; i < MAXMESSAGENUMBER - 1; i++) {
        if(strcmp(queues.messages[index][i + 1], "") != 0){
            memcpy(queues.messages[index][i],queues.messages[index][i + 1], strlen(queues.messages[index][i + 1]));
            memset(queues.messages[index][i + 1], 0, MAXMESSAGESIZE);
        } else return;
    }
}
