#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>

#include <tcp.hpp>
#include <udp.hpp>
#include <backend.hpp>

using namespace std;

int main (int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr,"Uso: %s <Porta TCP> <Porta UDP>\n",argv[0]);
        fprintf(stderr,"Vai rodar um servidor TCP e UDP nas portas <Porta TCP> e <Porta UDP>, respectivamente\n");
        exit(EXIT_FAILURE);
    }

    pid_t tcppid, udppid;
    Backend *server = new Backend();
    setCleanUpHook();

    if ((tcppid = fork()) == 0) {
        Logger *tcpLogger = new Logger("TCP", "tcp.txt");
        if(server->hasActiveUsers()) {
            tcpLogger->write("Main", "O servidor foi encerrado enquanto clientes estavam conectados! Reconectando!");
        }

        prctl(PR_SET_PDEATHSIG, SIGKILL);
        resetCleanUpHook();
        TCPServer *tcpManager = new TCPServer(argv[1]);
        tcpManager->listenToMessages(server, tcpLogger);
        exit(EXIT_SUCCESS);
    }

    if ((udppid = fork()) == 0) {
        Logger *udpLogger = new Logger("UDP", "udp.txt");
        if(server->hasActiveUsers()) {
            udpLogger->write("Main", "O servidor foi encerrado enquanto clientes estavam conectados! Reconectando!");
        }
        
        prctl(PR_SET_PDEATHSIG, SIGKILL);
        resetCleanUpHook();
        UDPServer *udpManager = new UDPServer(argv[2]);
        udpManager->listenToMessages(server, udpLogger);
        exit(EXIT_SUCCESS);
    }

    if(waitpid(tcppid, NULL, 0) == -1 || waitpid(udppid, NULL, 0) == -1) {
        perror("waitpid :(\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
