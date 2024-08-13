#include <sys/types.h>
#include "amqp.h"

const char PACKET_CONNECTION_START[] = 
"\x01\x00\x00\x00\x00\x01\xfa\x00\x0a\x00\x0a\x00\x09\x00\x00\x01" \
"\xd5\x0c\x63\x61\x70\x61\x62\x69\x6c\x69\x74\x69\x65\x73\x46\x00" \
"\x00\x00\xc7\x12\x70\x75\x62\x6c\x69\x73\x68\x65\x72\x5f\x63\x6f" \
"\x6e\x66\x69\x72\x6d\x73\x74\x01\x1a\x65\x78\x63\x68\x61\x6e\x67" \
"\x65\x5f\x65\x78\x63\x68\x61\x6e\x67\x65\x5f\x62\x69\x6e\x64\x69" \
"\x6e\x67\x73\x74\x01\x0a\x62\x61\x73\x69\x63\x2e\x6e\x61\x63\x6b" \
"\x74\x01\x16\x63\x6f\x6e\x73\x75\x6d\x65\x72\x5f\x63\x61\x6e\x63" \
"\x65\x6c\x5f\x6e\x6f\x74\x69\x66\x79\x74\x01\x12\x63\x6f\x6e\x6e" \
"\x65\x63\x74\x69\x6f\x6e\x2e\x62\x6c\x6f\x63\x6b\x65\x64\x74\x01" \
"\x13\x63\x6f\x6e\x73\x75\x6d\x65\x72\x5f\x70\x72\x69\x6f\x72\x69" \
"\x74\x69\x65\x73\x74\x01\x1c\x61\x75\x74\x68\x65\x6e\x74\x69\x63" \
"\x61\x74\x69\x6f\x6e\x5f\x66\x61\x69\x6c\x75\x72\x65\x5f\x63\x6c" \
"\x6f\x73\x65\x74\x01\x10\x70\x65\x72\x5f\x63\x6f\x6e\x73\x75\x6d" \
"\x65\x72\x5f\x71\x6f\x73\x74\x01\x0f\x64\x69\x72\x65\x63\x74\x5f" \
"\x72\x65\x70\x6c\x79\x5f\x74\x6f\x74\x01\x0c\x63\x6c\x75\x73\x74" \
"\x65\x72\x5f\x6e\x61\x6d\x65\x53\x00\x00\x00\x13\x72\x61\x62\x62" \
"\x69\x74\x40\x73\x61\x62\x72\x69\x6e\x61\x2d\x64\x65\x6c\x6c\x09" \
"\x63\x6f\x70\x79\x72\x69\x67\x68\x74\x53\x00\x00\x00\x37\x43\x6f" \
"\x70\x79\x72\x69\x67\x68\x74\x20\x28\x63\x29\x20\x32\x30\x30\x37" \
"\x2d\x32\x30\x32\x32\x20\x56\x4d\x77\x61\x72\x65\x2c\x20\x49\x6e" \
"\x63\x2e\x20\x6f\x72\x20\x69\x74\x73\x20\x61\x66\x66\x69\x6c\x69" \
"\x61\x74\x65\x73\x2e\x0b\x69\x6e\x66\x6f\x72\x6d\x61\x74\x69\x6f" \
"\x6e\x53\x00\x00\x00\x39\x4c\x69\x63\x65\x6e\x73\x65\x64\x20\x75" \
"\x6e\x64\x65\x72\x20\x74\x68\x65\x20\x4d\x50\x4c\x20\x32\x2e\x30" \
"\x2e\x20\x57\x65\x62\x73\x69\x74\x65\x3a\x20\x68\x74\x74\x70\x73" \
"\x3a\x2f\x2f\x72\x61\x62\x62\x69\x74\x6d\x71\x2e\x63\x6f\x6d\x08" \
"\x70\x6c\x61\x74\x66\x6f\x72\x6d\x53\x00\x00\x00\x11\x45\x72\x6c" \
"\x61\x6e\x67\x2f\x4f\x54\x50\x20\x32\x34\x2e\x32\x2e\x31\x07\x70" \
"\x72\x6f\x64\x75\x63\x74\x53\x00\x00\x00\x08\x52\x61\x62\x62\x69" \
"\x74\x4d\x51\x07\x76\x65\x72\x73\x69\x6f\x6e\x53\x00\x00\x00\x06" \
"\x33\x2e\x39\x2e\x31\x33\x00\x00\x00\x0e\x50\x4c\x41\x49\x4e\x20" \
"\x41\x4d\x51\x50\x4c\x41\x49\x4e\x00\x00\x00\x05\x65\x6e\x5f\x55" \
"\x53\xce";
const size_t PACKET_CONNECTION_START_SIZE = 515;

