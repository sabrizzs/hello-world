import socket
import sys
import threading
from pacman import PacMan
from typing import Tuple
import time


''' 
TO-DO:
- servidor udp
- lista de status com uma linha vazia no final
- out
- atualiza sockets
- ok
- esvaziar caixa de entrada apenas quando o jogo acabar
- atualizar multiplayer quando jogo acabar 
- desafio nao funciona quando o cliente reseta e o servidor nao
- lidar com gameover antes do desafiante chegar


'''

class Cliente:
    def __init__(self, host, port):
        self.IP = host
        self.PORT = port
        self.prompt = "Pac-Man> "

        self.jogo_socket = None
        self.multiplayer = False
        self.jogador_remoto = False
        self.terminou_jogo = False



        self.jogo_ip = None
        self.jogo_porta = None
          
    def conexao(self):
        print("[C] Estabelecendo conexão...")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.IP, self.PORT))

            ss_port = int(s.recv(5).decode('utf-8'))

            ss = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            ss.connect((IP, ss_port))
            
            envia_comando_ao_servidor('ok', ss)

            print("[C] Cliente conectado")
 
            servidor_ouvinte_thread = threading.Thread(target=self.servidor_ouvinte, args=(s, ss))
            servidor_ouvinte_thread.start()

            while True:
                
                if self.jogador_remoto:
                    while not self.terminou_jogo:
                        pass
                    #interrompe o input dessa thread enquanto esta jogando
                    #depois enviar comando ao servidor com op resultado do jogo
                    #redefinir variaveis multiplayer e jogador remoto

                out = ''
                try:                   
                    while not out:
                        if self.jogador_remoto: print("JOgador remoto! true!")
                        out = input(self.prompt)
  
                except:        
                    ss.close()
                    break

                comando = out.split()[0]

                #diminuir uso de ifs >:(
                try:
                    if comando == 'teste':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)

                    elif comando == 'senha':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)

                    elif comando == 'novo':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)

                    elif comando == 'entra':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)

                    elif comando == 'lideres':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)

                    elif comando == 'l':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)

                    elif comando == 'inicia':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)
                        self.inicia_jogo(1)

                    elif comando == 'desafio':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        elif resposta.split()[1] == "Erro:":
                            print(resposta)
                        else:
                            self.jogador_remoto = True
                            print(resposta)

                            # desafiante manda o desafio !!

                    elif comando == 'sai':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)

                    else:
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)
                except:
                    print("[C] Terminando o programa")
                    envia_comando_ao_servidor("exit", ss) 
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
                        envia_comando_ao_socket(atributos, s)

                    else:
                        atributos = ''
                        print("[P] Esperando o próximo turno...")
                        while not atributos:
                            atributos = recebe_resposta_do_socket(s)
       
                        pacman = atributos.split('/')[0]
                        print(pacman)
                        x = int((pacman.split(', ')[0])[1:])
                        y = int((pacman.split(', ')[1])[:-1])
                        jogo.pacman = (x, y)

                        if jogo.arena[x][y] == '.':
                            jogo.arena[x] = jogo.arena[x][:y] + ' ' + jogo.arena[x][y + 1:]

                        fantasma_local = atributos.split('/')[1]
                        print(fantasma_local)
                        x = int((fantasma_local.split(', ')[0])[1:])
                        y = int((fantasma_local.split(', ')[1])[:-1])
                        jogo.fantasma_local = (x, y)
                    
                    # jogador 2 envia a posição que começou no jogo para o jogador 1
                    if jogador == 2:
                        jogo.fantasma_remoto = jogo.posicao_aleatoria()
                        while jogo.fantasma_remoto == jogo.pacman: 
                            jogo.fantasma_remoto = jogo.posicao_aleatoria()
                        atributos = f"{jogo.fantasma_remoto}"
                        envia_comando_ao_socket(atributos, s)

                    else:
                        atributos = ''
                        while not atributos:
                            atributos = recebe_resposta_do_socket(s)
                        print(atributos)
                        x = int((atributos.split(', ')[0])[1:])
                        y = int((atributos.split(', ')[1])[:-1])
                        jogo.fantasma_remoto = (x, y)
                    
                    primeira_rodada_jogador_2 = False

                jogo.mostra_arena()
                time.sleep(1)

                # fantasma local
                if jogador == 1:
                    x, y = jogo.move_fantasma_local(1, -1, -1)
                    direcao = f"{x} {y}"
                    envia_comando_ao_socket(direcao, s)
                else:
                    direcao = ''
                    while not direcao:
                        direcao = recebe_resposta_do_socket(s)
                    x = int(direcao.split()[0])
                    y = int(direcao.split()[1])
                    jogo.move_fantasma_local(0, x, y)
                    
                
                print("[P] Fantasma local fez uma movimentação!")
                jogo.mostra_arena()
                if jogo.checa_colisao(): break
                time.sleep(1)
                
                # fantasma remoto
                if jogador == 2:
                    direcao = input("Pac-Man> Digite a direção para mover o fantasma remoto (w/a/s/d):\nPac-Man> ")
                    jogo.move_fantasma_remoto(direcao)
                    envia_comando_ao_socket(direcao, s)

                else:
                    print("[P] Aguardando movimentação do fantasma remoto (jogador 2)...")
                    direcao = ''
                    while not direcao:
                        direcao = recebe_resposta_do_socket(s)
                    jogo.move_fantasma_remoto(direcao)

                
                print("[P] Fantasma remoto fez uma movimentação!")
                jogo.mostra_arena()
                if jogo.checa_colisao(): break
                time.sleep(1)

                # pacman
                if jogador == 1:
                    direcao = input("Pac-Man> Digite a direção para mover o Pac-Man (w/a/s/d):\nPac-Man> ")
                    jogo.move_pacman(direcao)
                    envia_comando_ao_socket(direcao, s)
                else:
                    print("[P] Aguardando movimentação do pacman (jogador 1)...")
                    direcao = ''
                    while not direcao:
                        direcao = recebe_resposta_do_socket(s)
                    jogo.move_pacman(direcao)

                
                print("[P] Pacman fez uma movimentação!")
                if jogo.checa_colisao():
                    jogo.mostra_arena()
                    break
                
            else:
                jogo.turno()

        pontuacao = jogo.game_over()
                    
    def servidor_ouvinte(self, s: socket.socket, ss: socket.socket):
        while True:
            resposta = "0"
            try:
                while resposta == "0":
                    resposta = envia_comando_ao_servidor("caixadeentrada", s)
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

        resposta = envia_comando_ao_servidor(mensagem, ss)

        if not resposta: return
        if resposta != "ok": jogo_socket_ouvinte.close()
        else:
            jogo_socket, jogo_addr = jogo_socket_ouvinte.accept() #esta esperando uma resposta
            jogo_socket_ouvinte.close()
            self.jogo_socket = jogo_socket
            
    def conexao_desafiante(self, ss:socket.socket, mensagem):
        print(mensagem)
        jogo_porta = int(mensagem.split()[2])
        jogo_ip = mensagem.split()[3]
        print(f"Jogo porta: {jogo_porta} , Jogo ip: {jogo_ip}")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as jogo_socket:
            jogo_socket.connect((jogo_ip, jogo_porta))
            #refatorar
            self.jogo_ip = jogo_ip
            self.jogo_porta = jogo_porta
            self.multiplayer = True
            self.jogo_socket = jogo_socket         
            self.inicia_jogo(2)

            self.terminou_jogo = True
            
            # resposta = envia_comando_ao_servidor("ok", ss) envia resultado do jogo ao servidor

