using namespace std;
#ifndef BACKEND_HPP
#define BACKEND_HPP
#include <packet.hpp>
#include <user.hpp>
#include <util.hpp>
#include <logger.hpp>
#include <abstract.hpp>
#include <fileHandler.hpp>
#include <payloadHandler.hpp>

/*
Not part of the protocol, used
only for server control actions.
*/
#define NO_RESP 99
#define EXIT 100

#define MAX_USERS 256

class Backend : public MessageProcessor {
    private:
        FileHandler db;
        int loggedUserSession;

        string getUsernameBySession(int session);
        string getAllActiveUsers();
        string getAllUserScores();
    public:
        Backend();
        string processMessage(sockaddr_in connectionInfo, string message, Logger *logger);
        Packet processPacket(Packet packet, Logger *logger);

        /* hasActiveUsers
        Returns true if there is any
        active user in the database.
        */
        bool hasActiveUsers();
        /* endProcessor
        Clean up backend before shutdown.
        */
        void endProcessor();
        /* Backend Usecases
        For all functions, returns the fail type on failure, 0 otherwise.
        */
        int createUser(User user);
        /* Backend Usecases
        For all functions, returns the fail type on failure, 0 otherwise.
        */
        int connectUser(User user, int &session);
        /* Backend Usecases
        For all functions, returns the fail type on failure, 0 otherwise.
        */
        int disconnectUser(int session);
        /* Backend Usecases
        For all functions, returns the fail type on failure, 0 otherwise.
        */
        int authenticateUser(User user);
        /* Backend Usecases
        For all functions, returns the fail type on failure, 0 otherwise.
        */
        int changePassword(string username, string passwords);
        /* Backend Usecases
        For all functions, returns the fail type on failure, 0 otherwise.
        */
        int expireSession(int session);
        /* Backend Usecases
        For all functions, returns the fail type on failure, 0 otherwise.
        */
        int changeUserStatus(string session, int status);
        /* Backend Usecases
        For all functions, returns the fail type on failure, 0 otherwise.
        */
        int UpdateUserScore(string username, int value);

};
#endif