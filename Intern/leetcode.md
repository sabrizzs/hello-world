## C++

        #include <iostream>
        
        using namespace std;
        
        int main(){
            cout<<"Hello World";
        
            return 0;
        }

- string
    - string.size()
    - string.substr(size_tpos, size_tlen)

- stack
    - stack<char> st
    - st.pop(): remove elemento
    - st.top(): mostra o top da stack
    - st.push(): insere elemento
    - st.empty()

- vector
    - vector<int> v
    - v.push_back(x)
    - v.size()
    - sort(v.begin(), v.end())
        - #include <algorithm>

- operações
    - expoente: pow(x,z): x^z
    - min: min(x, y)
    - max: max(x,y)

- tree
    - tree == NULL
    - tree->val()
    - tree->right(): pode ser nullptr
    - tree->left()
 
- classe

        class Solution {
        public:
            ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
            }
        };

- lista ligada

         ListNode *result = new ListNode();

- Big O
    - do pior para o melhor
    - O(n!) > O(2^n) > O(n^2) > O(nlogn) > O(n) > O(logn) > O(1)
    - n! = fatorial

- merge sort O(nlogn)
    - space O(n)
    - divisão e conquista
    - divide até chegar no caso base que são dois itens e ordena
 
- insertion sort O(n^2)
    - space O(1)
    - para cada elemento do array encaixa o item comparando itens de 2 em 2
 
- quick sort O(nlogn)
    - pior caso O(n^2)
    - space O(logn)
    - escolhe um pivot
    - elementos são ordenados de acordo com o pivot
    - #include <stdlib.h>
    - qsort(array, tamanho do array, sizeof(int), compare);

- binary search O(logn)
    - space O(1)
    - divide o array e compara o meio com o item que quer achar
    - #include <stdlib.h>
    - bsearch(key, array, tam do array, sizeof(int), compareints);
 
- programação dinâmica
    - recursão com auxílio de uma tabela
    - recorrência

https://leetcode.com/list/954v5ops/

feitos: 8/45

### Two Sum (#1) (EASY) OK 

### Add Two Numbers (MEDIUM) OK REVISAR

Percorrer a lista até o final mas para cada número seguinte multiplicar por 10 (decimal). //mudei a lógica pois essa não funciona para números muito grandes.

Median of Two Sorted Arrays * & (#4) (HARD)

### Longest Palindromic Substring (#5) (MEDIUM) QUASE

String to Integer (atoi) (#8) (MEDIUM)

Integer to Roman (#12) (MEDIUM) 

### Roman to Integer (#13) (EASY) OK

### Valid Parentheses (#20) (EASY) OK

Merge K Sorted Lists (#23) (HARD)

Valid Sudoku (#36) (MEDIUM)

Combination Sum (#39) (MEDIUM) 

Permutations (#46) (MEDIUM)

Merge Intervals (#56) (MEDIUM)

Rotate List (#61) (MEDIUM)

Minimum Path Sum (#64) (MEDIUM)

Sort Colors (MEDIUM)

Word Search (#79) (MEDIUM)

Restore IP Addresses (MEDIUM)

Validate Binary Search Tree(#98) (MEDIUM)

### Same Tree ~ (#100) (EASY) OK

### Symmetric Tree ~ (#101) (EASY) OK

Binary Tree Level Order Traversal & (#102) (MEDIUM)

Convert Sorted List to Binary Search Tree (#109) (MEDIUM)

Path Sum II (MEDIUM)

Populating Next Right Pointers in Each Node (#116) (MEDIUM)

### Best Time to Buy and Sell Stock (#121) (EASY) OK BUT TLE

        class Solution {
        public:
            int maxProfit(vector<int>& prices) {
                int max = 0;
                int profit = 0;
                for(int i=0; i<prices.size()-1; i++){
                    for(int j=i+1; j<prices.size(); j++){
                        profit = prices[j]-prices[i];
                        if(profit>max) max = profit;
                    }
                }
                return max;
            }
        };

Word Ladder II (#126) (HARD)

Word Ladder (#127) (HARD)

Candy (HARD)

LRU Cache (#146) (MEDIUM)

Min Stack (#155) (MEDIUM)

Number of Islands & (#200) (MEDIUM)

Course Schedule & (#207) (MEDIUM)

Course Schedule II & (#210) (MEDIUM)

Add and Search Word - Data structure design (#211) (MEDIUM)

Word Search II (#212) (HARD)

Sliding Window Maximum (HARD)

Integer to English Words (#273) (HARD)

Game of Life & (#289) (MEDIUM)

Find Median from Data Stream (#295) (HARD)

Longest Increasing Subsequence (#300) (MEDIUM)

Design Tic-Tac-Toe (#348)

Pacific Atlantic Water Flow (#417) (MEDIUM)

Minesweeper (#529) (MEDIUM)

Diameter of Binary Tree (#543) (EASY) NAO CONSEGUI

Reorganize String & (#767) (MEDIUM)

*not required to solve
~solve both iteratively and recursively
&asked

https://leetcode.com/discuss/interview-question/488887/amazon-final-interview-questions-sde1

//Implemente um método que remova elementos duplicados de um array

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> removeDuplicates(vector<int> v){
    if(v.size() == 0) return v;
    if(v.size() == 1) return v;
    
    vector<int> aux;
    
    sort(v.begin(), v.end());
    
    int last = v[0];
    for(int i=1; i<v.size(); i++){
        if(v[i] != last) aux.push_back(v[i]);
        last = v[i];
    }
    return aux;
}


int main(){
    int array[] = {2, 4, 5, 4, 1, 3};
    vector<int> array_aux;
    
    for(int i:array){
        array_aux.push_back(i);
    }
    
    array_aux = removeDuplicates(array_aux);
    
    for(int i=0; i<array_aux.size(); i++){
        cout<<array_aux[i]<<endl;
    }

    return 0;
}

https://leetcode.com/list/954v5ops/

https://leetcode.com/discuss/interview-question/1590162/Amazon-Final-Interview-Questions-or-All-Combined-2021-or-SDE-and-New-Grad
