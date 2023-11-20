import socket
import sys
import threading
from pacman import PacMan
from typing import Tuple


''' 
TO-DO:
- servidor udp
- lista de status com uma linha vazia no final
- out
- atualiza sockets
- ok
- esvaziar caixa de entrada apenas quando o jogo acabar

'''

class Cliente:
    def __init__(self, host, port):
        self.IP = host
        self.PORT = port
        self.prompt = "Pac-Man> "
          
    def conexao(self):
        print("[C] Estabelecendo conexão...")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.IP, self.PORT))

            ss_port = int(s.recv(5).decode('utf-8'))
            print(f"[T] port cliente: {ss_port}")

            ss = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            ss.connect((IP, ss_port))
            
            envia_comando_ao_servidor('ok', ss)

            print("[C] Cliente conectado")
 
            servidor_ouvinte_thread = threading.Thread(target=self.servidor_ouvinte, args=(s, ss))
            servidor_ouvinte_thread.start()

            while True:
                
                out = ''
                try:                   
                    while not out:
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
                        self.inicia_jogo(ss)

                    elif comando == 'desafio':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: 
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

    def inicia_jogo(self, ss: socket.socket):
        jogo = PacMan()
        while True:
            game_over, pontuacao = jogo.checa_game_over()
            if game_over:
                break  
            jogo.turno()
        envia_comando_ao_servidor(f'pontuacao {pontuacao}', ss)

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
                        print("[T] Iniciando conexão do jogo")
                        self.conexao_desafiado(ss)
                        print("[T] Criou a conexão do jogo")

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
            print("[T] 5")
            print(f"Jogo porta: {jogo_porta}")
            jogo_socket, jogo_addr = jogo_socket_ouvinte.accept() #esta esperando uma resposta
            print("[T] Jogo deve iniciar aqui: conexão desafiado.")
            jogo_socket_ouvinte.close()

            with jogo_socket:
                pass
            

    def conexao_desafiante(self, ss:socket.socket, mensagem):
        print("[T] Na função conexao_desafiante")
        print(mensagem)
        jogo_porta = int(mensagem.split()[2])
        jogo_ip = mensagem.split()[3]
        print(f"Jogo porta: {jogo_porta} , Jogo ip: {jogo_ip}")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as jogo_socket:
            jogo_socket.connect((jogo_ip, jogo_porta))

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