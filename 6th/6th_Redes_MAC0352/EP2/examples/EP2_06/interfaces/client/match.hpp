using namespace std;
#include <math.h>
#include <iostream>
#include <vector>

class Match {
  public:
    int currentState;
    int moves;
    vector<long> delays;
    Match(int type);
    void play(string payload, int type);
    void printBoard();
    int checkWin();
    int opositeType();
    int type;
};