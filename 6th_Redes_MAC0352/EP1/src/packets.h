#ifndef PACKETS_H
#define PACKETS_H

#include <sys/types.h>

extern const char CONNECTION_START_PACKET[];
extern const size_t CONNECTION_START_PACKET_SIZE;

extern const char CONNECTION_TUNE_PACKET[];
extern const size_t CONNECTION_TUNE_PACKET_SIZE;

extern const char CONNECTION_OPEN_PACKET_OK[];
extern const size_t CONNECTION_OPEN_PACKET_OK_SIZE;

extern const char CONNECTION_CLOSE_PACKET_OK[];
extern const size_t CONNECTION_CLOSE_PACKET_OK_SIZE;

extern const char CHANNEL_OPEN_PACKET_OK[];
extern const size_t CHANNEL_OPEN_PACKET_OK_SIZE;

extern const char CHANNEL_CLOSE_PACKET_OK[];
extern const size_t CHANNEL_CLOSE_PACKET_OK_SIZE;

extern const char QUEUE_DECLARE_PACKET_OK[];
extern const size_t QUEUE_DECLARE_PACKET_OK_SIZE;

/*extern const char BASIC_CONSUME_PACKET_OK[];
extern const size_t BASIC_CONSUME_PACKET_OK_SIZE;

extern const char BASIC_DELIVER_PACKET[];
extern const size_t BASIC_DELIVER_PACKET_SIZE;

extern const char BASIC_QOS_PACKET_OK[];
extern const size_t BASIC_QOS_PACKET_OK_SIZE;*/

#endif
