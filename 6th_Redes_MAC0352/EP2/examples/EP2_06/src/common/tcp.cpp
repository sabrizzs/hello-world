#include <tcp.hpp>

void *handleHeartbeatTcp(void *args) {
    TCPServer *instance = (TCPServer *)args;
    instance->heartbeat();
    pthread_exit(NULL);
}

void TCPServer::logMessage(Logger *logger, string title, string message) {
    if(logger != NULL)
        logger->write(title, message);
}

TCPServer::TCPServer(char *port, bool mp) {
    connectionInfoLength = sizeof(connectionInfo);
    bzero(&connectionInfo, connectionInfoLength);
    serverPort = atoi(port);
    multiProcess = mp;

    /* 
    * Criação de um socket IPv4 (AF_INET) TCP (SOCK_STREAM)
    * que será usado sobre a Internet (0)
    */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket :(\n");
        exit(EXIT_TCP);
    }

    /*
    * Configuração para aceitar qualquer conexão (INADDR_ANY)
    */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(serverPort);
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind :(\n");
        exit(EXIT_TCP);
    }

    if (listen(listenfd, LISTENQ) == -1) {
        perror("listen :(\n");
        exit(EXIT_TCP);
    }
}

void TCPServer::listenToMessages(MessageProcessor *processor, Logger *logger) {
    pid_t childpid;

    logMessage(logger, "listenToMessages", "Servidor no ar. Aguardando conexões na porta " + to_string(serverPort));
    while(true) {
        if ((connfd = accept(listenfd, (sockaddr *)&connectionInfo, (socklen_t *)&(connectionInfoLength))) == -1 ) {
            perror("accept :(\n");
            exit(EXIT_TCP);
        }

        if(multiProcess) {
            if ((childpid = fork()) == 0) {
                /**** PROCESSO FILHO ****/
                if (pthread_create(&heartbeatThread, NULL, handleHeartbeatTcp, this) != 0) {
                    perror("pthread :(\n");
                    exit(EXIT_TCP);
                }
                close(listenfd);
                handleConnection(processor, logger);
                exit(EXIT_SUCCESS);
            }
            else
                /**** PROCESSO PAI ****/
                close(connfd);
        }
        else {
            if (pthread_create(&heartbeatThread, NULL, handleHeartbeatTcp, this) != 0) {
                perror("pthread :(\n");
                exit(EXIT_TCP);
            }

            handleConnection(processor, logger);
            pthread_cancel(heartbeatThread);          
            close(connfd);
        }
    }
}

void TCPServer::handleConnection(MessageProcessor *processor, Logger *logger) {
    char clientInput[MAXLINE + 1];
    string input;
    ssize_t n;

    logMessage(logger, "handleConnection", "Conexão com " + printNetworkData(connectionInfo) + " aberta!");
    /* Já que está no processo filho, não precisa mais do socket
    * listenfd. Só o processo pai precisa deste socket. */
    while ((n=read(connfd, clientInput, MAXLINE)) > 0) {
        input = string(clientInput, n);
        string output = processor->processMessage(connectionInfo, input, logger);
        if(output == "exit")
            break;
        if (output == "")
            continue;
        
        sendMessage(output);
    }

    if (n < 0) {
        if(errno == EAGAIN) {
            string log = "Conexão com " + printNetworkData(connectionInfo) + " foi encerrada inesperadamente!";
            logMessage(logger, "handleConnection", log);
        }
        else {
            cerr << "[ERROR] Read error :(" << errno << endl;
            exit(EXIT_TCP);
        }
    }

    processor->endProcessor();
    logMessage(logger, "handleConnection", "Conexão com " + printNetworkData(connectionInfo) + " encerrada!");
}

void TCPServer::sendMessage(string message) {
    if(write(connfd, message.c_str(), message.length()) == -1) {
        perror("[ERROR] Error writing data to client. Closing connection.\n");
        exit(EXIT_TCP);
    }
}

void TCPServer::setTimeoutTime() {
    struct timeval tv;
    tv.tv_sec = TIMEOUT_IN_SECONDS;
    tv.tv_usec = 0;
    setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
}

void TCPServer::heartbeat() {
    while(true) {
        sleep(HEARTBEAT_FREQUENCY_IN_SECONDS);
        struct timeval time_now;
        gettimeofday(&time_now, nullptr);
        time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
        string pingPacket = Packet(PING, 0, textPayload(to_string(msecs_time))).packetToBytes();
        sendMessage(pingPacket);
    }
}

TCPClient::TCPClient(string ip, char *port) {
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error :( \n");
        exit(EXIT_TCP);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(stoi(port));

    if (inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr) <= 0) {
        cerr << "inet_pton error for " << ip << " :(\n";
        exit(EXIT_TCP);
   }
   
   if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
       perror("connect error :(\n");
       exit(EXIT_TCP);
   }
}

void TCPClient::listenToMessages(MessageProcessor *processor) {
    char recvline[MAXLINE + 1];
    string input;
    ssize_t n;

    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        input = string(recvline, n);
        string output = processor->processMessage(sockaddr_in(), input, NULL);
        if (output == "exit") {
            break;
        }
    }

    close(sockfd);
    if (n < 0) {
        cerr << "[ERROR] Read error :(" << endl;
        exit(EXIT_TCP);
    }
}

void TCPClient::sendMessage(string message) {
    if(write(sockfd, message.c_str(), message.size()) == -1) {
        perror("[ERROR] Error writing data to server. Closing connection.\n");
        exit(EXIT_TCP);
    }
}

