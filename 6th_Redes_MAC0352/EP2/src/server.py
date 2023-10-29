import os
import signal
import sys

#from tcp import ServidorTCP
#from udp import ServidorUDP
#from backend import Backend

def main():
    # Verifica se foram passados dois argumentos na linha de comando
    if len(sys.argv) == 3:
        porta_tcp = int(sys.argv[1])
        porta_udp = int(sys.argv[2])
    else:
        print("Nenhum argumento fornecido. Usando portas padrão para TCP e UDP.")
        porta_tcp = 8080 
        porta_udp = 12345 

    print("Servidor TCP rodando na porta:", porta_tcp)
    print("Servidor UDP rodando na porta:", porta_udp)

    pid_tcp, pid_udp = None, None
    '''
    cria servidor
    servidor = Backend()
    '''


    # Cria um processo filho para o servidor TCP
    if (pid_tcp := os.fork()) == 0:
        print("Processo filho do TCP criado")
        '''
        registra mensagens do TCP
        common/logger.cp
        logger_tcp = Logger("TCP", "tcp.txt")
        '''

        '''
        if servidor.temUsuariosAtivos():
            logger_tcp.escrever("Principal", "O servidor foi encerrado enquanto clientes estavam conectados! Reconectando!")
        '''
        

        # Define um sinal para matar o processo pai se ele morrer
        # prctl(PR_SET_PDEATHSIG, SIGKILL);

        '''
        common/util.cpp
        resetCleanUpHook()
        '''

        '''
        servidor_tcp = ServidorTCP(sys.argv[1])
        servidor_tcp.escutarMensagens(servidor, logger_tcp)
        '''
        
        sys.exit(0)

    # Cria um processo filho para o servidor UDP
    if (pid_udp := os.fork()) == 0:
        print("Processo filho do UDP criado")

        '''
        registra mensagens do TCP
        common/logger.cp
        logger_tcp = Logger("UDP", "udp.txt")
        '''

        '''
        if servidor.temUsuariosAtivos():
            logger_tcp.escrever("Principal", "O servidor foi encerrado enquanto clientes estavam conectados! Reconectando!")
        '''
        

        # Define um sinal para matar o processo pai se ele morrer
        # os.prctl(os.PR_SET_PDEATHSIG, signal.SIGKILL)

        '''
        common/util.cpp
        resetCleanUpHook()
        '''
        
        '''
        servidor_udp = ServidorUTP(sys.argv[1])
        servidor_udp.escutarMensagens(servidor, logger_udp)
        '''
        
        sys.exit(0)

    # Aguarda a finalização dos processos filhos
    os.waitpid(pid_tcp, 0)
    os.waitpid(pid_udp, 0)

if __name__ == "__main__":
    main()
