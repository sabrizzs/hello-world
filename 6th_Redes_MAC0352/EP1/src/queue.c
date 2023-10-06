#include "queue.h"
#include "amqp.h"

queue queues;
char* empty = "\0";

void* malloc_shared_data(size_t size){
    void* m = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,0,0);
    return m;
}

//https://www.ibm.com/docs/en/i/7.2?topic=ssw_ibm_i_72/apis/munmap.html
void free_shared_data(void* p, size_t size){
    munmap(p, size);
}

void initialize_structure_queues(){
    for(int i=0; i < MAX_QUEUE_SIZE;i++){
        queues.name[i] = malloc_shared_data(MAX_QUEUE_NAME_SIZE * sizeof(char));
        queues.name[i][0] = 0;
        queues.messages[i] = malloc_shared_data(MAX_MESSAGE_NUMBER * sizeof(char*));
        queues.consumers[i] = malloc_shared_data(MAX_CONSUMER_NUMBER * sizeof(int)); 
        for(int j=0; j < MAX_MESSAGE_NUMBER;j++){
            queues.messages[i][j] = malloc_shared_data(MAX_MESSAGE_SIZE * sizeof(char));
            queues.messages[i][j][0] = 0;
            queues.consumers[i][j] = 0;
        }
    }
}

void create_structure_queues(){
    queues.name = malloc_shared_data(MAX_QUEUE_SIZE * sizeof(char*));
    queues.consumers = malloc_shared_data(MAX_QUEUE_SIZE * sizeof(int*));
    queues.messages = malloc_shared_data(MAX_QUEUE_SIZE * sizeof(char**));
    initialize_structure_queues();
}

void free_structure_queues(){
    for (int i = 0; i < MAX_QUEUE_SIZE; i++){
        for(int j = 0; j < MAX_MESSAGE_NUMBER; j++){
            free_shared_data(queues.messages[i][j], MAX_MESSAGE_SIZE * sizeof(char));
        }
        free_shared_data(queues.messages[i], MAX_MESSAGE_NUMBER * sizeof(char*));
        free_shared_data(queues.name[i], MAX_QUEUE_NAME_SIZE * sizeof(char));
        free_shared_data(queues.consumers[i], MAX_CONSUMER_NUMBER * sizeof(int*));
    }
    free_shared_data(queues.name, MAX_QUEUE_SIZE * sizeof(char*));
    free_shared_data(queues.messages, MAX_QUEUE_SIZE * sizeof(char**));
    free_shared_data(queues.consumers, MAX_QUEUE_SIZE * sizeof(int*));
}

void add_queue(char* name){
    int i;
    if((i = get_id(name)) != -1){
        printf("    [-]add_queue: %s alredy declared\n", name);
    }
    else if((i = get_id(empty)) == -1){
        printf("    [-]add_queue: get_id(%s): queue not found\n", empty);
    }
    else{
        memcpy(queues.name[i], name, strlen(name));
        printf("    [+]add_queue: %s %d %ld\n", queues.name[i], i, strlen(queues.name[i]));
    }
    return;
}

void publish(char* name, char* msg){
    int i;
    if((i = get_id(name)) == -1){
        printf("    [-]publish: get_id(%s): queue not found\n", name);
        return;
    }
    for(int j = 0; j < MAX_MESSAGE_NUMBER; j++){
        if(strcmp(queues.messages[i][j],empty) == 0){
            memcpy(queues.messages[i][j],msg,MAX_MESSAGE_SIZE);
            printf("    [+]publish: %s %d %d %s\n",name, i, j, queues.messages[i][j]);
            return;
        }
    }
}

void add_consumer(char* name, int* connfd){
    int i;
    if((i = get_id(name)) == -1){
        printf("    [-]add_consumer: get_id(%s): queue not found\n", name);
        return;
    }
    for(int j = 0; j < MAX_QUEUE_SIZE; j++){
        if(queues.consumers[i][j] == 0){
            memcpy(&queues.consumers[i][j],connfd, sizeof(int));
            printf("    [+]add_consumer: %s %d %d\n",name, *connfd, j);
            print_consumers(i);
            return;
        }
    }    
}

int move_consumer_to_last_position(int i){
    int swap = queues.consumers[i][0];
    for(int j = 0; j < MAX_CONSUMER_NUMBER; j++)
        if(queues.consumers[i][j+1] != 0){
            memcpy(&queues.consumers[i][j],&queues.consumers[i][j+1],sizeof(int));
        }
        else if(queues.consumers[i][j+1] == 0){
            memcpy(&queues.consumers[i][j], &swap, sizeof(int));
            return 0;
        }
    return -1;
}

void remove_message(int i){
    memcpy(queues.messages[i][0], "\0", sizeof(char));
    for(int j = 0; j < MAX_MESSAGE_NUMBER; j++){
        if(strcmp(queues.messages[i][j+1],empty) != 0){
            memcpy(queues.messages[i][j],queues.messages[i][j+1], strlen(queues.messages[i][j+1]));
            memcpy(queues.messages[i][j+1], "\0", sizeof(char));
        }else{
            break;
        }
    }
}

int consume(char* name, int* connfd, char* msg){
    int i;
    if((i = get_id(name)) == -1){
        printf("    [-]consume: get_id(%s): queue not found\n", name);
        return -1;
    }
    if(queues.consumers[i][0] == 0 || strcmp(queues.messages[i][0], empty)==0){
        printf("    [-]consume: %s %d %s\n", name, queues.consumers[i][0], queues.messages[i][0]);
        return -1;
    }
    memcpy(connfd, &queues.consumers[i][0],sizeof(int));
    memcpy(msg, queues.messages[i][0], MAX_MESSAGE_SIZE);
    printf("    [+]consume: %s %d %d %s\n",name, i, *connfd, msg);
    move_consumer_to_last_position(i);
    remove_message(i);
    return 0;   
}

int get_id(char* name){
    for(int i = 0; i < MAX_QUEUE_SIZE;i++){
        if(strcmp(queues.name[i], name) == 0){
            return i;
        }
    }
    return -1;
}

void print_consumers(int i){
    printf("  [C]:");
    for(int j = 0; j < MAX_CONSUMER_NUMBER;j++){
        if(queues.consumers[i][j] != 0){
            printf("%d, ",queues.consumers[i][j]);
        }
        else{
            printf("\n");
            break;
        }
    }
}

void print_names(){
    printf("    [N]:\n");
    for(int i = 0; i < MAX_QUEUE_SIZE;i++){
        if(strcmp(queues.name[i],empty) != 0){
            printf("%s ",queues.name[i]);
        }
        else{
            printf("\n");
            break; 
        }
    }
}

void print_messages(int i){
    printf("  [M]:");
    for(int j = 0; j < MAX_MESSAGE_NUMBER;j++){
        if(strcmp(queues.messages[i][j], empty) != 0){
            printf("%s, ",queues.messages[i][j]);
        }
        else{
            printf("\n");
            break;
        }
    }
}
void print_queues(){
    printf("<MEMORY>:\n");
    for(int i = 0; i < MAX_QUEUE_SIZE;i++){
        if(strcmp(queues.name[i],empty) != 0){
            printf("%s\n",queues.name[i]);
            print_consumers(i);
            print_messages(i);
        }
        else{
            printf("\n");
            break; 
        }
    }
    printf("</MEMORY>:\n");
}
