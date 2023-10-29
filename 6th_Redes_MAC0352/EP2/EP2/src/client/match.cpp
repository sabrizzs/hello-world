#include <match.hpp>

Match::Match(int type) {
  moves = 0;
  currentState = 0;
  this->type = type;
}

void Match::play(string payload, int type) {
  int line = stoi(payload.substr(0, payload.find(" ")));
  int column = stoi(payload.substr(payload.find(" ") + 1, payload.find(" ") + 2));

  int newState = 0;
  if (line == 1)
    newState = currentState + type * pow(3, column - 1); 
  else if (line == 2)
    newState = currentState + type * pow(3, column + 2);
  else if (line == 3)
    newState = currentState + type * pow(3, column + 5);

  currentState = newState;
  moves++;
}

int Match::opositeType() {
  return type == 1 ? 2 : 1;
}

void Match::printBoard() {
  int i, resultToPrint;

  for (i = 0, resultToPrint = currentState, cout << endl; i < 9; i++){
    if (resultToPrint % 3 == 1)
      cout << " X  ";
    else if (resultToPrint % 3 == 2)
      cout << " O  ";
    else 
      cout << "    ";
        
    resultToPrint = resultToPrint / 3;

    if (i == 2 || i == 5)
      cout << "\n----+----+----\n";
    else if (i != 8)
      cout << "|";
  }
  cout << endl;
}

int Match::checkWin() {
  int currentStateCheck;

  for(int i = 0, currentStateCheck = currentState; i < 3; i++) {
    int firstPosition = currentStateCheck % 3;
    int secondPosition = (currentStateCheck / 3) % 3;
    int thirdPosition = (currentStateCheck / 9) % 3;

    if (firstPosition == 1 && secondPosition == 1 && thirdPosition == 1)
      return 1;

    if (firstPosition == 2 && secondPosition == 2 && thirdPosition == 2)
      return 2;

    currentStateCheck = currentStateCheck / 27;
  }

  // Na vertical
  for (int i=0, currentStateCheck = currentState; i < 3; i++) {
    int firstPosition = currentStateCheck % 3;
    int secondPosition = (currentStateCheck/27) % 3;
    int thirdPosition = (currentStateCheck/729) % 3;

    if (firstPosition == 1 && secondPosition == 1 && thirdPosition == 1)
      return 1;

    if (firstPosition == 2 && secondPosition == 2 && thirdPosition == 2)
      return 2;

    currentStateCheck = currentStateCheck / 3;
  }
  
  // Na diagonal
  currentStateCheck = currentState;
  if(currentStateCheck % 3 == 1 && (currentStateCheck / 81) % 3 == 1 && (currentStateCheck/6561) % 3 == 1)
    return 1;

  if(currentStateCheck % 3 == 2 && (currentStateCheck / 81) % 3 == 2 && (currentStateCheck/6561) % 3 == 2)
    return 2;

  if((currentStateCheck/9) % 3 == 1 && (currentStateCheck / 81) % 3 == 1 && (currentStateCheck/729) % 3 == 1)
    return 1;

  if((currentStateCheck/9) % 3 == 2 && (currentStateCheck / 81) % 3 == 2 && (currentStateCheck/729) % 3 == 2)
    return 2;

  if (moves == 9)
    return -1;

  return 0;
}