def envia_comando_ao_socket(comando: str, s: socket.socket):
    comando = bytearray(comando.encode())
    s.sendall(comando)

def recebe_resposta_do_socket(s: socket.socket):
    return s.recv(1024).decode('utf-8')

# coordena e sincroniza a manipulação de sockets em um contexto multithread 
def atualiza_sockets():
    global reconectado

    mutex_reconectado.acquire()
    r = reconectado
    mutex_reconectado.release()
    while r == 0:
        time.sleep(1)
        mutex_reconectado.acquire()
        r = reconectado
        mutex_reconectado.release()

    mutex_reconectado.acquire()
    reconectado = 0
    mutex_reconectado.release()

    if r == 1:
        return 1, ss_g[0]
    else:
        return 0, None

def envia_comando_ao_servidor(comando: str, ss: socket.socket):
    envia_comando_ao_socket(comando, ss)
    resposta = recebe_resposta_do_socket(ss)

    while resposta == '':
        sucesso, ss = atualiza_sockets()
        if not sucesso:
            break
        envia_comando_ao_socket(comando, ss)
        resposta = recebe_resposta_do_socket(ss)

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

    if len(sys.argv) == 3:
        IP = sys.argv[1]
        PORT = int(sys.argv[2])
    else:
        print("Nenhum argumento fornecido. Forneça as portas como argumentos, por exemplo: python client.py 127.0.0.1 8080") 
        #temporario
        IP = '127.0.0.1'
        PORT = 8080
        #exit(1)

    print(f"[C] Cliente no IP {IP} irá conectar na porta {PORT} do TCP.")
    
    cliente = Cliente(IP, PORT)
    cliente.conexao()


if __name__ == "__main__":
    main()