## C++

        #include <iostream>
        
        using namespace std;
        
        int main(){
            cout<<"Hello World";
        
            return 0;
        }

### História da Amazon

- Criador: Jeff Bezos
- Líder mundial no e-commerce e em computação em nuvem
- Também possui serviçoes de assinatura
- Concorrentes:
    -  e-commerce: Walmart, eBay
    -  Serviços de nuvem: Google Cloud, Microsoft Azure
    -  streaming: Netflix, Spotify

### 16 LeaderShip

- Dive Deep (Mergulhar fundo)
    - Todos são líderes
    - Situações que não sabemos o contexto: mergulhamos de cabeça para entender o contexto, mesmo que seja difícil e consuma tempo, é preciso entender bem para chegar na melhor solução possível.
    - Exemplo: fila: se perguntar o porque foi escolhido, saber o que é, entender a decisão, entender profundamente.

- Bias for action (Ter iniciativa)
    - Riscos calculados
    - Tomar decisões e saber se são reversíveis ou não
    - Caso não for reversível é preciso pensar muito bem e conhecer todos os impactos da decisão. Exemplo: linguagem de programação que irá usar, arquitetura, etc.
    - Se for reversível facilmente, não é necessário saber sobre os mínimos detalhes, pois há muito custo de tempo, as vezes é melhor tomar a decisão e observar os resultados. Exemplo: usar um for ou um while.

- Learn and be Curious
    - Curiosidade de entender a situação e buscar alternativas para resolver o problema.
    - Exemplo: sistema falha: curiosidade de saber o que aconteceu e como evitar.
 
- Deliver Results (Entregar resultados)
    - Não se acomodar com problemas, e entender por que aconteceram
    - Exemplo: criação de ferramenta de automação: fazer estudo da tarefa ambígua, saber os passos de entrega do plano.



### Perguntas 

- Exemplos de como reagiu no passado para cada um dos leaderships.
- Método STAR.
    - Situação: contexto
    - Tarefa: qual tarefa e quais expectativas sobre
    - Ação: o que foi feito, foi necessário aprender algo?
    - Resultado: benefícios que a açõu trouxe, tempo gasto na tarefa, eficiência, processamento.

- Você pode compartilhar uma situação em que você demonstrou obsessão pelo cliente?
    - Teve uma época em que eu estava vendendo desenhos online, e tive uma compradora do Canadá que queria um desenho do marido dela e pediu para que eu entregasse antes do aniversário dele, e eu estava de férias viajando com a minha família e eu não podia fazer nas férias pois não tinha material.

### Conceitos

- Sistemas distribuídos
    - Pertencem a classe de computação paralela
    - São compostos por diversos componentes computacionais
        - Nós, que seriam as máquinas físicas ou virtuais em uma rede
        - Processos
        - Comunicação por meio de mensagens
    - Escabilidade, disponibilidade se um computador falhar, consistência
    - Um exemplo é a AWS (Amazon Web Services)
        - que provê serviços de computação em nuvem
        - como infraestrutura de tecnologias, ou banco de dados
        - exemplo de serviço: data lake: armazena dados em qualquer escala e facilita análises de dados.
    - Sistema distribuído de armazenamento, índice e consulta: dados acessados e consultados de maneira eficiente
    - Sistema distribuído multicamadas: divisão do sistema em várias camadas que representam a sua função
        - Exemplo: aplicativo web: interface, lógica de negócios, acesso de dados.
     
- Sistema embarcado
    - Conjunto de software e hardware desenvolvido para uma única função para um sistema maior
    - Possuem um conjunto limitado de componentes.
    - Exemplo: máquinas industriais, hospitalares.
    - Sem certeza: mas dispositivos da Amazon como kindle.
 
- Internet das Coisas
    - Objetos físicos do mundo real estão conectados à internet e podem coletar, trocar e transmitir dados.
    - Os dispositivos possuem sensores, processadores e tecnologias de comunicação.
    - Atuam em automação e monitoramento.
    - Exemplo: Alexa em casas automatizadas.
 
- Mineração de Dados
    - descoberta de padrões a partir de conjuntos de dados
 
- Inteligência artificial
    - Capacitar computadores a realizar tarefas como raciocínio e tomada de decisão, processamento de linguagem natural, visão computacional.

- Machine Learning (aprendizado de máquina)
    - Subárea da IA
    - Algoritmos que permitem que os computadores aprendam a partir de dados
    - O objetivo é encontrar uma função que recebe um dado, ajusta os parâmetros e tem uma saída prevista.
    - Exemplo: estimar limite de cartão de acordo com os dados de um cliente.



### Estruturas

- Arrays
    - int rush[] = { 21, 12 };
    - int num[1000] = {}; todos com valor NULL
    - sizeof(myNumbers) / sizeof(int); ou sizeof(myNumbers) / sizeof(myNumbers[0]);

- Lista ligada
    - inserir e remover é simples e evita deslocamento para direita e esquerda como em arrays
    - implementação de pilhas e filas
    - não é possível ir diretamente a um nó
    - nó para a cabeça e cada nó tem um apontador para o próximo nó

 exemplo estrutura:
 
        struct No {
            int valor;
            No *seguinte;
            No *cabeca = NULL;
            No *no = NULL;
        };
  
        ListNode *result = new ListNode();
        
