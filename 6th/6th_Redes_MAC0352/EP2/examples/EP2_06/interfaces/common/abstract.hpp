using namespace std;
#ifndef ABSTRACT_HPP
#define ABSTRACT_HPP
#include <iostream>
#include <netdb.h>

#include <logger.hpp>

/* 
* Abstract class for socket-based
* message processing classes
*/
class MessageProcessor {
    public:
        virtual string processMessage(sockaddr_in connectionInfo, string message, Logger *logger = NULL);
        virtual void endProcessor();
};

class NetworkClient {
    public:
        int sockfd;
        struct sockaddr_in servaddr;
        virtual void listenToMessages(MessageProcessor *clientProcessor);
        virtual void sendMessage(string message);
};
#endif