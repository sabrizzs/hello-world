#include <sys/types.h>

const char CONNECTION_START_PKT[] = 
"\x01\x00\x00\x00\x00\x01\xf2\x00\x0a\x00\x0a\x00\x09\x00\x00\x01" 
"\xcd\x0c\x63\x61\x70\x61\x62\x69\x6c\x69\x74\x69\x65\x73\x46\x00" 
"\x00\x00\xc7\x12\x70\x75\x62\x6c\x69\x73\x68\x65\x72\x5f\x63\x6f" 
"\x6e\x66\x69\x72\x6d\x73\x74\x01\x1a\x65\x78\x63\x68\x61\x6e\x67" 
"\x65\x5f\x65\x78\x63\x68\x61\x6e\x67\x65\x5f\x62\x69\x6e\x64\x69" 
"\x6e\x67\x73\x74\x01\x0a\x62\x61\x73\x69\x63\x2e\x6e\x61\x63\x6b" 
"\x74\x01\x16\x63\x6f\x6e\x73\x75\x6d\x65\x72\x5f\x63\x61\x6e\x63" 
"\x65\x6c\x5f\x6e\x6f\x74\x69\x66\x79\x74\x01\x12\x63\x6f\x6e\x6e" 
"\x65\x63\x74\x69\x6f\x6e\x2e\x62\x6c\x6f\x63\x6b\x65\x64\x74\x01" 
"\x13\x63\x6f\x6e\x73\x75\x6d\x65\x72\x5f\x70\x72\x69\x6f\x72\x69" 
"\x74\x69\x65\x73\x74\x01\x1c\x61\x75\x74\x68\x65\x6e\x74\x69\x63" 
"\x61\x74\x69\x6f\x6e\x5f\x66\x61\x69\x6c\x75\x72\x65\x5f\x63\x6c" 
"\x6f\x73\x65\x74\x01\x10\x70\x65\x72\x5f\x63\x6f\x6e\x73\x75\x6d" 
"\x65\x72\x5f\x71\x6f\x73\x74\x01\x0f\x64\x69\x72\x65\x63\x74\x5f" 
"\x72\x65\x70\x6c\x79\x5f\x74\x6f\x74\x01\x0c\x63\x6c\x75\x73\x74" 
"\x65\x72\x5f\x6e\x61\x6d\x65\x53\x00\x00\x00\x0b\x72\x61\x62\x62" 
"\x69\x74\x40\x45\x52\x53\x4f\x09\x63\x6f\x70\x79\x72\x69\x67\x68" 
"\x74\x53\x00\x00\x00\x37\x43\x6f\x70\x79\x72\x69\x67\x68\x74\x20" 
"\x28\x63\x29\x20\x32\x30\x30\x37\x2d\x32\x30\x32\x32\x20\x56\x4d" 
"\x77\x61\x72\x65\x2c\x20\x49\x6e\x63\x2e\x20\x6f\x72\x20\x69\x74" 
"\x73\x20\x61\x66\x66\x69\x6c\x69\x61\x74\x65\x73\x2e\x0b\x69\x6e" 
"\x66\x6f\x72\x6d\x61\x74\x69\x6f\x6e\x53\x00\x00\x00\x39\x4c\x69" 
"\x63\x65\x6e\x73\x65\x64\x20\x75\x6e\x64\x65\x72\x20\x74\x68\x65" 
"\x20\x4d\x50\x4c\x20\x32\x2e\x30\x2e\x20\x57\x65\x62\x73\x69\x74" 
"\x65\x3a\x20\x68\x74\x74\x70\x73\x3a\x2f\x2f\x72\x61\x62\x62\x69" 
"\x74\x6d\x71\x2e\x63\x6f\x6d\x08\x70\x6c\x61\x74\x66\x6f\x72\x6d" 
"\x53\x00\x00\x00\x11\x45\x72\x6c\x61\x6e\x67\x2f\x4f\x54\x50\x20" 
"\x32\x34\x2e\x32\x2e\x31\x07\x70\x72\x6f\x64\x75\x63\x74\x53\x00" 
"\x00\x00\x08\x52\x61\x62\x62\x69\x74\x4d\x51\x07\x76\x65\x72\x73" 
"\x69\x6f\x6e\x53\x00\x00\x00\x06\x33\x2e\x39\x2e\x31\x33\x00\x00" 
"\x00\x0e\x50\x4c\x41\x49\x4e\x20\x41\x4d\x51\x50\x4c\x41\x49\x4e" 
"\x00\x00\x00\x05\x65\x6e\x5f\x55\x53\xce";
const size_t SZ_CONNECTION_START_PKT = 507;

