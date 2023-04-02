## EP1 - MAC0422 - Sistemas Operacionais
### Sabrina Araujo da Silva - n°USP 12566182
### Samantha - n°USP 
---------------

#### Criando uma Shell, usando chamadas de sistema

A shell simplificada foi desenvolvida na linguagem C e implementa um programa que recebe comandos e caminhos de arquivo para realizar suas operações. O programa possui quatro funções: *nem_eu_nem_de_ninguem*, *soh_eumesmo*, *rodaeolhe* e *sohroda*.

O programa tem como base um loop infinito que lê comandos e argumentos, compara os comandos com as funções citadas anteriormente e executa a função correspondente. Se o comando digitado pelo usuário não for reconhecido, o programa exibirá uma mensagem informando que o comando é desconhecido e o loop será encerrado.

#### nem_eu_nem_de_ninguem e soh_eumesmo

As funções ```nem_eu_nem_de_ninguem``` e ```soh_eumesmo``` utilizam a chamada de sistema chmod para alterar as permissões dos arquivos especificados. A função nem_eu_nem_de_ninguem altera suas permissões para 000, ou seja, nenhum usuário terá permissão de leitura, gravação ou execução. A função soh_eumesmo altera suas permissões para 0700, ou seja, apenas o usuário atual terá permissão de leitura, gravação e execução.

#### rodaeolhe

A função cria um novo processo usando a função ```fork()```. Se ocorrer um erro na criação do processo filho (pid <0), a função ```perror()``` é chamada para imprimir uma mensagem de erro. Se o processo em execução é o processo filho (pid == 0), o programa passado como parâmetro é executado usando a função ```execve()```. Se o processo em execução for o processo pai (pid > 0), o código aguarda que o processo filho seja encerrado usando a função ```wait()``` e, em seguida, exibe uma mensagem informando o código de saída do programa.

#### sohroda

A função cria um novo processo usando a função ```fork()```. Se ocorrer um erro na criação do processo filho (pid <0), a função ```perror()``` é chamada para imprimir uma mensagem de erro. Se o processo em execução é o processo filho (pid == 0), antes da execução do programa, a função ```close(STDIN_FILENO)``` fecha o descritor de arquivo de entrada padrão (stdin) do processo filho e, em seguida,  o programa passado como parâmetro é executado usando a função ```execve()```.
