import sys
import socket
import ssl
from typing import Tuple

class ServidorTCP:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def iniciar(self):
        print(f"[S] Servidor TCP rodando na porta {self.port} e no host {self.host}")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s_listener:
            s_listener.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s_listener.bind((self.host, self.port))
            s_listener.listen()
            try:
                while(True):                
                    print("[S] Esperando conexão com algum cliente")
                    conn, addr = s_listener.accept()
                    print(f"[S] Conexão estabelecida com {addr}")
                    cliente = Cliente(conn, addr)
            except:
                print("[S] Servidor finalizado")

class Cliente:
    def __init__(self, socket: socket.socket, addr):
        self.s = socket
        self.addr = addr

        s_listen, port = create_listener_socket()
        send_command_to_socket(self.s, port)

        self.s_sender, addr_background = s_listen.accept()
        self.ss, addr_SSL = setup_SSL_socket(s_listen)

        client_answer = self.ss.recv(1024).decode('utf-8')
        
        print(f"[S] Recebeu resposta do cliente: {client_answer}")

        #"ok" caso nova conexão
        if client_answer == 'ok':
            print(f"[S] Cliente {addr} conectou")

def create_listener_socket() -> Tuple[socket.socket, str]:
    """Cria um socket de listen usando uma porta disponível.
       Retorna o socket (pronto para accept) e sua porta em 
       uma string com 5 caracteres."""

    s_listen = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_listen.bind(('', 0))
    s_listen.listen(5)
    _, port1 = s_listen.getsockname()
    str_port1 = '%05d' % port1
    return s_listen, str_port1

def setup_SSL_socket(s_listen: socket.socket):
    """Recebe um socket de listen (pronto) e cria um socket
       SSL a partir daquele. Retorna o socket e seu endereço."""

    context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    context.load_cert_chain('server.pem', 'server.key', password = 'servidor')
    ssock = context.wrap_socket(s_listen, server_side = True)
    #ssock.listen(5)
    return ssock.accept()

def send_command_to_socket(s: socket.socket, msg: str):
    s.sendall(bytearray(msg.encode()))
        
def main():
    if len(sys.argv) == 3:
        porta_tcp = int(sys.argv[1])
        porta_udp = int(sys.argv[2])
    else:
        print("[S] Nenhum argumento fornecido. Forneça as portas como argumentos, por exemplo: python servidor.py 8080 12345")
        #temporario
        porta_tcp = 8080
        porta_udp = 12345
        #exit(1)

    print(f"[S] Servidor irá rodar na porta {porta_tcp} do TCP.")

    servidor_tcp = ServidorTCP('', porta_tcp)
    servidor_tcp.iniciar()
    
    
    #servidor_udp = ServidorUDP('127.0.0.1', porta_udp)

if __name__ == "__main__":
    main()
