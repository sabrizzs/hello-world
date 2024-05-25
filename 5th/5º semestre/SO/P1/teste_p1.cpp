#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Define as afirmações e se elas são verdadeiras ou falsas
    vector<string> afirmacoes = {
        "Um processo pode estar em 3 estados diferentes: rodando, bloqueado e pronto. ", // Verdadeira
        "Na multi-programacao cada programa tem o monopolio da CPU ate seu termino, mas o Sistema Operacional pode decidir a ordem do escalonamento de alto nivel do processo (decidir qual a ordem em que eles serao executados).", // Falsa
        "No Minix existem apenas 3 maneiras dos processos se comunicarem, todas sincronas: arquivos, pipes e mensagens.", // Falsa
        "Os processos em Minix sao organizados de maneira hierarquica, com o processo INIT no topo da arvore.", // Verdadeira
        "Pipes sao tratados como arquivos no MINIX.", // Verdadeira
        "Na versao que utilizamos do Minix o SO eh dividido em 4 camadas, sendo que as duas inferiores compartilham o espaco de enderecamento e nas outras os processos rodam com memorias independentes.", // Falsa
        "Em Minix, chamadas de sistemas nao sao realmente ''chamadas''. A biblioteca do sistema transforma a chamada de procedimentos no envio de mensagens sincronas. ", // Verdadeira
        "Todos os processos em Minix, inclusive os do Kernel (System Task e Clock Task) funcionam de maneira sincrona, com um loop de recebimento de mensagens.", // Verdadeira
        "O funcionamento do Minix com envio de mensagens torna o sistema menos seguro.", // Falsa
        "A unica maneira de se criar um processo em Minix eh pela chamada de sistema `fork()`.", // Verdadeira
        "As duas maneiras de se criar um processo em Minix sao a chamada de sistema `fork()` e a chamada de sistema `execve()`.", // Falsa
        "A rotina `malloc()`, deve utilizar diretamente a chamada de sistema `brk()`. Desta maneira, a rotina `free()` libera memoria apenas quando a regiao liberada esta no limite da area de dados do processo.", // Falsa
        "A chamada `open()` eh necessaria apenas para verificar as permissoes do arquivo. ", // Falsa
        "O Minix tem apenas dois tipos de arquivo: de bloco e de caractere. O primeiro oferece acesso aleatorio pela manipulacao do ponteiro de leitura. O segundo prove apenas acesso sequencial.", // Verdadeira
        "Para CRIARMOS um pipe no Minix precisamos utilizar nao somente a chamada `pipe()` mas tambem a chamada `close()`.", // Verdadeira
        "Quando queremos redirecionar entrada e saida, utilizamos a chamada `dup()`.", // Verdadeira
        "A chamada `setuid()` eh muito util para a seguranca do sistema Minix, uma vez que permite que um processo chamado por um usuário rode com privilegios de superusuario.", // Verdadeira
        "Tabelas de processo sao essenciais para o multiprocessamento. Elas guardam todas as informacoes de um processo e permitem o restauro de seu estado quando ele voltar a executar.", // Verdadeira
        "No Minix, assim como no UNIX , apenas o Kernel eh responsavel pela manutencao da tabela de processos. Chamadas ao System Task permitem que os programas obtenham os dados que precisam para tomar decisoes de escalonamento.", // Falsa
        "Interrupcoes sao comunicacoes assincronas do hardware para o Kernel do sistema. Quando ocorrem, o hardware consulta uma tabela de enderecos. Estes enderecos se referem a procedimentos do System Task. Basta entao que o processador de um goto a estes procedimentos, escritos diretamente na linguagem C.", // Falsa
        "Em muitos sistemas operacionais, processos que trabalham em conjunto compartilham alguma memoria em comum. O uso compartilhado dessa memoria cria “condicoes de corrida”, o que implica que o uso deste recurso precisa ser coordenado. As regioes do programa que acessam a memoria comum sao chamadas de ''regioes criticas''.", // Verdadeira
        "Sao 3 as condicoes para uma boa solucao para o problema da exclusao mutua: i. So um processo deve entrar na regiao critica de cada vez. ii. Nao deve ser feita nenhuma hipotese sobre a velocidade relativa dos processos. iii. Nenhum processo executando fora de sua regiao critica deve bloquear outro processo.", // Falsa
        "Existe uma equivalencia entre semaforos, monitores e mensagens. Qualquer um destes esquemas pode ser implementado usando o outro.", // Verdadeira
        "Sao 3 os niveis de escalonamento de processos: i. alto nivel onde se decide quais processos entram na disputa por recursos; ii. nivel medio, usado para balanceamento de carga; iii. baixo nivel, onde se decide quão dos processos prontos deve ter o controle da CPU.", // Verdadeira
        "Um processo em uma fila de menor prioridade sempre demorara mais para rodar que um processo numa fila de maior prioridade.", // Falsa
        "O codigo abaixo resolve o problema dos filosofos comiloes: #define N 5 Philosopher(i) { int I; think(); take_chopstick(i); take_chopstick((i+1) % N); eat(); put_chopstick(i); put_chopstick(i+1); } ", // Verdadeira
        "Em sistemas nao preemptivos, o relogio eh desligado e o processo decide quando deve ceder a CPU. Isso pode gerar o travamento do sistema.", // Verdadeira
        "No sistema de multi-level feeback queues, existem varias filas de prioridade e cada processo eh alocado a uma desde o inicio de sua execucao. Desta maneira a alocacao desta prioridade eh essencial para o bom desempenho do sistema.", // Verdadeira
        "No EP1, para que os comandos rodados com `rode()` ou `rodeveja()` recebessem argumentos, eh necessario criar um vetor de strings com os argumentos que seria passado para a chamada de sistema `execve()`.", // Falsa
        "Para implementar semaforos usando monitores, basta criar um monitor chamado “semaforo_mon”, com dois procedimentos, P() e V(). A exclusao mutua do monitor por si so ja garante o funcionamento, sem necessidade de mais codigo.", // Falsa
        "Em sistemas de memoria real nao e possivel executar um programa maior do que a memoria, dai a importancia da memoria virtual ", // Falsa
        "Em sistemas de memoria real, a estrategia de colocação ''first fit'' eh baseada no principio da localidade.", // Falsa
        "Em sistemas de memoria real as estrategias “best fit” e ''worst fit'' envolvem heuristicas que visam diminuir a fragmentacao externa.", // Verdadeira
        "Em sistemas de memoria real com particoes fixas um programa eh compilado para rodar em apenas uma particao, isso pode gerar ociosidade no sistema, mesmo com programas habilitados a rodar.", // Verdadeira
        "Em sistemas de memoria particionada, um processo sem memooria disponivel fica aguardando fora das filas de escalonamento primario (ou seja, seu estado NAO eh''pronto'').", // Verdadeira
        "No minix o grande desafio de implementacao eh impedir que muitas mensagens se acumulem e causando um overflow do buffer de mensagens.", // Falsa
        "As mensagens do Minix sao sincronas. ", // Verdadeira
        "O Estado abaixo eh seguro de acordo com o algoritmo do banqueiro:", // Verdadeira
        "A solucao abaixo resolve o problema da exclusao mutua: p1dentro = FALSE; p2dentro = FALSE; Processo 1 while (TRUE){ while (p2dentro == TRUE){};/*espera*/  p1dentro = TRUE; …..<regiã o critica>…. p1dentro = 0; ….. <resto do código>…. } Processo 2 while (TRUE){ while (p1dentro == TRUE){};/*espera*/ p2dentro = TRUE;  …..<regiã o critica>….  p2dentro = 0;  …..<resto do código>….  }" // Falsa
        };
    vector<bool> respostas_corretas = { true, false, false, true, true, false, true, true, false, true, 
                                        false, false, false, true, true, true, true, true, false, false, 
                                        true, false, true, true, false, true, true, true, false, false,
                                        false, false, true, true, true, false, true, true, false};
    vector<string> justificativas_corretas = {
        "",
        "Essa afirmacao eh falsa porque na multiprogramacao, varios programas compartilham a CPU simultaneamente, e nao ha monopolio de CPU por um unico programa.",
        "Essa afirmacao eh falsa porque o Minix tambem suporta outras formas de comunicacao entre processos, incluindo sinais, semaforos e memoria compartilhada.",
        "",
        "",
        "Essa afirmacao eh falsa porque na versao do Minix que utilizamos o SO eh dividido em tres camadas, nao em quatro, e as duas camadas inferiores sao as que possuem memorias independentes, nao as duas superiores.",
        "",
        "",
        "Essa afirmacao eh falsa porque o envio de mensagens no Minix eh um mecanismo sincrono que permite uma comunicacao segura entre processos, garantindo que a mensagem seja entregue ao processo destinatario sem a possibilidade de interferencia de outros processos.",
        "",
        "Essa afirmacao eh falsa porque a chamada de sistema execve() nao cria um novo processo. Na verdade, ela substitui o processo atual por um novo processo, carregando um novo programa na memoria e executando-o. ",
        "Essa afirmacao eh falsa porque a rotina malloc() pode utilizar outras chamadas de sistema alem de brk(), como sbrk() ou mmap(), dependendo da implementacao do sistema operacional. Alem disso, a rotina free() libera a memoria de forma apropriada, independentemente da localizacao na area de dados do processo.",
        "Essa afirmacao eh falsa porque a chamada open() serve para abrir um arquivo ou criar um novo, alem de permitir a verificacao das permissoes de acesso do arquivo. ",
        "",
        "",
        "",
        "",
        "",
        "Essa afirmacao eh falsa porque as chamadas ao System Task permitem que os programas obtenham informacoes sobre o sistema, mas nao permitem que tomem decisoes de escalonamento.",
        "Essa afirmacao eh falsa porque os procedimentos do System Task nao sao escritos diretamente em linguagem C, mas sim em linguagem de montagem, e eles sao responsaveis por tratar as interrupcoes e acionar o codigo apropriado em C.",
        "",
        "Essa afirmacao eh falsa porque existem quatro condicoes para uma boa solucao para o problema da exclusao mutua, nao apenas tres. Alem das condicoes mencionadas, a quarta condicao e que nenhum processo pode esperar indefinidamente para entrar na regiao critica.",
        "",
        "",
        "Essa afirmacao eh falsa porque a prioridade da fila nao determina o tempo que o processo leva para rodar.",
        "",
        "",
        "",
        "Essa afirmacao eh falsa porque argumentos tambem podem ser passados diretamente como parametros para a funcao rode() ou rodeveja(), sem a necessidade de criar um vetor de strings.",
        "Essa afirmacao eh falsa porque a exclusao mutua garantida pelo monitor nao eh suficiente para implementar semaforos.",
        "f",
        "Essa afirmacao eh falsa porque a estrategia de colocacao ''first fit'' eh usada em sistemas de memoria virtual, nao em sistemas de memoria real.",
        "",
        "",
        "",
        "Essa afirmacao eh falsa porque no Minix, o grande desafio de implementacao eh garantir a seguranca e estabilidade do sistema operacional, em vez de impedir a acumulacao de mensagens no buffer.",
        "",
        "",
        "Essa afirmacao eh falsa porque essa solucao não eh adequada para garantir a exclusao mutua, pois pode ocorrer uma situacao de interbloqueio, onde ambos os processos ficam presos no loop while de espera e nao conseguem entrar na regiao critica.",
    };

    // Inicia o quiz
    cout << "Bem-vindo ao Quiz de Afirmacoes da prova do Alan! Responda V para Verdadeiro ou F para Falso.\n";

    int acertos = 0;
    vector<bool> respostas_usuario;
    vector<string> justificativas_usuario;

    // Loop pelas afirmações e perguntas
    for (int i = 0; i < afirmacoes.size(); i++) {
        cout << "\nAfirmacao " << (i + 1) << ": " << afirmacoes[i] << endl;
        cout << "Sua resposta (V/F): ";
        char resposta;
        cin >> resposta;

        bool resposta_bool;
        string justificativa = "";

        if (resposta == 'V' || resposta == 'v') {
            resposta_bool = true;
        } else if (resposta == 'F' || resposta == 'f') {
            resposta_bool = false;
            cout << "Por favor, de uma justificativa: ";
            cin.ignore();
            getline(cin, justificativa);
        } else {
            cout << "Resposta invalida. Tente novamente." << endl;
            i--; // Volta para a mesma afirmação
            continue;
        }

        respostas_usuario.push_back(resposta_bool);
        justificativas_usuario.push_back(justificativa);

        if (resposta_bool == respostas_corretas[i]) {
            cout << "Resposta correta!" << endl;
            if (resposta_bool == false) { // Resposta correta, e é falsa
                cout << "Justificativa correta: " << justificativas_corretas[i] << endl;
            }
            acertos++; // Adiciona um ponto
        } else {
            cout << "Resposta incorreta." << endl;
            cout << "A resposta correta eh: " << (respostas_corretas[i] ? "Verdadeira" : "Falsa") << endl;
            cout << "Justificativa correta: " << justificativas_corretas[i] << endl;
        }
    }

    // Fornecer feedback final
    cout << "\nFim do quiz! Voce acertou " << acertos << " de 39 afirmacoes." << endl;
}