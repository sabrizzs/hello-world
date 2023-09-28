#ifndef PACKETS_H
#define PACKETS_H

#include <sys/types.h>

extern const char PACKET_CONNECTION_START[];
extern const size_t PACKET_CONNECTION_START_SIZE;

extern const char PACKET_CONNECTION_TUNE[];
extern const size_t PACKET_CONNECTION_TUNE_SIZE;

extern const char PACKET_CONNECTION_OPEN_OK[];
extern const size_t PACKET_CONNECTION_OPEN_OK_SIZE;

extern const char PACKET_CONNECTION_CLOSE_OK[];
extern const size_t PACKET_CONNECTION_CLOSE_OK_SIZE;

extern const char PACKET_CHANNEL_OPEN_OK[];
extern const size_t PACKET_CHANNEL_OPEN_OK_SIZE;

extern const char PACKET_CHANNEL_CLOSE_OK[];
extern const size_t PACKET_CHANNEL_CLOSE_OK_SIZE;

extern const char PACKET_QUEUE_DECLARE_OK[];
extern const size_t PACKET_QUEUE_DECLARE_OK_SIZE;

/*extern const char PACKET_BASIC_CONSUME_OK[];
extern const size_t PACKET_BASIC_CONSUME_OK_SIZE;

extern const char PACKET_BASIC_DELIVER[];
extern const size_t PACKET_BASIC_DELIVER_SIZE;

extern const char PACKET_BASIC_QOS_OK[];
extern const size_t PACKET_BASIC_QOS_OK_SIZE;*/

#endif