- Hash maps
    - semelhante em python
    - não é util quando ordem importa ou quando a eficiência de memória importa
    - #include <unordered_map>
    - std::unordered_map<std::string, int> age;
    - age.insert({"Chris", 30});
    - age["Michael"] = 18;
    - if (age.find(query) == age.end())
    - age.erase("Michael");
    - para não usar os valores das keys usamos unordered_set
    - std::unordered_set<std::string> people;

- Stack
    - LIFO (last in first out)
    - #include <stack>
    - stack<char> st
    - st.pop(): remove elemento
    - st.top(): mostra o top da stack
    - st.push(): insere elemento
    - st.empty()

- Queues
    - FIFO (first in first out)
    - #include <queue>
    - queue<char> q
    - q.pop()
    - q.push()
    - q.size()
    - q.front()
    - q.back()

- Tree
    - tree == NULL
    - tree->val()
    - tree->right(): pode ser nullptr
    - tree->left()
    - arvores binarias, arvores rubro negras

- String
    - string.size()
    - string.substr(size_tpos, size_tlen)
    - #include string
    - string.erase(i, 1): exclui elemento i

- Vector
    - vector<int> v
    - v.push_back(x)
    - v.pop_back()
    - v.size()
    - v.erase(i)
    - sort(v.begin(), v.end())
        - #include <algorithm>

- Operações
    - expoente: pow(x,z): x^z
    - min: min(x, y)
    - max: max(x,y)

### Notação Big O e ordenação

- Big O
    - do pior para o melhor
    - O(n!) > O(2^n) > O(n^2) > O(nlogn) > O(n) > O(logn) > O(1)
    - n! = fatorial

- merge sort O(nlogn)
    - space O(n)
    - divisão e conquista, quebrar o problema em problemas menores
    - divide até chegar no caso base que são dois itens e ordena
    - recursivo
 
- insertion sort O(n^2)
    - space O(1)
    - para cada elemento do array encaixa o item comparando itens de 2 em 2
    - pior caso: o array está em ordem decrescente
    - iterativo
 
- selection sort O(n^2)
    - seleciona o mínimo do array e aloca para o começo
    - iterativo
 
- quick sort O(nlogn)
    - pior caso O(n^2), quando um pivot ruim é escolhido
    - space O(logn)
    - escolhe um pivot
    - elementos são ordenados de acordo com o pivot
    - #include <stdlib.h>
    - qsort(array, tamanho do array, sizeof(int), compare);
    - recursivo

- binary search O(logn)
    - space O(1)
    - divide o array e compara o meio com o item que quer achar
    - #include <stdlib.h>
    - bsearch(key, array, tam do array, sizeof(int), compareints);
    - recursivo

### Programação dinâmica
 
- recursão com auxílio de uma tabela
- recorrência
- divisão do problema em problemas menores
- evita recalcular os mesmos subproblemas
- tabela de memoização

        função knapsack(capacidade, pesos, valores, n):
            crie uma matriz dp com dimensões (n + 1) x (capacidade + 1)
        
            para i de 0 até n:
                para w de 0 até capacidade:
                    se i = 0 ou w = 0:
                        dp[i][w] = 0
                    senão se pesos[i - 1] <= w:
                        dp[i][w] = max(valores[i - 1] + dp[i - 1][w - pesos[i - 1]], dp[i - 1][w])
                    senão:
                        dp[i][w] = dp[i - 1][w]
        
            retorne dp[n][capacidade]

### Backtrack

- Explora todas as possibilidades em busca de uma solução

        procedure backtrack(estado_atual):
            se o estado_atual é uma solução:
                adiciona o estado_atual à lista de soluções
                retorne
            senão:
                para cada opção disponível a partir do estado_atual:
                    adicione a opção ao estado_atual
                    chame backtrack com o novo estado_atual
                    remova a última opção do estado_atual

### Classe e Struct

- Classe tem maior controle de privado e público
- Struct é tudo público

        // Usando class
        class MyClass {
        private:
            int privateMember;
        
        public:
            int publicMember;
            void myMethod();
        };
        
        // Usando struct
        struct MyStruct {
            int publicMember;
            void myMethod();
        };

### DFS E BFS

- DFS (busca em profundidade)
    - recursão ou stack
    - explora todos os nós de um ramo antes de voltar para visitar outros

- BFS (busca em largura)
    - queue
    - explora todos os nós de um nível antes de explorar outro nível
    - caminho mais curto

### Códigos do leetcode

https://leetcode.com/list/954v5ops/

feitos: 12/45

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

### Permutations (#46) (MEDIUM) TENTEI

### Merge Intervals (#56) (MEDIUM) TENTEI

Rotate List (#61) (MEDIUM)

Minimum Path Sum (#64) (MEDIUM)

Sort Colors (MEDIUM)

Word Search (#79) (MEDIUM)

Restore IP Addresses (MEDIUM)

### Validate Binary Search Tree(#98) (MEDIUM) OK MAS RESTA ALGUNS CASOS

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

### Diameter of Binary Tree (#543) (EASY) NAO CONSEGUI

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
