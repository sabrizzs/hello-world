#include <abstract.hpp>

string MessageProcessor::processMessage(sockaddr_in connectionInfo, string message, Logger *logger) {
    cerr << "[ERROR] abstract method called! Closing connection." << endl;
    exit(EXIT_FAILURE);
}

void MessageProcessor::endProcessor() {
    cerr << "[ERROR] abstract method called! Closing connection." << endl;
    exit(EXIT_FAILURE);
}

void NetworkClient::listenToMessages(MessageProcessor *clientProcessor) {
    cerr << "[ERROR] abstract method called! Closing connection." << endl;
    exit(EXIT_FAILURE);
}

void NetworkClient::sendMessage(string message) {
    cerr << "[ERROR] abstract method called! Closing connection." << endl;
    exit(EXIT_FAILURE);
}
