using namespace std;
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <payloadHandler.hpp>
#include <user.hpp>
#include <match.hpp>
#include <packet.hpp>
#include <util.hpp>
#include <abstract.hpp>
#include <tcp.hpp>

#include <vector>
#include <pthread.h>

extern pthread_t listenerID;
extern pthread_mutex_t inputBlock;

class Client : public MessageProcessor {
    public:
        string input;
        User * user;
        Match * match;
        vector<User *> playerList;
        int p2pPort;
        NetworkClient *serverConnection;
        NetworkClient *clientConnection;
        TCPServer *p2pConnection;
        int hasClientConnected;

        Client(int p2pPort);
        string processMessage(sockaddr_in connectionInfo, string message, Logger *logger);
        Packet *processInput();
        string userPayload();
        string userPayloadWithP2pPort();
        string passwordPayload();
        void processServerOuput(Packet packet);
        void savePlayersList(vector<string> payload);
        void printPlayersList();
        User *getUserByName(string username);
        void initMatch(int type);
};

#endif