const char CONNECTION_TUNE_PKT[] = 
"\x01\x00\x00\x00\x00\x00\x0c\x00\x0a\x00\x1e\x07\xff\x00\x02\x00" 
"\x00\x00\x3c\xce";
const size_t SZ_CONNECTION_TUNE_PKT = 21;

const char CONNECTION_OPEN_OK_PKT[] = "\x01\x00\x00\x00\x00\x00\x05\x00\x0a\x00\x29\x00\xce";
const size_t SZ_CONNECTION_OPEN_OK_PKT = 14;

const char CONNECTION_CLOSE_OK_PKT[] = "\x01\x00\x00\x00\x00\x00\x04\x00\x0a\x00\x33\xce";
const size_t SZ_CONNECTION_CLOSE_OK_PKT = 13;

const char CHANNEL_OPEN_OK_PKT[] = "\x01\x00\x01\x00\x00\x00\x08\x00\x14\x00\x0b\x00\x00\x00\x00\xce";
const size_t SZ_CHANNEL_OPEN_OK_PKT = 17;

const char CHANNEL_CLOSE_OK_PKT[] = "\x01\x00\x01\x00\x00\x00\x04\x00\x14\x00\x29\xce";
const size_t SZ_CHANNEL_CLOSE_OK_PKT = 13;

const char QUEUE_DECLARE_OK_PKT[] = 
"\x01\x00\x01\x00\x00\x00\x0f\x00\x32\x00\x0b\x02\x71\x31\x00\x00"
"\x00\x00\x00\x00\x00\x00\xce";
const size_t SZ_QUEUE_DECLARE_OK_PKT = 24;

const char BASIC_CONSUME_OK_PKT[] = 
"\x00\x00\x03\x04\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x08\x00" 
"\x45\x00\x00\x60\xa2\xc8\x40\x00\x40\x06\x99\xcd\x7f\x00\x00\x01" 
"\x7f\x00\x00\x01\x16\x28\x80\xcc\xa6\xbe\xfc\x89\x53\x71\x6c\xef" 
"\x80\x18\x02\x00\xfe\x54\x00\x00\x01\x01\x08\x0a\x33\x18\xf3\x80" 
"\x33\x18\xf3\x80\x01\x00\x01\x00\x00\x00\x24\x00\x3c\x00\x15\x1f" 
"\x61\x6d\x71\x2e\x63\x74\x61\x67\x2d\x43\x4f\x39\x2d\x79\x36\x34" 
"\x69\x67\x4f\x57\x5f\x77\x56\x6b\x43\x42\x44\x49\x58\x74\x67\xce";
const size_t SZ_BASIC_CONSUME_OK_PKT = 113;
//there is another type of consume pkt with way more data...

const char BASIC_DELIVER_PKT[] = 
"\x00\x00\x03\x04\x00\x06\x00\x00\x00\x00\x00\x00\x6d\x71\x08\x00" 
"\x45\x00\x00\x90\xb1\x40\x40\x00\x40\x06\x8b\x25\x7f\x00\x00\x01" 
"\x7f\x00\x00\x01\x16\x28\xa7\xa4\x81\xc4\xa9\xae\x96\xa9\xea\x0a" 
"\x80\x18\x02\x00\xfe\x84\x00\x00\x01\x01\x08\x0a\x33\x1d\x50\x6d" 
"\x33\x1c\x5d\xa7\x01\x00\x01\x00\x00\x00\x31\x00\x3c\x00\x3c\x1f" 
"\x61\x6d\x71\x2e\x63\x74\x61\x67\x2d\x77\x69\x56\x4c\x37\x63\x6b" 
"\x59\x49\x63\x33\x47\x46\x65\x69\x73\x61\x36\x52\x42\x44\x67\x00" 
"\x00\x00\x00\x00\x00\x00\x01\x00\x00\x02\x71\x31\xce\x02\x00\x01" 
"\x00\x00\x00\x0f\x00\x3c\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04" 
"\x10\x00\x01\xce\x03\x00\x01\x00\x00\x00\x04\x4d\x73\x67\x31\xce";
const size_t SZ_BASIC_DELIVER_PKT = 161;

const char BASIC_QOS_OK_PKT[] = "\x01\x00\x01\x00\x00\x00\x04\x00\x3c\x00\x0b\xce";
const size_t SZ_BASIC_QOS_OK_PKT = 13;
