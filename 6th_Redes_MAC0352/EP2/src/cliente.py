import socket
import sys
import threading
from pacman import PacMan
from typing import Tuple
import time


''' 
TO-DO:
- lista de status com uma linha vazia no final
- out
- atualiza sockets
- ok
- desafio nao funciona quando o cliente reseta e o servidor nao
- lidar com gameover antes do desafiante chegar

'''

class Cliente:
    def __init__(self, host, port):
        self.IP = host
        self.PORT = port
        self.ss_port = None
        self.protocolo = None
        self.prompt = "Pac-Man> "

        self.jogo_socket = None
        self.multiplayer = False
        self.jogador_remoto = False
        self.terminou_jogo = False

        self.jogo_ip = None
        self.jogo_porta = None
          
    def conexao_tcp(self):
        self.protocolo = 'tcp'
        #print("[C] Estabelecendo conexão...")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.IP, self.PORT))

            self.ss_port = int(s.recv(5).decode('utf-8'))

            ss = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            ss.connect((IP, self.ss_port))
            envia_comando_ao_servidor('ok', ss, self.protocolo, None)
            print("[C] Conectado!")
 
            servidor_ouvinte_thread = threading.Thread(target=self.servidor_ouvinte, args=(s, ss))
            servidor_ouvinte_thread.start()

            self.interpretador_comandos(ss)

    def conexao_udp(self):
        self.protocolo = 'udp'
        #print("[C] Estabelecendo conexão...")
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.sendto(b"conectado", ('', self.PORT)) #ip era self.IP

            msg, addr = s.recvfrom(1024)
            self.ss_port = int(msg.decode('utf-8'))

            ss = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            ss.sendto(b'ok', ('', self.ss_port))
            print(f"[C] Conectado!")

            servidor_ouvinte_thread = threading.Thread(target=self.servidor_ouvinte, args=(s, ss))
            servidor_ouvinte_thread.start()

            self.interpretador_comandos(ss)

    def interpretador_comandos(self, ss):
        while True:
            
            if self.jogador_remoto:
                while not self.terminou_jogo: # interrompe o input dessa thread enquanto esta jogando
                    pass
                self.terminou_jogo = False
                
            out = ''
            try:                   
                while not out:
                    out = input(self.prompt)

            except:        
                ss.close()
                break

            comando = out.split()[0]

            try:
                if comando == 'teste':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                   
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    else: print(resposta)

                elif comando == 'senha':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                     
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    else: print(resposta)

                elif comando == 'novo':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                       
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    else: print(resposta)

                elif comando == 'entra':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                    
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    else: print(resposta)

                elif comando == 'lideres':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                     
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    else: print(resposta)

                elif comando == 'l':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                        
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    else: print(resposta)

                elif comando == 'inicia':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                         
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    elif resposta.split()[1] == "Erro:":
                        print(resposta)
                    else: 
                        print(resposta)
                        pontuacao_pacman, pontuacao_fantasma_remoto, vitoria = self.inicia_jogo(1)
                        resposta = envia_comando_ao_servidor(f'pontuacao {"vitoria" if vitoria else "derrota"} {pontuacao_pacman}', ss, self.protocolo, self.ss_port)   
                        print(resposta)

                elif comando == 'desafio':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                       
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    elif resposta.split()[1] == "Erro:":
                        print(resposta)
                    else:
                        self.jogador_remoto = True
                        print(resposta)

                elif comando == 'sai':
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                     
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    else: print(resposta)

                elif comando == 'tchau':
                    print("[C] Terminando o programa")
                    envia_comando_ao_servidor("tchau", ss, self.protocolo, self.ss_port)   
                    ss.close()
                    break

                else:
                    resposta = envia_comando_ao_servidor(out, ss, self.protocolo, self.ss_port)                        
                    if not resposta:
                        print(f"[C] Servidor não respondeu ao comando {comando}")
                    else: print(resposta)
            except:
                print("[C] Terminando o programa")
                envia_comando_ao_servidor("tchau", ss, self.protocolo, self.ss_port)   
                ss.close()
                break

    def inicia_jogo(self, jogador):
        jogo = PacMan()
        primeira_rodada_jogador_2 = True

        while True:
            if self.jogo_socket != None:
                s = self.jogo_socket

                # jogador 1 envia informações do seu jogo ao jogador 2 que recem chegou
                if primeira_rodada_jogador_2:
                    print("[T] Segundo jogador entrou no jogo!")

                    if jogador == 1:
                        atributos = f"{jogo.pacman}/{jogo.fantasma_local}"
                        envia_comando_ao_socket(s, atributos, 'tcp', None)

                    else:
                        atributos = ''
                        print("[P] Esperando o próximo turno...")
                        while not atributos:
                            atributos = recebe_resposta_do_socket(s, 'tcp')
       
                        pacman = atributos.split('/')[0]
                        x = int((pacman.split(', ')[0])[1:])
                        y = int((pacman.split(', ')[1])[:-1])
                        jogo.pacman = (x, y)

                        if jogo.arena[x][y] == '.':
                            jogo.arena[x] = jogo.arena[x][:y] + ' ' + jogo.arena[x][y + 1:]

                        fantasma_local = atributos.split('/')[1]
                        x = int((fantasma_local.split(', ')[0])[1:])
                        y = int((fantasma_local.split(', ')[1])[:-1])
                        jogo.fantasma_local = (x, y)
                    
                    # jogador 2 envia a posição que começou no jogo para o jogador 1
                    if jogador == 2:
                        jogo.fantasma_remoto = jogo.posicao_aleatoria()
                        while jogo.fantasma_remoto == jogo.pacman: 
                            jogo.fantasma_remoto = jogo.posicao_aleatoria()
                        atributos = f"{jogo.fantasma_remoto}"
                        envia_comando_ao_socket(s, atributos, 'tcp', None)

                    else:
                        atributos = ''
                        while not atributos:
                            atributos = recebe_resposta_do_socket(s, 'tcp')
                        x = int((atributos.split(', ')[0])[1:])
                        y = int((atributos.split(', ')[1])[:-1])
                        jogo.fantasma_remoto = (x, y)
                    
                    primeira_rodada_jogador_2 = False

                print(jogo.mostra_arena())
                time.sleep(1)

                # fantasma local
                if jogador == 1:
                    x, y = jogo.move_fantasma_local(1, -1, -1)
                    direcao = f"{x} {y}"
                    envia_comando_ao_socket(s, direcao, 'tcp', None)
                else:
                    direcao = ''
                    while not direcao:
                        direcao = recebe_resposta_do_socket(s, 'tcp')
                    x = int(direcao.split()[0])
                    y = int(direcao.split()[1])
                    jogo.move_fantasma_local(0, x, y)
                    
                
                print("[P] Fantasma local fez uma movimentação!")
                print(jogo.mostra_arena())
                if jogo.game_over:
                    if jogador == 2: jogo.vitoria = True
                    break
                time.sleep(1)
                
                # fantasma remoto
                if jogador == 2:
                    direcao = input("Pac-Man> Digite a direção para mover o fantasma remoto (w/a/s/d):\nPac-Man> ")
                    if direcao == "encerra":
                        envia_comando_ao_socket(s, direcao, 'tcp', None)
                        print("[P] Partida encerrada!")
                        self.finaliza_jogo()
                        return jogo.pontuacoes()
                    jogo.move_fantasma_remoto(direcao)
                    envia_comando_ao_socket(s, direcao, 'tcp', None)

                else:
                    print("[P] Aguardando movimentação do fantasma remoto (jogador 2)...")
                    direcao = ''
                    while not direcao:
                        direcao = recebe_resposta_do_socket(s, 'tcp')
                    if direcao == "encerra":
                            print("[P] O jogador 2 encerrou a partida!")
                            self.jogo_socket = None
                            primeira_rodada_jogador_2 = True
                            jogo.remove_fantasma_remoto()
                    else: jogo.move_fantasma_remoto(direcao)

                if self.jogo_socket != None:
                    print("[P] Fantasma remoto fez uma movimentação!")
                    print(jogo.mostra_arena())
                    if jogo.game_over:
                        if jogador == 2: jogo.vitoria = True
                        break
                    time.sleep(1)

                    # pacman
                    if jogador == 1:
                        direcao = input("Pac-Man> Digite a direção para mover o Pac-Man (w/a/s/d):\nPac-Man> ")
                        if direcao == "encerra":
                            print("[P] Partida encerrada!")
                            self.finaliza_jogo()
                            envia_comando_ao_socket(s, direcao, 'tcp', None)
                            return jogo.pontuacoes()
                        jogo.move_pacman(direcao)
                        envia_comando_ao_socket(s, direcao, 'tcp', None)
                    else:
                        print("[P] Aguardando movimentação do pacman (jogador 1)...")
                        direcao = ''
                        while not direcao:
                            direcao = recebe_resposta_do_socket(s, 'tcp')
                            if direcao == "encerra":
                                print("[P] O jogador 1 encerrou a partida!")
                                self.finaliza_jogo()
                                return jogo.pontuacoes()
                        jogo.move_pacman(direcao)

                    
                    print("[P] Pacman fez uma movimentação!")
                    jogo.mostra_arena()
                    if jogo.vitoria:
                        print(jogo.mostra_arena())
                        break
                    elif jogo.game_over:
                        if jogador == 2: jogo.vitoria = True
                        print(jogo.mostra_arena())
                        break
                    time.sleep(1)
                
            else:
                print(jogo.mostra_arena())
                time.sleep(1)

                print("[P] Fantasma local fez uma movimentação!")
                jogo.move_fantasma_local(1, -1, -1)
                print(jogo.mostra_arena())    
                if jogo.game_over:
                    break   
                time.sleep(1)
                
                direcao = input("Pac-Man> Digite a direção para mover o Pac-Man (w/a/s/d):\nPac-Man> ")
                if direcao == "encerra":
                    print("[P] Partida encerrada!")
                    self.finaliza_jogo()
                    return jogo.pontuacoes()
                jogo.move_pacman(direcao)
                jogo.mostra_arena()
                if jogo.vitoria:
                    print(jogo.mostra_arena())
                    break
                elif jogo.game_over:
                    jogo.vitoria = True
                    print(jogo.mostra_arena())
                    break
                time.sleep(1)

        self.finaliza_jogo()
        return jogo.pontuacoes()

    def finaliza_jogo(self):
        self.jogo_socket = None
        self.multiplayer = False
        self.jogador_remoto = False
        self.terminou_jogo = True

    def servidor_ouvinte(self, s: socket.socket, ss: socket.socket):
        while True:
            resposta = "0"
            try:
                while resposta == "0":
                    resposta = envia_comando_ao_servidor("heartbeat", s, self.protocolo, self.PORT)   
                if resposta != "0":
                    if resposta.split()[0] == "Desafio:":
                        print(resposta, end='')

                        # desafiado recebe desafio e cria a conexao do jogo !
                        self.conexao_desafiado(ss)
                        resposta = "0"

                    elif resposta.split()[0] == "Conexão:": 
                        self.conexao_desafiante(ss, resposta)
            except:        
                s.close()
                break

    def conexao_desafiado(self, ss:socket.socket):
        jogo_socket_ouvinte, jogo_porta = cria_socket_ouvinte()
        jogo_socket_ouvinte.listen()

        mensagem = f"desafiado {jogo_porta}" #mando a porta do jogo para o servidor

        resposta = envia_comando_ao_servidor(mensagem, ss, self.protocolo, self.ss_port)   

        if not resposta: return
        if resposta != "ok": jogo_socket_ouvinte.close()
        else:
            jogo_socket, jogo_addr = jogo_socket_ouvinte.accept() #esta esperando uma resposta
            jogo_socket_ouvinte.close()
            self.jogo_socket = jogo_socket
            
    def conexao_desafiante(self, ss:socket.socket, mensagem):
        jogo_porta = int(mensagem.split()[2])
        jogo_ip = mensagem.split()[3]

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as jogo_socket:
            jogo_socket.connect((jogo_ip, jogo_porta))

            self.jogo_ip = jogo_ip
            self.jogo_porta = jogo_porta
            self.multiplayer = True
            self.jogo_socket = jogo_socket   

            pontuacao_pacman, pontuacao_fantasma_remoto, vitoria = self.inicia_jogo(2)
            resposta = envia_comando_ao_servidor(f'pontuacao {"vitoria" if vitoria else "derrota"} {pontuacao_fantasma_remoto}', ss, self.protocolo, self.ss_port)      
            print(f"{resposta}\nPac-Man> ")

