import sys
import socket

class Servidor:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def iniciar(self):
        pass

    def aceitar_conexao(self):
        pass

    def encerrar(self):
        self.socket.close()

class ServidorTCP(Servidor):
    def iniciar(self):
        self.socket.bind((self.host, self.port))
        self.socket.listen(5)
        print(f"Servidor TCP rodando na porta {self.port}")

        log = Log("servidor_log.txt")
        usuarios_conectados = Usuarios()  # Crie uma instância de usuários

    def aceitar_conexao(self):
        conn, addr = self.socket.accept()
        print(f"Conexão estabelecida com {addr}")
        # Implemente o tratamento dessa conexão aqui

class ServidorUDP(Servidor):
    def iniciar(self):
        self.socket.bind((self.host, self.port))
        print(f"Servidor UDP rodando na porta {self.port}")

    def receber_dados(self):
        data, addr = self.socket.recvfrom(1024)
        print(f"Dados recebidos de {addr}: {data.decode('utf-8')}")
        # Implemente o tratamento dos dados UDP aqui

class Log:
    def __init__(self, arquivo):
        self.arquivo = arquivo

class Usuarios:
    def __init__(self):
        self.usuarios = {}

    def criar_usuario(self, username, senha):
        self.usuarios[username] = senha

    def verificar_autenticacao(self, username, senha):
        return username in self.usuarios and self.usuarios[username] == senha
        
def main():
    if len(sys.argv) == 3:
        porta_tcp = int(sys.argv[1])
        porta_udp = int(sys.argv[2])
    else:
        print("Nenhum argumento fornecido. Forneça as portas como argumentos, por exemplo: python servidor.py 8080 12345") 
        #temporario
        porta_tcp = 8080
        porta_udp = 12345
        #exit(1)

    servidor_tcp = ServidorTCP('127.0.0.1', porta_tcp)
    servidor_tcp.iniciar()
    try:
        while(True):
            servidor_tcp.aceitar_conexao()
    except:
        print("Servidor finalizado")
    
    #servidor_udp = ServidorUDP('127.0.0.1', porta_udp)

if __name__ == "__main__":
    main()
