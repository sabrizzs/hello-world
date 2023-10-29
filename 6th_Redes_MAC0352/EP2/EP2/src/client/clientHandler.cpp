#include <clientHandler.hpp>

pthread_t listenerID;
pthread_mutex_t inputBlock;

Client::Client(int p2pPort) {
  user = NULL;
  match = NULL;
  hasClientConnected = 0;
  this->p2pPort = p2pPort;
}

string Client::processMessage(sockaddr_in connectionInfo, string message, Logger *logger) {
    Packet *serverOutput = new Packet(message);
    processServerOuput(*serverOutput);
    return " ";
}

string Client::userPayload() {
  int usernameSize = user->username.size();
  int passwordSize = user->password.size();

  if (usernameSize > MAX_SIZE || passwordSize > MAX_SIZE)
  {
    cerr << "[ERROR] Username or password too long! It must be at most 256 letters." << endl;
    return "";
  }

  int totalSize = 2 + usernameSize + passwordSize;
  char *output = (char *)malloc(totalSize * sizeof(char));
  sprintf(output, "%c%s%c%s", usernameSize, user->username.c_str(), passwordSize, user->password.c_str());

  return string(output, totalSize);
}

string Client::userPayloadWithP2pPort() {
  string userPayload = this->userPayload();

  int portSize = floor(log10(p2pPort)) + 1;
  string port = to_string(p2pPort);

  char * withPort = (char *) malloc((sizeof(userPayload) + portSize) * sizeof(char));
  sprintf(withPort, "%c%s%s", portSize, port.c_str(), userPayload.c_str());

  return string(withPort);
}

string Client::passwordPayload() {
  string passwords = input.substr(input.find(" ") + 1, input.size());
  string currentPassword = passwords.substr(0, passwords.find(" "));
  string newPassword = passwords.substr(passwords.find(" ") + 1, passwords.size());

  int newPasswordSize = newPassword.size();
  int passwordSize = currentPassword.size();

  if (newPasswordSize > MAX_SIZE || passwordSize > MAX_SIZE) {
    cerr << "[ERROR] Password too long! It must be at most 256 letters." << endl;
    return "";
  }

  int totalSize = 2 + newPasswordSize + passwordSize;
  char *output = (char *)malloc(totalSize * sizeof(char));

  sprintf(output, "%c%s%c%s", passwordSize, currentPassword.c_str(), newPasswordSize, newPassword.c_str());

  return string(output, totalSize);
}

Packet *Client::processInput() {
  Packet *request = NULL;
  int end = input.find(" ");
  string command = input.substr(0, end);
  string payload = input.substr(end + 1, input.length());

  if (command == "new") {
    user = new User(payload);
    request = new Packet(NEW, user->session, userPayload());
    delete user;
    user = NULL;
  }

  else if (command == "in") {
    if (user != NULL) {
      cerr << "Você já está conectado. Saia para se conectar em outra conta" << endl;
      return NULL;
    }

    user = new User(payload);
    request = new Packet(IN, user->session, userPayloadWithP2pPort());
  }

  else if (command == "pass") {
    if (user == NULL) {
      cerr << "Você precisa estar logado para trocar a senha" << endl;
      return NULL;
    }

    request = new Packet(PASS, user->session, passwordPayload());
  }

  else if (command == "out") {
    if (user == NULL)
      return NULL;

    char session = user->session;

    request = new Packet(OUT, session, "");
  }

  else if (command == "l") {
    char session = user != NULL ? user->session : 0;
    request = new Packet(LIST, session, "");
  }

  else if (command == "halloffame") {
    char session = user != NULL ? user->session : 0;
    request = new Packet(HALL_OF_FAME, session, "");
  }

  else if (command == "play") {
    match->play(payload, match->type);
    match->printBoard();
    cout << endl;
    if (match->checkWin() != 0) { 
      match->checkWin() >= 1 ? cout << "Você venceu!" << endl : cout << "Empate!" << endl;
      pthread_mutex_unlock(&inputBlock);
    }
    request = new Packet(PLAY, user->session, textPayload(payload));
  }

  else if (command == "call") {
    if (user == NULL) {
      cerr << "Você deve estar logado para chamar alguem para jogar" << endl;
      return NULL;
    }

    request = new Packet(CALL, user->session, textPayload(user->username));
  }

  else if (command == "accept") {
    request = new Packet(CALL_RESP, user->session, integerPayload(stoi(payload)));
    if (stoi(payload) >= 1)
      cout << "Partida aceita, aguarde a jogada do adversário" << endl;
    if (stoi(payload) == 1)
      match = new Match(1);
    else if (stoi(payload) == 2)
      match = new Match(2);
    else 
      pthread_mutex_unlock(&inputBlock);
  }

  else if (command == "over") {
    if (match == NULL) {
      cerr << "Você precisa estar em uma partida para usar esse comando" << endl;
      return NULL;
    }
    pthread_mutex_unlock(&inputBlock);
    request = new Packet(OVER, user->session, "");
  }

  else if (command == "bye") {
    Packet bye = Packet(DISCONNECT, user->session, "");
    serverConnection->sendMessage(bye.packetToBytes());
    exit(EXIT_SUCCESS);
  }

  else if (command == "delay") {
    cout << "Ultimas 3 latências: " << endl;
    int delaysSize = match->delays.size();
    for (int i = delaysSize - 1; i > delaysSize - 4; i--)
      cout << match->delays[i] << endl;
  }

  else {
    cerr << "Comando desconhecido!" << endl;
    return NULL;
  }

  return request;
}

