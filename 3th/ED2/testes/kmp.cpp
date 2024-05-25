#include <iostream>
using namespace std;


int kmp(string txt, string pat) {
    int R = 6;
    int j, M = pat.length();
    int i, N = txt.length();
    int dfa[R][M];

    dfa[pat[0]][0] = 1;
    for (int j = 1, X = 0; j < M; j++) {
        for (int c = 0; c < R; c++)
            /* copie casos de conflito */
            dfa[c][j] = dfa[c][X];
        /* defina casos de casamento */
        dfa[pat[j]][j] = j+1;
        /* atualize estado de reinício */
        X = dfa[pat[j]][X];
    } 

   for (i = 0, j = 0; i < N && j < M; i++)
      j = dfa[txt[i]][j];

   if (j == M) return i - M;
   else return N;
}

int main(){
    string texto = "sabrina";
    string pat = "bri";
    cout<< kmp(texto, pat);
}