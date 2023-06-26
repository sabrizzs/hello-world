## Processes and Threads
- Multithreading (diferente de multiprogramação)
	- Cada processo tem uma linha de execução

## Threads
- Ponteiro de pilha e ponteiro de instrução
- Cada thread está ligada a um processo só
- Um processo pode ter várias threads
- Área de memória comum para cooperar entre threads
	- Em geral acaba usando memória compartilhada

## One or more threads in a Process
- Cada thread tem sua pilha de execução
- Área por thread para guardar váriaveis locais

## Benefits using threads
- Muito mais rápido que criar um processo
- Menos recurso liberado quando ela morre
- Mudar entre threads tem menor tempo que muudar entre processos

- Se um processo é suspenso, todas as threads dos processos também são suspensas
	- O processo inteiro é suspenso para "suspender uma thread"
- Thread não tem fork, tem spawn, "uma brota da outra"

## TYpes of threads
- Nível de usuário (ULTs): simulação de uma thread
	- Não tem multiprocessamento, só há quando o kernel sabe sobre o multiprocessamento
- Kernel: entrada nova na tabela de processos
	- Kernel gerencia o escalonamento de cada thread
