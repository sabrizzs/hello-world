using namespace std;
#include <backend.hpp>

Backend::Backend() {
    srand(time(NULL));
    db = FileHandler();
    loggedUserSession = 0;
}

string Backend::processMessage(sockaddr_in connectionInfo, string message, Logger *logger) {
    Packet packet(message, connectionInfo);
    Packet output = processPacket(packet, logger);

    switch (output.packetType) {
    case NO_RESP:
        return "";
    case EXIT:
        return "exit";
    default:
        return output.packetToBytes();
    }
}

Packet Backend::processPacket(Packet packet, Logger *logger) {
    Packet response = Packet(FAIL, 0, integerPayload(MALFORMED_PACKET));
    string packetType = "[Unkown]";
    string commonLogMessage = "Cliente " + printNetworkData(packet.connectionInfo) + " ";
    string logMessage = "enviou um pacote inválido!";
    bool needsLogging = true;

    switch (packet.packetType) {
    case NEW: {
        packetType = "[NEW]";
        if(packet.malformed(4))
            break;

        string input = processPayload(packet.packetPayload);
        User user = User(input, packet.connectionInfo);

        int status = createUser(user);
        if(status == 0) {
            logMessage = "criou o usuário \'" + user.username + "\' com sucesso!";
            string payload = textPayload("Usuário cadastrado com sucesso!");
            response = Packet(NEW_RESP, 0, payload);
        }
        else {
            logMessage = "enviou um pacote que falhou com status " + to_string(status);
            response = Packet(FAIL, 0, integerPayload(status));
        }
    } break;
    case IN: {
        packetType = "[IN]";
        if(packet.malformed(4))
            break;

        if(packet.userSession != 0) {
            logMessage = "já possui uma sessão de usuário ativa!";
            response = Packet(FAIL, 0, integerPayload(ALREADY_LOGGED_IN));
            break;
        }

        string input = processPayload(packet.packetPayload);
        string p2pPort = input.substr(0, input.find(" "));
        string userInput = input.substr(input.find(" ") + 1, input.length());
        User user = User(userInput, packet.connectionInfo, stoi(p2pPort));

        int status = authenticateUser(user);
        if(status == 0) {
            int userSession = MAX_USERS;
            status = connectUser(user, userSession);
            if(status == 0) {
                logMessage = "logou no usuário \'" + user.username + "\' com a sessão " + to_string(userSession) + "!"; 
                loggedUserSession = userSession;
                string payload = textPayload("Usuário logado com sucesso!");
                response = Packet(IN_RESP, userSession, payload);
            }
            else {
                logMessage = "enviou um pacote que falhou com status " + to_string(status);
                response = Packet(FAIL, 0, integerPayload(status));
            }
        }
        else {
            logMessage = "enviou um pacote que falhou com status " + to_string(status);
            response = Packet(FAIL, 0, integerPayload(status));
        }
    } break;
    case PASS: {
        packetType = "[PASS]";
        if(packet.malformed(4))
            break;
    
        if(packet.userSession == 0) {
            logMessage = "não possui uma sessão de usuário ativa!";
            response = Packet(FAIL, 0, integerPayload(NOT_LOGGED_IN));
            break;
        }

        string passwords = processPayload(packet.packetPayload);
        string username = getUsernameBySession(packet.userSession);

        if(username == "") {
            logMessage = "possui sessão de usuário inválida!";
            response = Packet(FAIL, 0, integerPayload(NOT_LOGGED_IN));
            break;
        }

        int status = changePassword(username, passwords);
        if(status == 0) {
            logMessage = "mudou a senha do usuário \'" + username + "\' com sucesso!";
            string payload = textPayload("Senha atualizada com sucesso!");
            response = Packet(PASS_RESP, packet.userSession, payload);
        }
        else {
            logMessage = "enviou um pacote que falhou com status " + to_string(status);
            response = Packet(FAIL, 0, integerPayload(status));
        }
    } break;
    case OUT: {
        packetType = "[OUT]";
        if(packet.userSession == 0) {
            logMessage = "não está logado!";
            response = Packet(FAIL, 0, integerPayload(NOT_LOGGED_IN));
            break;
        }

        string username = getUsernameBySession(packet.userSession);
        int status = expireSession(packet.userSession);
        if(status == 0) {
            logMessage = "deslogou do usuário \'" + username + "\' com sucesso!"; 
            string payload = textPayload("Usuário deslogado com sucesso!");
            loggedUserSession = 0;
            response = Packet(OUT_RESP, packet.userSession, payload);
        }
        else {
            logMessage = "enviou um pacote que falhou com status " + to_string(status);
            response = Packet(FAIL, 0, integerPayload(status));
        }
    } break;
    case START: {
        packetType = "[START]";
        if(packet.malformed(4))
            break;

        if(packet.userSession == 0) {
            logMessage = "não está logado!";
            response = Packet(FAIL, 0, integerPayload(NOT_LOGGED_IN));
            break;
        }

        string sessions = processPayload(packet.packetPayload);
        string firstSession = sessions.substr(0, sessions.find(" "));
        string secondSession = sessions.substr(sessions.find(" ") + 1, sessions.length());
        string username = getUsernameBySession(stoi(firstSession));
        string opponentName = getUsernameBySession(stoi(secondSession));

        int status = changeUserStatus(firstSession, OCUPADO) || changeUserStatus(secondSession, OCUPADO);
        if(status == 0) {
            logMessage = "logado no usuário \'" + username + "\' começou uma partida contra o usuário \'" + opponentName + "\'!";
            response = Packet(START_RESP, packet.userSession, "");
        }
        else {
            logMessage = "enviou um pacote que falhou com status " + to_string(status);
            response = Packet(FAIL, packet.userSession, integerPayload(status));
        }
    } break;
    case END: {
        packetType = "[END]";
        if(packet.malformed(2))
            break;
        
        string input = processPayload(packet.packetPayload);
        int gameStatus = stoi(input.substr(0, input.find(" ")));
        string sessions = input.substr(input.find(" ") + 1, input.length());

        string firstSession = sessions.substr(0, sessions.find(" "));
        string secondSession = sessions.substr(sessions.find(" ") + 1, sessions.length());

        string firstUsername = getUsernameBySession(stoi(firstSession));
        string secondUsername = getUsernameBySession(stoi(secondSession));

        int status;
        switch (gameStatus) {
        case 1:
            status = (UpdateUserScore(firstUsername, 1) || UpdateUserScore(secondUsername, 1));
            logMessage = "informou que o usuário \'" + firstUsername + "\' empatou com o usuário \'" + secondUsername + "\'!";
            break;
        case 2:
            status = UpdateUserScore(firstUsername, 3);
            logMessage = "informou que o usuário \'" + firstUsername + "\' ganhou do usuário \'" + secondUsername + "\'!";
            break;
        case 3:
            status = UpdateUserScore(secondUsername, 3);
            logMessage = "informou que o usuário \'" + secondUsername + "\' ganhou do usuário \'" + firstUsername + "\'!";
            break;
        case 0:
            status = 0;
            logMessage = "informou que a partida entre os usuários \'"\
            + secondUsername + "\' e \'" + firstUsername + "\' foi encerrada antes da hora!";
            break;
        default:
            status = MALFORMED_PACKET;
            break;
        }
        changeUserStatus(firstSession, LIVRE);
        changeUserStatus(secondSession, LIVRE);
        if(status == 0) {
            string successPayload = textPayload("Jogo encerrado com sucesso!");
            response = Packet(END_RESP, packet.userSession, successPayload);
        }
        else {
            logMessage = "enviou um pacote que falhou com status " + to_string(status);
            response = Packet(FAIL, packet.userSession, integerPayload(status));
        }
    } break;
    case LIST:
        needsLogging = false;
        response = Packet(LIST_RESP, packet.userSession, getAllActiveUsers());
        break;
    case HALL_OF_FAME:
        needsLogging = false;
        response = Packet(HALL_OF_FAME_RESP, packet.userSession, getAllUserScores());
        break;
    case PING_RESP:
        needsLogging = false;
        response = Packet(NO_RESP, 0, "");
        break;
    case DISCONNECT:
        packetType = "[DISCONNECT]";
        logMessage = "disconectou!";
        if(packet.userSession != 0) {
            disconnectUser(packet.userSession);
        }
        response = Packet(EXIT, 0, "");
        break;
    }

    if(needsLogging)
        logger->write("processPacket", packetType + " " + commonLogMessage + logMessage);
    return response;
}

