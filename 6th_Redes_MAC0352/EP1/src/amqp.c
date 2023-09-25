#include <string.h>
#include <stdio.h>

#include "amqp.h"
#include "packets.h"

void processAMQPMessage() {
    printf("processAMQPMessage\n");
    return;
}

void startConnection(int connfd) {
    int state = STATE_CONNECTION_START;
    switch (state) {
        case STATE_CONNECTION_START:
            // Connection start process
            printf("State: STATE_CONNECTION_START\n");
            write(connfd, CONNECTION_START_PACKET, CONNECTION_START_PACKET_SIZE - 1);
            state++;
            printf(state);
            break;
        case STATE_CONNECTION_TUNE:
            // Connection tune process
            printf("State: STATE_CONNECTION_TUNE\n");
            write(connfd, CONNECTION_TUNE_PACKET, CONNECTION_TUNE_PACKET_SIZE - 1);
            state++;
            break;
        case STATE_CONNECTION_OPEN:
            // Connection open process
            printf("State: STATE_CONNECTION_OPEN\n");
            write(connfd, CONNECTION_OPEN_PACKET_OK, CONNECTION_OPEN_PACKET_OK_SIZE - 1);
            state++;
            break;
        case STATE_CHANNEL_OPEN:
            // Channel open process
            printf("State: STATE_CHANNEL_OPEN\n");
            write(connfd, CHANNEL_OPEN_PACKET_OK, CHANNEL_OPEN_PACKET_OK_SIZE - 1);
            state++;
            break;
        default:
            // Process AMQP messages
            printf("State: Default (Processing AMQP messages)\n");
            processAMQPMessage();
            break;
    }
}
