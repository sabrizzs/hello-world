using namespace std;
#ifndef UDP_HPP
#define UDP_HPP
#include <iostream>
#include <string.h>
#include <type_traits>
#include <set>

#include <abstract.hpp>
#include <packet.hpp>
#include <config.hpp>
#include <logger.hpp>
#include <user.hpp>

#define MAXLINE 4096
#define EXIT_UDP 11

/* handleHeartbeatUdp
Dummy function to run UDP heartbeat in a thread
*/
void *handleHeartbeatUdp(void *args);

using Cmp = std::integral_constant<decltype(&Address::compare), &Address::compare>;
class UDPServer {
    private:
        int serverPort;
        int sockfd;
        sockaddr_in servaddr;
        sockaddr_in connectionInfo;
        int connectionInfoLength;
        pthread_t heartbeatThread;
        set<Address, Cmp>clientsList;

        void logMessage(Logger *logger, string title, string message);
        void answerConnection(MessageProcessor *serverProcessor, Logger *logger, string message);
        void setTimeoutTime();
    public:
        UDPServer(char *port);
        void listenToMessages(MessageProcessor * serverProcessor, Logger *logger);
        void heartbeat(sockaddr_in connection, int connectionInfoLength);
};

class UDPHeartbeatThreadArgs {
    public:
        UDPServer *server;
        sockaddr_in connectionInfo;
        int connectionInfoLength;

        UDPHeartbeatThreadArgs(UDPServer *server, sockaddr_in connection, int connectionInfoLength);
};

class UDPClient : public NetworkClient {
    private:
        int serverInfoLength;
    public:
        UDPClient(string ip, char *port);
        void listenToMessages(MessageProcessor *clientProcessor);
        void sendMessage(string message);
};

#endif