bool Backend::hasActiveUsers() {
    return db.getFilenamesInDirectory(ACTIVE_USERS_FOLDER).size() != 0;
}

void Backend::endProcessor() {
    if(loggedUserSession != 0) {
        disconnectUser(loggedUserSession);
    }
}

int Backend::createUser(User user) {
    vector<string> payload;

    payload.push_back(textPayload(user.password));
    payload.push_back(integerPayload(user.score));

    if(db.createNewUser(user, payload) == -1)
        return USER_EXISTS;
    return 0;
}

int Backend::connectUser(User user, int &session) {
    vector<string>connectedUsers = db.getFilenamesInDirectory(ACTIVE_USERS_FOLDER);

    if(connectedUsers.size() >= MAX_USERS)
        return SERVER_FULL;

    int newSession = (rand()%MAX_USERS) + 1;
    string filePath = ACTIVE_USERS_FOLDER + string("/") + to_string(newSession);
    while(fileExists(filePath)) {
        newSession = (rand()%MAX_USERS) + 1;
        filePath = ACTIVE_USERS_FOLDER + string("/") + to_string(newSession);
    }

    session = newSession;
    user.session = session;

    vector<string> payload;
    payload.push_back(integerPayload(user.status));
    payload.push_back(textPayload(user.username));
    payload.push_back(networkPayload(user.address));
    payload.push_back(integerPayload(user.p2pPort));

    db.connectNewUser(user, payload);

    return 0;
}

