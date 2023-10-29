#include <payloadHandler.hpp>

string processPayload(string payload) {
    string processedString;

    for(int currentPosition = 0; currentPosition < (int)payload.length(); currentPosition++) {
        int dataLength = payload[currentPosition];
        if(currentPosition != 0)
            processedString += ' ';
        processedString += payload.substr(currentPosition + 1, dataLength);
        currentPosition += dataLength;
    }

    return processedString;
}

vector<string> payloadToVector(string payload) {
    string tmp; 
    stringstream ss(payload);
    vector<string> words;

    while(getline(ss, tmp, ' ')){
        words.push_back(tmp);
    }
    
    return words;
}

string networkPayload(Address address) {
    int ipSize = (address.ip == 0? 1 : floor(log10(address.ip)) + 1);
    int portSize = (address.port == 0? 1 : floor(log10(address.port)) + 1);

    int totalSize = 2 + ipSize + portSize;
    char *output = (char *)malloc(totalSize * sizeof(char)); 
    sprintf(output, "%c%d%c%d", ipSize, address.ip, portSize, address.port);

    string result = string(output, totalSize);
    free(output);
    return result;
}

string integerPayload(int integer) {
    int integerSize = (integer == 0? 1 : floor(log10(integer)) + 1);

    int totalSize = 1 + integerSize;
    char *output = (char *)malloc(totalSize * sizeof(char));
    sprintf(output, "%c%d", integerSize, integer);

    string result = string(output, totalSize);
    free(output);
    return result;
}

string textPayload(string text) {
    if((int)text.length() > 256) {
        cerr << "[ERROR] Text too long! Closing connection." << endl;
        exit(EXIT_PAYLOAD);
    }

    int textSize = text.length();
    int totalSize = 1 + textSize;
    char *output = (char *)malloc(totalSize*sizeof(char));
    sprintf(output, "%c%s", textSize, text.c_str());

    string result = string(output, totalSize);
    free(output);
    return result;
}

string aggregatePayloads(vector<string> payloads) {
    string aggregatedPayload; 
    for(size_t i = 0; i < payloads.size(); i++)
        aggregatedPayload+=payloads[i];
    
    return aggregatedPayload;
}