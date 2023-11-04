import socket
import ssl
import sys

class Cliente:
    def __init__(self, host, port):
        self.IP = host
        self.PORT = port
        self.prompt = "> "
        self.exit_manual = [False]
    
    def conexao(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((self.IP, self.PORT))
        PORTA_SSL = int(s.recv(5).decode('utf-8'))

        if PORTA_SSL == '':
            print("Erro: Não foi possível obter a porta SSL do servidor.")
            return

        PORTA_SSL = int(PORTA_SSL)

        socket_background = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socket_background.connect((self.IP, PORTA_SSL))

        contexto = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)
        contexto.check_hostname = False
        contexto.verify_mode = ssl.CERT_NONE

        socket_ssl = contexto.wrap_socket(socket.socket(socket.AF_INET, socket.SOCK_STREAM), server_hostname=self.IP)
        socket_ssl.connect((self.IP, PORTA_SSL))

        self.enviar_comando_socket('OK', socket_ssl)

        thread_background = threading.Thread(target=self.servidor_background, args=(socket_background, s, socket_ssl, exit_manual))
        thread_background.start()

        while True:
            out = ''
            try:
                while not out:
                    out = input(self.prompt)
            except:
                self.exit_manual[0] = True
                socket_ssl.close()
                socket_background.close()
                break

            first = out.split()[0]

            try:
                if first == 'exemplo_comando':
                    print("Recebeu o comando")

            except Exception as e:
                print("Terminando o programa")
                break

    def servidor_background(self, backsocket, ss):
        while not self.manual_death[0]:
            try:
                data = backsocket.recv(1024)
                if not data:
                    break
                print(data.decode('utf-8'))
            except Exception as e:
                break

    def enviar_comando_socket(command: str, s: socket.socket):
        command = bytearray(command.encode())
        s.sendall(command)

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

        return resp, s, backsocket, ss

def main():
    if len(sys.argv) == 3:
        ip = sys.argv[1]
        porta = int(sys.argv[2])
    else:
        print("Nenhum argumento fornecido. Forneça as portas como argumentos, por exemplo: python client.py 127.0.0.1 8080") 
        #temporario
        ip = '127.0.0.1'
        porta = 8080
        #exit(1)
    
    cliente = Cliente(ip, porta)
    cliente.conexao()
    
if __name__ == "__main__":
    main()
