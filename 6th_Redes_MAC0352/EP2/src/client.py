import socket
import ssl
import sys
import threading

'''
TO-DO:
- retirar server.key e server.pem
'''

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

            send_command_to_socket('ok', ss)
            
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
                        resp = try_to_send_command(out, ss, s, backsocket, ss)                      
                        if not resp:
                            print(f"[C] Servidor não respondeu ao comando {command}")
                        else: print(f"[C] Comando: {command}; Retornou: {resp}")
                    else:
                        resp = try_to_send_command(out, ss, s, backsocket, ss)                      
                        if not resp:
                            print(f"[C] Servidor não respondeu ao comando {command}")
                        else: print(f"[C] {resp}")
                except:
                    print("[C] Terminando o programa")
                    break

def background_server_listener(backsocket: socket.socket, normal_socket: socket.socket, ssl_socket: ssl.SSLSocket, exit_manual):
    print("[T] Ainda não implementado: background_server_listener")

def send_command_to_socket(command: str, s: socket.socket):
    command = bytearray(command.encode())
    s.sendall(command)

def receive_string_from_socket(s: socket.socket):
    return s.recv(1024).decode('utf-8')

def update_sockets():
    global reconnected

    mutex_reconnected.acquire()
    r = reconnected
    mutex_reconnected.release()
    while r == 0:
        time.sleep(1)
        mutex_reconnected.acquire()
        r = reconnected
        mutex_reconnected.release()

    mutex_reconnected.acquire()
    reconnected = 0
    mutex_reconnected.release()

    if r == 1:
        return 1, s_g[0], backsocket_g[0], ss_g[0]
    else:
        return 0, None, None, None

def try_to_send_command(command: str, used_socket: socket.socket, s: socket.socket, backsocket: socket.socket, ss: ssl.SSLSocket):
    send_command_to_socket(command, used_socket)
    resp = receive_string_from_socket(used_socket)

    while resp == '':
        #Conexão fechada
        success, s, backsocket, ss = update_sockets()
        if not success:
            break
        send_command_to_socket(command, s)
        resp = receive_string_from_socket(s)

    return resp

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
