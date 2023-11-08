import socket
import ssl
import sys
import threading

'''
TO-DO:
- nao usar ssl
- backsocket
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
            SSLPORT = int(s.recv(5).decode('utf-8'))

            backsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            backsocket.connect((IP, SSLPORT))

            context = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)
            context.check_hostname = False
            context.verify_mode = ssl.CERT_NONE

            ss = context.wrap_socket(socket.socket(socket.AF_INET, socket.SOCK_STREAM), server_hostname = IP)
            ss.connect((IP, SSLPORT))

            envia_comando_ao_socket('ok', ss)

            print("[C] Cliente conectado")

            while True:
                out = ''
                try:
                    while not out:
                        out = input(self.prompt)
                except:        
                    ss.close()
                    backsocket.close()
                    break

                comando = out.split()[0]
                try:
                    if comando == 'teste':
                        resposta = envia_comando_ao_servidor(out, ss, s, backsocket, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respostaondeu ao comando {comando}")
                        else: print(f"[C] Comando: {comando}; Retornou: {resposta}")
                    else:
                        resposta = envia_comando_ao_servidor(out, ss, s, backsocket, ss)                      
                        if not resposta:
                            print(f"[C] Servidor não respostaondeu ao comando {comando}")
                        else: print(f"[C] {resposta}")
                except:
                    print("[C] Terminando o programa")
                    break

def envia_comando_ao_socket(comando: str, s: socket.socket):
    comando = bytearray(comando.encode())
    s.sendall(comando)

def recebe_resposta_do_socket(s: socket.socket):
    return s.recv(1024).decode('utf-8')

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
        return 1, s_g[0], backsocket_g[0], ss_g[0]
    else:
        return 0, None, None, None

def envia_comando_ao_servidor(comando: str, used_socket: socket.socket, s: socket.socket, backsocket: socket.socket, ss: ssl.SSLSocket):
    envia_comando_ao_socket(comando, used_socket)
    resposta = recebe_resposta_do_socket(used_socket)

    while resposta == '':
        #Conexão fechada
        sucesso, s, backsocket, ss = atualiza_sockets()
        if not sucesso:
            break
        envia_comando_ao_socket(comando, s)
        resposta = recebe_resposta_do_socket(s)

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
