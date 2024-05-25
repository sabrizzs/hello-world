#include <iostream>
#include <cstdlib>
#include <time.h>

int main(){
    clock_t tStart = clock();
    int N = 10000000;
    int acertos = 0;

    srand (time(NULL));

    for(int i=0; i<N; i++){
        float x = (rand() % 101);
        float y = (rand() % 101);
        x = x/100;
        y = y/100;
     
        if(x * x + y * y <= 1){
            acertos = acertos + 1;
        }
    }
    
    std::cout << 4 * acertos/N << std::endl;

    printf("%.2f seconds\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
