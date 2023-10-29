using namespace std;
#ifndef GAME_PROCESSOR_HPP
#define GAME_PROCESSOR_HPP
#include <abstract.hpp>
#include <packet.hpp>
#include <payloadHandler.hpp>
#include <clientHandler.hpp>
#include <tcp.hpp>
#include <user.hpp>

class GameProcessor : public MessageProcessor {
    public:      
        Client *client;

        GameProcessor(Client *client);
        Packet * endConnection();
        string processMessage(sockaddr_in connectionInfo, string message, Logger *logger);
        Packet * processPacket(Packet packet);
        void endProcessor();
};

#endif