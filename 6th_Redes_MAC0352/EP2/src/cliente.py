import socket
import sys
import threading
from pacman import PacMan


''' 
TO-DO:
- servidor udp
- lista de status com uma linha vazia no final
- out
- atualiza sockets
- ok

- lideres
- inicia
...
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
 
            servidor_ouvinte_thread = threading.Thread(target=self.servidor_ouvinte, args=(s,))
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
                        self.inicia_jogo()

                    elif comando == 'desafio':
                        resposta = envia_comando_ao_servidor(out, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respondeu ao comando {comando}")
                        else: print(resposta)

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

    def inicia_jogo(self):
        jogo = PacMan()
        while not jogo.checa_game_over():
            jogo.turno()

    def servidor_ouvinte(self, s: socket.socket):
        while True:
            resposta = "0"
            try:
                while resposta == "0":
                    resposta = envia_comando_ao_servidor("caixadeentrada", s)
                if resposta != "0":
                    print(resposta, end='')
                    resposta = "0"
            except:        
                s.close()
                break

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