const char PACKET_CONNECTION_TUNE[] = "\x01\x00\x00\x00\x00\x00\x0c\x00\x0a\x00\x1e\x07\xff\x00\x02\x00" \
"\x00\x00\x3c\xce";
const size_t PACKET_CONNECTION_TUNE_SIZE = 21;

const char PACKET_CONNECTION_OPEN_OK[] = "\x01\x00\x00\x00\x00\x00\x05\x00\x0a\x00\x29\x00\xce";
const size_t PACKET_CONNECTION_OPEN_OK_SIZE = 14;

const char PACKET_CONNECTION_CLOSE_OK[] = "\x01\x00\x00\x00\x00\x00\x04\x00\x0a\x00\x33\xce";
const size_t PACKET_CONNECTION_CLOSE_OK_SIZE = 13;

const char PACKET_CHANNEL_OPEN_OK[] = "\x01\x00\x01\x00\x00\x00\x08\x00\x14\x00\x0b\x00\x00\x00\x00\xce";
const size_t PACKET_CHANNEL_OPEN_OK_SIZE = 17;

const char PACKET_CHANNEL_CLOSE_OK[] = "\x01\x00\x01\x00\x00\x00\x04\x00\x14\x00\x29\xce";
const size_t PACKET_CHANNEL_CLOSE_OK_SIZE = 13;

const char PACKET_BASIC_CONSUME_OK[] = "\x01\x00\x01\x00\x00\x00\x24\x00\x3c\x00\x15\x1f\x61\x6d\x71\x2e" \
"\x63\x74\x61\x67\x2d\x43\x4b\x75\x77\x30\x6b\x73\x41\x45\x52\x52" \
"\x4f\x71\x50\x49\x35\x78\x38\x48\x52\x39\x77\xce";
const size_t PACKET_BASIC_CONSUME_OK_SIZE = 45;

const char PACKET_BASIC_DELIVER[] = "\x01\x00\x01\x00\x00\x00\x33\x00\x3c\x00\x3c\x1f\x61\x6d\x71\x2e" \
"\x63\x74\x61\x67\x2d\x43\x4b\x75\x77\x30\x6b\x73\x41\x45\x52\x52" \
"\x4f\x71\x50\x49\x35\x78\x38\x48\x52\x39\x77\x00\x00\x00\x00\x00" \
"\x00\x00\x01\x00\x00\x04\x66\x69\x6c\x61\xce";
const size_t PACKET_BASIC_DELIVER_SIZE = 60;

const char PACKET_BASIC_QOS_OK[] = "\x01\x00\x01\x00\x00\x00\x04\x00\x3c\x00\x0b\xce";
const size_t PACKET_BASIC_QOS_OK_SIZE = 13;

void queuePacket(char *queueName, char *packet, int *packetSize, u_int32_t size){
    // create a packet for the packet
    struct AMQPFrame frame;
    frame.type = 1;
    frame.channel = htons(1);
    frame.size = htonl(size + 1);
    frame.class_id = htons(50);
    frame.method_id = htons(11);

    // copy frame data to the packet
    memcpy(packet + (*packetSize), (char *)&frame.type, sizeof(frame.type));
    (*packetSize) += sizeof(frame.type);
    memcpy(packet + (*packetSize), (char *)&frame.channel, sizeof(frame.channel));
    (*packetSize) += sizeof(frame.channel);
    memcpy(packet + (*packetSize), (char *)&frame.size, sizeof(frame.size));
    (*packetSize) += sizeof(frame.size);
    memcpy(packet + (*packetSize), (char *)&frame.class_id, sizeof(frame.class_id));
    (*packetSize) += sizeof(frame.class_id);
    memcpy(packet + (*packetSize), (char *)&frame.method_id, sizeof(frame.method_id));
    (*packetSize) += sizeof(frame.method_id);

    u_int8_t len = strlen(queueName);
    u_int32_t v3 = htonl(0);

    // Copy queueName length and data to the packet
    memcpy(packet + (*packetSize), (char *)&(len), sizeof(len));
    (*packetSize) += sizeof(len);
    memcpy(packet + (*packetSize), queueName, len);
    (*packetSize) += len;

    // copy v3 and the delimiter to the packet
    memcpy(packet + (*packetSize), (char *)&(v3), sizeof(v3));
    (*packetSize) += sizeof(v3);
    memcpy(packet + (*packetSize), (char *)&(v3), sizeof(v3));
    (*packetSize) += sizeof(v3);
    memcpy(packet + (*packetSize), "\xce", 1);
    (*packetSize) += 1;
}

