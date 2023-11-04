using namespace std;
#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <math.h>
#include <netdb.h>

// Packet types
#define PING 1
#define PING_RESP 2
#define NEW 3
#define NEW_RESP 4
#define IN 5
#define IN_RESP 6
#define PASS 7
#define PASS_RESP 8
#define OUT 9 
#define OUT_RESP 10 
#define FAIL 11
#define LIST 12
#define LIST_RESP 13
#define CALL 14
#define CALL_RESP 15
#define START 16
#define START_RESP 17
#define PLAY 18
#define END 19
#define END_RESP 20
#define OVER 21
#define HALL_OF_FAME 22
#define HALL_OF_FAME_RESP 23
#define DISCONNECT 24

// Fail status
#define MALFORMED_PACKET 1
#define USER_NOT_EXISTS 2
#define USER_EXISTS 3
#define NOT_LOGGED_IN 4
#define ALREADY_LOGGED_IN 5
#define INVALID_PASSWORD 6
#define SERVER_FULL 7

#define EXIT_PACKET 2

class Packet {
    public:
        int packetType;
        int userSession;
        string packetPayload;
        sockaddr_in connectionInfo;

        Packet(string rawData);
        Packet(string rawData, sockaddr_in networkData);
        Packet(int packetType, int userSession, string payload);
        /* packetToBytes
        Converts the packet into a raw string.
        */
        string packetToBytes();
        /* malformed
        Returns if the packet is malformed.
        */
        bool malformed(int expectedSize);
        void print();
};

#endif