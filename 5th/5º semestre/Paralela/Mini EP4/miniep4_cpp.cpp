#include <iostream>
#include <cstdlib>
#include <time.h>

int main(){
    clock_t tStart = clock();
    const int N = 10000000;
    int acertos = 0;
    float x,y;

    srand(time(nullptr));

    for(int i=0; i<N; i++){
        x = static_cast<float>(rand()) / RAND_MAX;
        y = static_cast<float>(rand()) / RAND_MAX;

        if(x * x + y * y <= 1){
            acertos++;
        }
    }
    
    std::cout << 4 * acertos/N << '\n';

    printf("%.2f seconds\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