int Backend::disconnectUser(int session) {
    string filePath = ACTIVE_USERS_FOLDER + string("/") + to_string(session);
    if(session == 0 || !fileExists(filePath))
        return NOT_LOGGED_IN;
    
    removeFile(filePath);
    return 0;
}

int Backend::authenticateUser(User user) {
    string userPath = TMP_FOLDER + string("/") + user.username;
    if(!fileExists(userPath))
        return USER_NOT_EXISTS;
    
    vector<string>userContent = db.getFileContent(userPath);
    if(user.password != processPayload(userContent[0]))
        return INVALID_PASSWORD;

    return 0;
}

int Backend::changePassword(string username, string passwords) {
    string currentPassword = passwords.substr(0, passwords.find(" "));
    string newPassword = passwords.substr(passwords.find(" ") + 1, passwords.size());
    string filename = TMP_FOLDER + string("/") + username;

    if(!fileExists(filename))
        return USER_NOT_EXISTS;

    vector<string> data = db.getFileContent(filename);

    if(processPayload(data[0]) != currentPassword)
        return INVALID_PASSWORD;

    data[0] = textPayload(newPassword);
    db.writeFile(filename, data);
    return 0;
}

int Backend::expireSession(int session) {
    string filePath = ACTIVE_USERS_FOLDER + string("/") + to_string(session);
    if(!fileExists(filePath))
        return NOT_LOGGED_IN;

    removeFile(filePath);
    return 0;
}

int Backend::changeUserStatus(string session, int status) {
    string filePath = ACTIVE_USERS_FOLDER + string("/") + session;

    if(!fileExists(filePath))
        return NOT_LOGGED_IN;
    
    vector<string> fileContent = db.getFileContent(filePath);

    fileContent[0] = integerPayload(status);

    db.writeFile(filePath, fileContent);
    return 0;
}

int Backend::UpdateUserScore(string username, int value) {
    string filePath = TMP_FOLDER + string("/") + username;

    if(!fileExists(filePath))
        return USER_NOT_EXISTS;
    
    vector<string> fileContent = db.getFileContent(filePath);

    int currentScore = stoi(processPayload(fileContent[1]));
    fileContent[1] = integerPayload(currentScore + value);

    db.writeFile(filePath, fileContent);
    return 0;
}

string Backend::getUsernameBySession(int session) {
    string filePath = ACTIVE_USERS_FOLDER + string("/") + to_string(session);

    if(!fileExists(filePath)) {
        return "";
    }

    vector<string> fileContent = db.getFileContent(filePath);
    string username = processPayload(fileContent[1]);
    return username;
}

string Backend::getAllActiveUsers() {
    vector<string> filenames = db.getFilenamesInDirectory(ACTIVE_USERS_FOLDER);
    vector<string> payloads;

    for(size_t i = 0; i < filenames.size(); i++) {
        string filepath = ACTIVE_USERS_FOLDER + string("/") + filenames[i];
        vector<string> filePayloads = db.getFileContent(filepath);

        string userAddress = processPayload(filePayloads[2]);
        string p2pPort = processPayload(filePayloads[3]);
        filePayloads.pop_back();

        sockaddr_in p2pAddress;
        p2pAddress.sin_addr.s_addr = stoi(userAddress.substr(0, userAddress.find(" ")));
        p2pAddress.sin_port = stoi(p2pPort);
    
        filePayloads[2] = networkPayload(Address(p2pAddress));
        payloads.push_back(aggregatePayloads(filePayloads));
    }

    return aggregatePayloads(payloads);
}

string Backend::getAllUserScores() {
    vector<string> filenames = db.getFilenamesInDirectory(TMP_FOLDER);
    vector<string> payloads;

    for(size_t i = 0; i < filenames.size(); i++) {
        string filePath = TMP_FOLDER + string("/") + filenames[i];
        if(isDirectory(filePath))
            continue;

        vector<string> filePayloads = db.getFileContent(filePath);
        filePayloads[0] = textPayload(filenames[i]);
        payloads.push_back(aggregatePayloads(filePayloads));
    }

    return aggregatePayloads(payloads);
}