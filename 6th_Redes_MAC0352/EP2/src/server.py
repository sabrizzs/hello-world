import sys
import socket
import threading
from typing import Tuple

class ServidorTCP:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def inicia(self):
        print(f"[S] Servidor TCP rodando na porta {self.port} e no host {self.host}")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s_ouvinte:
            s_ouvinte.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s_ouvinte.bind((self.host, self.port))
            s_ouvinte.listen()
            try:
                while(True):                
                    print("[S] Esperando conexão com algum cliente")
                    conn, addr = s_ouvinte.accept()
                    print(f"[S] Conexão estabelecida com {addr}")
                    cliente = Cliente(conn, addr)
                    cliente.threads()
            except:
                print("[S] Servidor finalizado")
                exit(0)

class Cliente:
    def __init__(self, socket: socket.socket, addr):
        self.s = socket
        self.addr = addr

        s_ouvinte, port = cria_socket_ouvinte()
        envia_comando_ao_socket(self.s, port)
        print(f"[T] port servidor: {port}")

        self.ss, addr_background = s_ouvinte.accept()
        resposta = self.ss.recv(1024).decode('utf-8')
        
        print(f"[S] Recebeu resposta do cliente: {resposta}")

        #"ok" caso nova conexão
        if resposta == "ok":
            print(f"[S] Cliente {addr} conectou")

    def threads(self):
        '''  O uso de threads garante que o servidor seja capaz de 
             atender a várias conexões de clientes simultaneamente '''
        thread = threading.Thread(target=self.interpretador, args=())
        thread.start()

    def interpretador(self):
        with self.ss as ss:
            while True:
                comando = ''
                try:
                    comando = ss.recv(1024).decode('utf-8')
                except:
                    print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    break
                comando = comando.split()
                if not comando:
                    print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    break
                elif comando[0] == 'teste':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    envia_comando_ao_socket(ss, "Cliente enviou: teste")
                else:
                    print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                    envia_comando_ao_socket(ss, "Comando não reconhecido")

def cria_socket_ouvinte() -> Tuple[socket.socket, str]:
    s_ouvinte = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_ouvinte.bind(('', 0))
    s_ouvinte.listen(5)
    _, port1 = s_ouvinte.getsockname()
    str_port1 = '%05d' % port1
    return s_ouvinte, str_port1

def envia_comando_ao_socket(s: socket.socket, msg: str):
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
    servidor_tcp.inicia()
    
    
    #servidor_udp = ServidorUDP('127.0.0.1', porta_udp)

if __name__ == "__main__":
    main()