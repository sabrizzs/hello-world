import socket
import ssl
import sys
import threading

class Cliente:
    def __init__(self, host, port):
        self.IP = host
        self.PORT = port
        self.prompt = "Pac-Man > "
        
        self.exit_manual = [False]
    
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

            send_command_to_socket('ok ', ss)
            
            back_thread = threading.Thread(target=background_server_listener, args=(backsocket, s, ss, self.exit_manual))
            back_thread.start()

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

                command = out.split()[0]
                try:
                    if command == 'teste':
                        print("[S] Cliente mandou teste")
                except:
                    print("[S] Terminando o programa")
                    break

def background_server_listener(backsocket: socket.socket, normal_socket: socket.socket, ssl_socket: ssl.SSLSocket, exit_manual):
    print("[T] Ainda não implementado: background_server_listener")

def send_command_to_socket(command: str, s: socket.socket):
    command = bytearray(command.encode())
    s.sendall(command)

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
