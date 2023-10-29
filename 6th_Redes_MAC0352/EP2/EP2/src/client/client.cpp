#include <iostream>
#include <iomanip>
using namespace std;

#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <packet.hpp>
#include <util.hpp>
#include <tcp.hpp>
#include <udp.hpp>
#include <clientHandler.hpp>
#include <gameProcessor.hpp>

class ThreadArgs {
    public:
        NetworkClient *clientConnection;
        NetworkClient *serverConnection;
        TCPServer *p2pConnection;
        Client * client;

        ThreadArgs(NetworkClient *cc, NetworkClient *sc, TCPServer *p2p, Client * c) {
            clientConnection = cc;
            serverConnection = sc;
            p2pConnection = p2p;
            client = c;
        }
};

void *listenToServer(void * args);
void *listenP2P(void * args);
void *listenToClient(void * args);
TCPClient * handleClientConnect(ThreadArgs * args, string username);
bool serverMessage(int packetType);

int main(int argc, char **argv) {
   if (argc != 5) {
      fprintf(stderr,"Uso: %s <IP Servidor> <Porta Servidor> TCP|UDP <Porta P2P>\n",argv[0]);
      exit(EXIT_FAILURE);
   }

   Client *client = new Client(stoi(string(argv[4])));
   string connectionType = string(argv[3]);
   string ip = argv[1];
   if(!isNumber(ip)) {
      char str[INET_ADDRSTRLEN];
      struct hostent *hptr;
      if ((hptr = gethostbyname(ip.c_str())) == NULL) {
         perror("gethostbyname :(\n");
         exit(EXIT_FAILURE);
      }
       if ((inet_ntop(AF_INET, hptr->h_addr_list[0], str, sizeof(str))) == NULL) {
         cerr << "inet_ntop error for " << string(hptr->h_addr_list[0]) << " :(\n";
         exit(EXIT_FAILURE);
       }
       ip = string(str);
   }

   NetworkClient *serverConnection = NULL;

   if(connectionType == "TCP") {
      serverConnection = new TCPClient(ip, argv[2]);
   }
   else if (connectionType == "UDP") {
      serverConnection = new UDPClient(ip, argv[2]);
   }
   else {
      cerr << "[ERROR] invalid connection type. You must use UDP or TCP." << endl;
      exit(EXIT_FAILURE);
   }

   pthread_mutex_init(&inputBlock, NULL);
   pthread_mutex_unlock(&inputBlock);
   TCPServer *p2pServer = new TCPServer(argv[4], false);
   client->serverConnection = serverConnection;
   client->p2pConnection = p2pServer;
   
   ThreadArgs *args = new ThreadArgs(NULL, serverConnection, p2pServer, client);
   //Create Client - Server listener
   if (pthread_create(&listenerID, NULL, listenToServer, args) != 0) {
      perror("pthread :(\n");
      exit(EXIT_FAILURE);
   }

   //Create Client-Client listener
   if (pthread_create(&listenerID, NULL, listenP2P, args) != 0) {
      perror("pthread :(\n");
      exit(EXIT_FAILURE);
   }

   while (true) {
        if (!pthread_mutex_lock(&inputBlock)) {
            fflush(NULL);   
            cout << "JogoDaVelha> ";
            getline(cin, client->input);
            Packet *output = client->processInput();
            if (output == NULL) {
               pthread_mutex_unlock(&inputBlock);
               continue;
            }
            if (output->packetType == CALL && client->clientConnection == NULL) {
               string usernameToInvite = client->input.substr(client->input.find(" ") + 1, client->input.length());
               client->clientConnection = handleClientConnect(args, usernameToInvite);
            }
            string rawOutput = output->packetToBytes();
            if (serverMessage(output->packetType))
               serverConnection->sendMessage(rawOutput);
            else if (!serverMessage(output->packetType)) {
               if (client->clientConnection != NULL)
                  client->clientConnection->sendMessage(rawOutput);
               else if (client->hasClientConnected)
                  p2pServer->sendMessage(rawOutput);
            }
            else {
               pthread_mutex_unlock(&inputBlock);
            }
        }
   }

   signal(SIGCHLD, SIG_IGN);
   exit(EXIT_SUCCESS);
}

bool serverMessage(int packetType) {
   switch (packetType) {
   case CALL:
   case PLAY:
   case OVER:
   case CALL_RESP:
      return false;
   default:
      return true;
   }
}

TCPClient * handleClientConnect(ThreadArgs * args, string username) {
   User * user = args->client->getUserByName(username);
   
   if (user == NULL)
      return NULL;

   if (user->status == OCUPADO) {
      cout << "Usuário ocupado! Espere até ele ficar disponível!" << endl;
      pthread_mutex_unlock(&inputBlock);
      return NULL;
   }
   char ip[INET_ADDRSTRLEN];
   inet_ntop(AF_INET, &user->address.ip, ip, INET_ADDRSTRLEN);
   string ipString = string(ip);
   string port = to_string(user->address.port);

   TCPClient *clientConnection = new TCPClient(ipString, (char *) port.c_str());
   args->clientConnection = clientConnection;
   if (pthread_create(&listenerID, NULL, listenToClient, args) != 0) {
      perror("pthread :(\n");
      exit(EXIT_FAILURE);
   }

   return clientConnection;
}

void *listenToClient(void * args) {
   ThreadArgs *castedArgs = (ThreadArgs *)args;
   GameProcessor * processor = new GameProcessor(castedArgs->client);
   castedArgs->clientConnection->listenToMessages(processor);
   return NULL;
}

void *listenToServer(void * args) {
   ThreadArgs *castedArgs = (ThreadArgs *)args;
   castedArgs->serverConnection->listenToMessages(castedArgs->client);
   return NULL;
}

void *listenP2P(void * args) {
   ThreadArgs *castedArgs = (ThreadArgs *)args;
   GameProcessor * processor = new GameProcessor(castedArgs->client);
   castedArgs->p2pConnection->listenToMessages(processor, NULL);
   return NULL;
}