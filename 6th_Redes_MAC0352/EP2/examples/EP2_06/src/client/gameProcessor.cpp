#include <gameProcessor.hpp>

GameProcessor::GameProcessor(Client *client) {
    this->client = client;
}

void GameProcessor::endProcessor() {
    return;
}

string GameProcessor::processMessage(sockaddr_in connectionInfo, string message,  Logger *logger) {
    Packet packet(message, connectionInfo);
    Packet * output = this->processPacket(packet);
    if (output == NULL)
        return "";
    if (output->packetType == DISCONNECT)
        return "exit";
    return output->packetToBytes();
}

time_t getCurrentTime() {
    struct timeval time_now;
    gettimeofday(&time_now, nullptr);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    return msecs_time;
}

void measureDelayAndSave(Client * client, long currentTime, long packetTime) {
    if (client->match == NULL)  
        return;

    time_t dif = currentTime - packetTime;
    client->match->delays.push_back((long) dif);
}

Packet * GameProcessor::endConnection() {
    if (client->clientConnection != NULL) {
        client->clientConnection->sendMessage(Packet(DISCONNECT, 0, "").packetToBytes());
        client->clientConnection = NULL;
    } else {
        client->p2pConnection->sendMessage(Packet(DISCONNECT, 0, "").packetToBytes());
    }
    client->hasClientConnected = 0;
    return new Packet(DISCONNECT, 0, "");
}

Packet * GameProcessor::processPacket(Packet packet) {
    Packet * output = NULL;
    string payload = processPayload(packet.packetPayload);
    switch (packet.packetType) {
    case CALL:
        client->hasClientConnected = 1;
        cout << "\nVocê foi convidado por " << payload << " para uma partida. Digite accept e: 1 para aceitar e ser o 'X', 2 para ser o 'O' ou 0 para recusar" << endl;
        break;
    case CALL_RESP: {
        if (stoi(payload) == 0) {
            cout << "Partida recusada!" << endl;
            output = endConnection();
            pthread_mutex_unlock(&inputBlock);
        }
        else {
            cout << "Partida aceita!" << endl;
            client->match = stoi(payload) == 1 ? new Match(2) : new Match(1);
            Packet serverPacket = Packet(START, client->user->session, textPayload(to_string(packet.userSession)) + textPayload(to_string(client->user->session)));
            client->serverConnection->sendMessage(serverPacket.packetToBytes());
        }
    } break;
    case PLAY: {
        client->match->play(payload, client->match->opositeType());
        cout << "Jogada do adversário: \n";
        client->match->printBoard();
        if (client->match->checkWin() >= 1) {
            cout << "Partida finalizada, você perdeu!" << endl;
            Packet serverPacket = Packet(END, client->user->session, integerPayload(3) + textPayload(to_string(client->user->session)) + textPayload(to_string(packet.userSession)));
            client->serverConnection->sendMessage(serverPacket.packetToBytes());
            output = endConnection();
        } 
        else if (client->match->checkWin() == -1) {
            cout << "Partida finalizada, empate!" << endl;
            Packet serverPacket = Packet(END, client->user->session, integerPayload(1) + textPayload(to_string(client->user->session)) + textPayload(to_string(packet.userSession)));
            client->serverConnection->sendMessage(serverPacket.packetToBytes());
            output = endConnection();
        }
        else 
            cout << "Digite play linha e coluna" << endl;
        pthread_mutex_unlock(&inputBlock);
    } break;
    case OVER: {
        cout <<  "O adversário finalizou a partida :(" << endl;
        client->match = NULL;
        Packet serverPacket = Packet(END, client->user->session, integerPayload(0) + textPayload(to_string(client->user->session)) + textPayload(to_string(packet.userSession)));
        client->serverConnection->sendMessage(serverPacket.packetToBytes());
        output = endConnection();
        pthread_mutex_unlock(&inputBlock);
    } break;
    case PING: {
        time_t currentTime = getCurrentTime();
        measureDelayAndSave(client, currentTime, stol(payload));
        Packet pingResp = Packet(PING_RESP, 0, textPayload(to_string(currentTime)));
        client->clientConnection->sendMessage(pingResp.packetToBytes());
    } break;
    case PING_RESP: {
        time_t currentTime = getCurrentTime();
        measureDelayAndSave(client, currentTime, stol(payload));
    } break;
    case DISCONNECT: {
        output = endConnection();
    } break;
    default:
        break;
    }
    return output;
}