void failStatusToString(int failStatus) {
  switch (failStatus) {
  case MALFORMED_PACKET:
    cerr << "Problema interno, tente novamente" << endl;
    break;
  case USER_NOT_EXISTS:
    cerr << "Usuário não existe" << endl;
    break;
  case USER_EXISTS:
    cerr << "Usuário já existente" << endl;
    break;
  case NOT_LOGGED_IN:
    cerr << "Log in necessário para realizar essa ação" << endl;
    break;
  case ALREADY_LOGGED_IN:
    cerr << "Você já está logado" << endl;
    break;
  case INVALID_PASSWORD:
    cerr << "Senha incorreta" << endl;
    break;
  case SERVER_FULL:
    cerr << "Servidor cheio :(, tente novamente mais tarde" << endl;
    break;
  default:
    cerr << "Problema não identificado, tente novamente" << endl;
    break;
  }
}

void Client::savePlayersList(vector<string> payload) {
  playerList.clear();

  //1<Status>Z<username>X<IP>Y<Port>
  for (int i = 0; i < (int) payload.size(); i += 4) {
    string username = payload[i + 1];
    if (user != NULL && user->username == username)
      continue;
    sockaddr_in clientAddress;
    bzero(&clientAddress, sizeof(clientAddress));
    bool status = stoi(payload[i]);
    clientAddress.sin_addr.s_addr = stoi(payload[i + 2]);
    clientAddress.sin_port = stoi(payload[i + 3]);
    playerList.push_back(new User(username, status, Address(clientAddress)));
  }
}

void Client::printPlayersList() {
  cout << "Lista de jogadores: " << endl;
  for (int i = 0; i < (int) playerList.size(); i++) {
    cout << playerList[i]->username << " ";
    playerList[i]->status ? cout << "OCUPADO" : cout << "DISPONÍVEL";
    cout << endl;
  }
}

void Client::processServerOuput(Packet packet) {
  string payload = processPayload(packet.packetPayload);
  vector<string> payloadVector = payloadToVector(payload);
  switch (packet.packetType) {
  case NEW_RESP:
    cout << payload << endl;
    break;
  case IN_RESP:
    cout << payload << endl;
    if (packet.userSession != 0) {
      user->session = packet.userSession;
    }
    break;
  case PASS_RESP:
    cout << payload << endl;
    break;
  case OUT_RESP:
    cout << payload << endl;
    delete user;
    user = NULL;
    break;
  case FAIL:
    failStatusToString(stoi(payload));
    if (user != NULL) {
      delete user;
      user = NULL;
    }
    break;
  case LIST_RESP:
    savePlayersList(payloadVector);
    printPlayersList();
    break;
  case HALL_OF_FAME_RESP:
    cout << "Jogador | Pontuação" << endl;
    for (int i = 0; i < (int) payloadVector.size(); i += 2) {
      cout << payloadVector[i] << " | " << payloadVector[i + 1] << endl;
    }
    break;
  case PING: {
    Packet pingResp = Packet(PING_RESP, 0, "");
    serverConnection->sendMessage(pingResp.packetToBytes());
  } break;
  case START_RESP:
    cout << "Partida vai começar!" << endl;
    match->printBoard();
    cout << "Digite play linha e coluna\n" << endl;
    break;
  case END_RESP:
    match = NULL;
    break;
  default:
    cout << "Erro inesperado, tente novamente!" << endl;
    break;
  }

  if (packet.packetType != PING)
    pthread_mutex_unlock(&inputBlock);
}

void Client::initMatch(int type) {
  match = new Match(type);
}

User *Client::getUserByName(string username) {
  if (playerList.empty()) {
    cerr << "Lista de usuários vazia, digite o comando l para saber os usuários conectados!" << endl;
    pthread_mutex_unlock(&inputBlock);
    return NULL;
  }

  for (int i = 0; i < (int) playerList.size(); i++) {
    if (playerList[i]->username == username)
      return playerList[i];
  }

  cout << "Usuário não encontrado" << endl;
  pthread_mutex_unlock(&inputBlock);
  return NULL;
}