def envia_comando_ao_socket(s: socket.socket, comando: str, protocolo, udp_port):
    comando = bytearray(comando.encode())
    if protocolo == 'tcp':
        s.sendall(comando)
    elif protocolo == 'udp':
        s.sendto(comando, ('', udp_port))

def recebe_resposta_do_socket(s: socket.socket, protocolo):
    if protocolo == 'tcp':
        return s.recv(1024).decode('utf-8')
    elif protocolo == 'udp':
        resposta, addr = s.recvfrom(1024)
        resposta = resposta.decode('utf-8')
        return resposta

def envia_comando_ao_servidor(comando: str, ss: socket.socket, protocolo, udp_port):
    envia_comando_ao_socket(ss, comando, protocolo, udp_port)
    resposta = recebe_resposta_do_socket(ss, protocolo)

    while resposta == '':
        envia_comando_ao_socket(ss, comando, protocolo, udp_port)
        resposta = recebe_resposta_do_socket(ss, protocolo)
    return resposta

def cria_socket_ouvinte() -> Tuple[socket.socket, str]:
    s_ouvinte = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_ouvinte.bind(('', 0))
    s_ouvinte.listen(5)
    _, port1 = s_ouvinte.getsockname()
    str_port1 = '%05d' % port1
    return s_ouvinte, str_port1

def main():
    global IP
    global PORT

    if len(sys.argv) == 4:
        IP = sys.argv[1]
        PORT = int(sys.argv[2])
        protocolo = sys.argv[3].lower()
    else:
        print("Forneça o IP, a porta e o protocolo como argumentos, por exemplo: python client.py 127.0.0.1 8080 tcp")
        '''print("[C] Rodando o cliente nos argumentos pré definidos ip: 127.0.0.1 porta: 8080 protocolo: x")
        IP = '127.0.0.1'
        PORT = 8080
        protocolo = 'tcp' '''
        exit(1)

    print(f"[C] Cliente no IP {IP} irá conectar na porta {PORT} usando o protocolo {protocolo.upper()}.")
    cliente = Cliente(IP, PORT)

    if protocolo == 'tcp':
        cliente.conexao_tcp()
    elif protocolo == 'udp':
        cliente.conexao_udp()
    else:
        print("Protocolo inválido. Use 'tcp' ou 'udp'.")


if __name__ == "__main__":
    main()