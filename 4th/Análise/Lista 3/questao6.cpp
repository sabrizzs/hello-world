#include <iostream>
#include <vector> 
#include <cmath>
using namespace std;

//questao 6
void troca(){
    int n = 8;
    //vector<string> v = {"B","B","B","A","A","A"};
    vector<string> v = {"B","B","B","A","B","A","B","A"};
    string *aux = new string[n];

    int i = 0;
    int f = n-1;

    for(int j = 0; j<n; j++){
        if(v[j] == "A"){
            aux[i] = "A";
            i = i + 1;
        } else {
            aux[f] = "B";
            f = f - 1;
        }
    }

    for(int j = 0; j<n; j++){
        cout << aux[j];
    }
}

void trocaa(){
    int n = 8;
    //vector<string> v = {"B","B","B","A","B","A","B","A"};
    //vector<string> v = {"B","B","B","B","B","B","B","A"};
    //vector<string> v = {"A","A","A","A","A","A","A","A"};
    //vector<string> v = {"B","B","B","B","B","B","B","B"};
    //vector<string> v = {"A","B","A","B","A","B","A","A"};
    vector<string> v = {"A","B","B","B","B","B","B","B"};

    int j = n-1;
    int count = 0;

    for(int i = 0; i<j; i++){
        if(v[i] == "B" && v[j] == "A"){
            v[i] = "A";
            v[j] = "B";
            j = j-1;
        } else if(v[i] == "A" && v[j] == "B"){
            j = j-1;
        } else if(v[i] == "B" && v[j] == "B"){
            j = j-1;
            i = i-1;
        }
        count++;
    }

    for(int j = 0; j<n; j++){
        cout << v[j];
    }
    cout << " contador " << count;
}



int main(){
    trocaa();

    //questao 8
    cout << "a" << endl;
    cout << 6/2;
    return 0;
}