void consumePacket(char *queueName, char *packet, int *packetSize, char *message){
    // create a packet for the packet
    struct AMQPFrame frame;
    frame.type = 1;
    frame.channel = htons(0x1);
    frame.size = htonl(47 + strlen(queueName));
    frame.class_id = htons(60);
    frame.method_id = htons(60);

    // copy frame data to the packet
    memcpy(packet + *packetSize, (char *)&frame.type, sizeof(frame.type));
    *packetSize += sizeof(frame.type);
    memcpy(packet + *packetSize, (char *)&frame.channel, sizeof(frame.channel));
    *packetSize += sizeof(frame.channel);
    memcpy(packet + *packetSize, (char *)&frame.size, sizeof(frame.size));
    *packetSize += sizeof(frame.size);
    memcpy(packet + *packetSize, (char *)&frame.class_id, sizeof(frame.class_id));
    *packetSize += sizeof(frame.class_id);
    memcpy(packet + *packetSize, (char *)&frame.method_id, sizeof(frame.method_id));
    *packetSize += sizeof(frame.method_id);

    char data[] = "\x1f\x61\x6d\x71\x2e\x63\x74\x61\x67\x2d\x55\x6e\x73\x75\x6f\x31\x58\x6c\x68\x46\x58\x41\x6e\x45\x68\x6f\x58\x76\x58\x68\x59\x41\x00\x00\x00\x00\x00\x00\x00\x01\x00";
    u_int8_t queueNameSize = strlen(queueName);

    // copy data to the packet
    memcpy(packet + *packetSize, data, 42); 
    *packetSize += 42;
    memcpy(packet + *packetSize, (char*)&(queueNameSize), sizeof(queueNameSize));
    *packetSize += sizeof(queueNameSize);
    memcpy(packet + *packetSize, queueName, queueNameSize);
    *packetSize += queueNameSize;
    memcpy(packet + *packetSize, "\xce", 1);
    *packetSize += 1;

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

    // copy additional data to the packet
    memcpy(packet + *packetSize, (char*)&type, sizeof(type)); 
    *packetSize += sizeof(type);
    memcpy(packet + *packetSize, (char*)&channel, sizeof(channel)); 
    *packetSize += sizeof(channel);
    memcpy(packet + *packetSize, (char*)&length, sizeof(length)); 
    *packetSize += sizeof(length);
    memcpy(packet + *packetSize, (char*)&class_id, sizeof(class_id)); 
    *packetSize += sizeof(class_id);
    memcpy(packet + *packetSize, (char*)&wt, sizeof(wt)); 
    *packetSize += sizeof(wt);
    memcpy(packet + *packetSize, (char*)&bl, sizeof(bl)); 
    *packetSize += sizeof(bl);
    memcpy(packet + *packetSize, (char*)&pf, sizeof(pf)); 
    *packetSize += sizeof(pf);
    memcpy(packet + *packetSize, (char*)&dl, sizeof(dl)); 
    *packetSize += sizeof(dl);
    memcpy(packet + *packetSize, "\xce", 1); 
    *packetSize += 1;

    type = 3;
    length = htonl((u_int32_t)strlen(message));

    // copy message-specific data to the packet
    memcpy(packet + *packetSize, (char*)&type, sizeof(type)); 
    *packetSize += sizeof(type);
    memcpy(packet + *packetSize, (char*)&channel, sizeof(channel)); 
    *packetSize += sizeof(channel);
    memcpy(packet + *packetSize, (char*)&length, sizeof(length)); 
    *packetSize += sizeof(length);
    memcpy(packet + *packetSize, message, strlen(message)); 
    *packetSize += strlen(message);
    memcpy(packet + *packetSize, "\xce", 1); 
    *packetSize += 1;
}
