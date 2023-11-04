#include <packet.hpp>

Packet::Packet(string rawData) {
    if(rawData.length() < 2) {
        cerr << "[ERROR] Malformed packet! Closing connection." << endl;
        exit(EXIT_PACKET);
    }
    packetType = rawData[0];
    unsigned char userSession = rawData[1];
    this->userSession = userSession;

    packetPayload = rawData.length() > 2? rawData.substr(2) : "";
}

Packet::Packet(string rawData, sockaddr_in networkData) {
    if(rawData.length() < 2) {
        cerr << "[ERROR] Malformed packet! Closing connection." << endl;
        exit(EXIT_PACKET);
    }
    packetType = rawData[0];
    unsigned char userSession = rawData[1];
    this->userSession = userSession;

    packetPayload = rawData.length() > 2? rawData.substr(2) : "";

    connectionInfo = networkData;
}

Packet::Packet(int type, int session, string payload) {
    packetType = type;
    userSession = session;
    packetPayload = payload;
}

string Packet::packetToBytes() {
    if(packetType > pow(2, 8) || userSession > pow(2, 8)) {
        cerr << "[ERROR] Packet type or user session too large!" << endl;
        return "";
    }
    
    char output[2 + packetPayload.length()];
    sprintf(output, "%c%c%s", packetType, userSession, packetPayload.c_str());

    return string(output, 2 + packetPayload.length());
}

bool Packet::malformed(int expectedSize) {
    return ((int)packetPayload.length() < expectedSize);
}

void Packet::print() {
    cout << "Packet Data:" << endl;
    cout << "Type: " << packetType << endl;
    cout << "Session: " << userSession << endl;
    cout << "Payload: " << packetPayload << endl;
    cout << "#############" << endl;
}