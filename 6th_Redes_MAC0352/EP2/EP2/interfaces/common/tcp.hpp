using namespace std;
#ifndef TCP_HPP
#define TCP_HPP
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <abstract.hpp>
#include <packet.hpp>
#include <util.hpp>
#include <logger.hpp>
#include <payloadHandler.hpp>

#define MAXLINE 4096
#define LISTENQ 1
#define EXIT_TCP 10

/* handleHeartbeatTcp
Dummy function to run TCP heartbeat in a thread
*/
void *handleHeartbeatTcp(void *args);

class TCPServer {
    private:
        int serverPort;
        int listenfd, connfd;
        sockaddr_in servaddr;
        sockaddr_in connectionInfo;
        int connectionInfoLength;
        pthread_t heartbeatThread;
        bool multiProcess;

        void handleConnection(MessageProcessor *serverProcessor, Logger *logger);
        void logMessage(Logger *logger, string title, string message);
        void setTimeoutTime();
    public:
        TCPServer(char *port, bool mp = true);
        void listenToMessages(MessageProcessor *serverProcessor, Logger *logger);
        void heartbeat();
        void sendMessage(string message);
};

class TCPClient : public NetworkClient {
    public:
        TCPClient(string ip, char *port);
        void listenToMessages(MessageProcessor *clientProcessor);
        void sendMessage(string message);
};

#endif