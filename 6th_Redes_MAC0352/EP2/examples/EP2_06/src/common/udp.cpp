#include <udp.hpp>

void *handleHeartbeatUdp(void *args) {
    UDPHeartbeatThreadArgs *castedArgs = (UDPHeartbeatThreadArgs *)args;
    castedArgs->server->heartbeat(castedArgs->connectionInfo, castedArgs->connectionInfoLength);
    pthread_exit(NULL);
}

UDPHeartbeatThreadArgs::UDPHeartbeatThreadArgs(UDPServer *server, sockaddr_in connection, int connectionInfoLength) {
    this->connectionInfo = connection;
    this->connectionInfoLength = connectionInfoLength;
    this->server = server;
}

void UDPServer::logMessage(Logger *logger, string title, string message) {
    if(logger != NULL)
        logger->write(title, message);
}

UDPServer::UDPServer(char *port) {
    connectionInfoLength = sizeof(connectionInfo);
    bzero(&connectionInfo, connectionInfoLength);
    serverPort = atoi(port);

    /* 
    * Criação de um socket IPv4 (AF_INET) UDP (SOCK_DGRAM)
    * que será usado sobre a Internet (0)
    */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket :(\n");
        exit(EXIT_UDP);
    }

    /*
    * Configuração para aceitar qualquer conexão (INADDR_ANY)
    */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(serverPort);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind :(\n");
        exit(EXIT_UDP);
    }
}

void UDPServer::listenToMessages(MessageProcessor *processor, Logger *logger) {
    pid_t childpid;
    char clientInput[MAXLINE + 1];
    string input;
    ssize_t n;

    logMessage(logger, "listenToMessages", "Servidor no ar. Aguardando conexões na porta " + to_string(serverPort));

    while(true) {
        if((n = recvfrom(sockfd, clientInput, MAXLINE, 0,(sockaddr *)&connectionInfo, (socklen_t *)&(connectionInfoLength))) == -1) {
            if(errno == EAGAIN) {
                string log = "Conexão com " + printNetworkData(connectionInfo) + " foi encerrada inesperadamente!";
                logMessage(logger, "handleConnection", log);
                continue;
            }
            else {
                perror("recvfrom :(\n");
                exit(EXIT_UDP);
            }
        }
        input = string(clientInput, n);

        Address *connectionAddress = new Address(connectionInfo);
        if(clientsList.count(*connectionAddress) == 0) {
            clientsList.insert(*connectionAddress);
            UDPHeartbeatThreadArgs *heartbeatArgs = new UDPHeartbeatThreadArgs(this, connectionInfo, connectionInfoLength);
            if (pthread_create(&heartbeatThread, NULL, handleHeartbeatUdp, heartbeatArgs) != 0) {
                perror("pthread :(\n");
                exit(EXIT_UDP);
            }
        }

        if ((childpid = fork()) == 0) {
            /**** PROCESSO FILHO ****/
            answerConnection(processor, logger, input);
            exit(EXIT_SUCCESS);
        }
    }
}

void UDPServer::answerConnection(MessageProcessor *processor, Logger *logger, string message) {
    string output = processor->processMessage(connectionInfo, message, logger);

    if(output == "exit" || output == "")
        return;

    if(sendto(sockfd, output.c_str(), output.length(), 0,(sockaddr *)&connectionInfo, (socklen_t)connectionInfoLength) == -1) {
        perror("sendto :(\n");
        exit(EXIT_UDP);
    }
}

void UDPServer::setTimeoutTime() {
    struct timeval tv;
    tv.tv_sec = TIMEOUT_IN_SECONDS;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
}

void UDPServer::heartbeat(sockaddr_in connection, int connectionInfoLength) {
    string pingPacket = Packet(PING, 0, "").packetToBytes();

    while(true) {
        sleep(HEARTBEAT_FREQUENCY_IN_SECONDS);
        if(sendto(sockfd, pingPacket.c_str(), pingPacket.length(), 0,(sockaddr *)&connectionInfo, (socklen_t)connectionInfoLength) == -1) {
        perror("sendto :(\n");
        exit(EXIT_UDP);
        }
    }
}

UDPClient::UDPClient(string ip, char *port) {
    serverInfoLength = sizeof(servaddr);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket error :( \n");
        exit(EXIT_UDP);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(stoi(port));

    if (inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr) <= 0) {
        cerr << "inet_pton error for " << ip << " :(\n";
        exit(EXIT_UDP);
   }
}

void UDPClient::listenToMessages(MessageProcessor *processor) {
    char recvline[MAXLINE + 1];
    string input;
    ssize_t n;

    while ((n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *)&servaddr, (socklen_t *)&serverInfoLength)) > 0) {
        input = string(recvline, n);
        string output = processor->processMessage(sockaddr_in(), input, NULL);
    }

    if (n < 0) {
        cerr << "[ERROR] Read error :(" << endl;
        exit(EXIT_UDP);
    }
}

void UDPClient::sendMessage(string message) {
    if(sendto(sockfd, message.c_str(), message.length(), 0, (struct sockaddr *)&servaddr, (socklen_t)serverInfoLength) == -1) {
        perror("[ERROR] Error writing data to server. Closing connection.\n");
        exit(EXIT_UDP);
    }
}