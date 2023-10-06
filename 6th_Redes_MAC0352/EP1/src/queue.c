#include "queue.h"
#include "amqp.h"

//queue queues;
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

int get_id(char* name){
    for(int i = 0; i < MAX_QUEUE_SIZE;i++){
        if(strcmp(queues.name[i], name) == 0){
            return i;
        }
    }
    return -1;
}


