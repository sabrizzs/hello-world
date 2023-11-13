import sys
import socket
import threading
from typing import Tuple, List

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
                    clientes.append(cliente)
                    cliente.threads()
            except:
                print("[S] Servidor finalizado")
                exit(0)

class Cliente:
    def __init__(self, socket: socket.socket, addr):
        self.logado = False
        self.usuario = None

        self.caixa_de_entrada = None
        self.desafiado = False
        self.desafiando = False

        self.s = socket
        self.addr = addr

        s_ouvinte, port = cria_socket_ouvinte()
        envia_comando_ao_socket(self.s, port)
        print(f"[T] port servidor: {port}")

        self.ss, addr_background = s_ouvinte.accept()
        resposta = self.ss.recv(1024).decode('utf-8')
        envia_comando_ao_socket(self.ss, "ok")
        
        print(f"[S] Recebeu resposta do cliente: {resposta}")

        #"ok" caso nova conexão
        if resposta == "ok":
            print(f"[S] Cliente {addr} conectou")

    def threads(self):
        thread = threading.Thread(target=self.interpretador, args=())
        thread.start()
        caixa_de_entrada = threading.Thread(target=self.interpretador_caixa_de_entrada, args=())
        caixa_de_entrada.start()

    def interpretador_caixa_de_entrada(self):
        with self.s as s:
            while True:
                comando = ''
                try:
                    comando = s.recv(1024).decode('utf-8')
                except:
                    print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    self.logado = False
                    status.sai_usuario(self.usuario)
                    break

                comando = comando.split()

                if len(comando) > 0 and comando[0] == 'caixadeentrada':
                    if self.caixa_de_entrada is not None and not self.desafiado:
                        envia_comando_ao_socket(s, f"{self.caixa_de_entrada}")
                        self.desafiado = True
                    else: envia_comando_ao_socket(s, "0")

    def envia_desafio(self, oponente):
        print("[T] Encontrando oponente...")
        for cliente in clientes:
            if cliente.usuario == oponente:
                print(f"[T] {self.usuario} achou oponente {oponente} na lista de clientes.")
                if cliente.caixa_de_entrada == None:
                    prompt = "Pac-Man> "
                    cliente.caixa_de_entrada = f"\nDesafio: {self.usuario} te desafiou!\n{prompt}"
                    return 1
                else: return 0

    def interpretador(self):
        with self.ss as ss:
            while True:
                comando = ''
                try:
                    comando = ss.recv(1024).decode('utf-8')
                except:
                    print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    self.logado = False
                    status.sai_usuario(self.usuario)
                    break

                comando = comando.split()

                if not comando or comando[0] == 'exit':
                    print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    self.logado = False
                    status.sai_usuario(self.usuario)
                    break

                elif comando[0] == 'caixadeentrada':
                    if self.caixa_de_entrada != None:
                        envia_comando_ao_socket(ss, f"[S] {self.caixa_de_entrada}")
                    else: envia_comando_ao_socket(ss, "0")

                elif comando[0] == 'exit':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    self.logado = False
                    status.sai_usuario(self.usuario)
                    envia_comando_ao_socket(ss, f"[S] Usuário deslogado com sucesso!")

                elif comando[0] == 'l':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    lista = status.lista_status()
                    envia_comando_ao_socket(ss, lista)

                elif not self.logado:

                    if comando[0] == 'teste':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        envia_comando_ao_socket(ss, f"[S] Cliente <não logado> enviou: {comando}")
                    
                    elif comando[0] == 'novo':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 3:
                            usuario = comando[1]
                            senha = comando[2]

                            if usuarios.novo_usuario(usuario, senha):
                                envia_comando_ao_socket(ss, "[S] Usuário criado com sucesso!")
                            else:
                                envia_comando_ao_socket(ss, "[S] Nome de usuário já existente.")

                        elif len(comando) == 2 or len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Número inválido de argumentos. Use: novo <usuario> <senha>")

                    elif comando[0] == 'entra':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 3:
                            usuario = comando[1]
                            senha = comando[2]

                            if usuarios.entra_usuario(usuario, senha):
                                self.logado = True
                                self.usuario = usuario
                                status.entra_usuario(usuario, self.addr)
                                envia_comando_ao_socket(ss, "[S] Usuário logado com sucesso!")
                            else:
                                envia_comando_ao_socket(ss, "[S] Usuário e senha não encontrados.")

                        elif len(comando) == 2 or len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Número inválido de argumentos. Use: entra <usuario> <senha>")

                    else:
                        print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                        envia_comando_ao_socket(ss, "[S] Comando não reconhecido para cliente não logado")

                elif self.logado:

                    if comando[0] == 'teste':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        envia_comando_ao_socket(ss, f"[S] Cliente <logado> enviou: {comando}")

                    elif comando[0] == 'senha':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 3:
                            senha_antiga = comando[1]
                            senha_nova = comando[2]

                            if usuarios.altera_senha(senha_antiga, senha_nova, self.usuario):
                                envia_comando_ao_socket(ss, "[S] Senha alterada com sucesso!")
                            else:
                                envia_comando_ao_socket(ss, "[S] Não foi possível alterar a senha.")

                        elif len(comando) == 2 or len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Número inválido de argumentos. Use: entra <usuario> <senha>")

                    elif comando[0] == 'sai':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        self.logado = False
                        status.sai_usuario(self.usuario)
                        envia_comando_ao_socket(ss, f"[S] Usuário deslogado com sucesso!")

                    elif comando[0] == 'inicia':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        
                        envia_comando_ao_socket(ss, f"[S] Usuário mandou <inicia>.")

                    elif comando[0] == 'desafio':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 2:
                            oponente = comando[1]

                            if oponente == self.usuario:
                                envia_comando_ao_socket(ss, f"[S] Você não pode se desafiar! Escolha um oponente válido. Use o comando <l> para encontrar os usuários disponíveis.")

                            elif status.verifica_status(oponente) == "Jogando":
                                envia_comando_ao_socket(ss, f"[S] O usuário {oponente} está em uma partida neste momento!")

                            elif status.verifica_status(oponente) == "Não encontrado":
                                envia_comando_ao_socket(ss, f"[S] O usuário {oponente} não existe ou não está online.")    
                                
                            elif status.verifica_status(oponente) == "Disponível":
                                if self.envia_desafio(oponente) == 1:
                                    self.desafiando = True
                                    envia_comando_ao_socket(ss, "[S] Desafio enviado.")
                                else: envia_comando_ao_socket(ss, f"[S] O jogador {oponente} já está sendo desafiado.")

                        elif len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Número inválido de argumentos. Use: desafio <oponente>")

                    else:
                        print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                        envia_comando_ao_socket(ss, "[S] Comando não reconhecido para cliente logado")

                else:
                    print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                    envia_comando_ao_socket(ss, "[S] Comando não reconhecido")

class Usuarios:
    def __init__(self):
        self.usuarios_arq = 'usuarios.txt'
        self.usuarios_mutex = threading.Lock()
        with open(self.usuarios_arq, 'a') as f:
            pass

    def novo_usuario(self, usuario, senha):
        self.usuarios_mutex.acquire()
        with open(self.usuarios_arq, 'r') as f:
           linhas = f.readlines()
           for l in linhas:
               nome = l.split(' ')[0]
               if nome == usuario:
                   self.usuarios_mutex.release()
                   return False

        with open(self.usuarios_arq, 'a') as f:
            f.write(f'{usuario} {senha}\n')
        
        return True

    def altera_senha(self, senha_antiga, senha_nova, u):
        alterou = False
        self.usuarios_mutex.acquire()

        with open(self.usuarios_arq, 'r') as f:
            linhas = f.readlines()
        with open(self.usuarios_arq, 'w') as f:
            for l in linhas:
                conta = l.split(' ')
                usuario = conta[0]
                senha = conta[1]
                if usuario == u and senha[:-1] == senha_antiga:
                    l = f'{usuario} {senha_nova}\n'
                    alterou = True
                f.write(l)

        self.usuarios_mutex.release()
        return alterou

    def entra_usuario(self, u, s):
        with open(self.usuarios_arq, 'r') as f:
            linhas = f.readlines()
            for l in linhas:
                l = l.split(' ')
                usuario = l[0]
                senha = l[1]
                if usuario == u and senha[:-1] == s:
                    return True
        return False

class Status:
    def __init__(self):
        self.status_arq = 'status.txt'
        self.status_mutex = threading.Lock()
        with open(self.status_arq, 'a') as f:
            pass
    
    def entra_usuario(self, usuario, addr):
        self.status_mutex.acquire()
        status = 'Disponível'
        with open(self.status_arq, 'r') as f:
           linhas = f.readlines()
        with open(self.status_arq, 'a') as f:
            f.write(f'{usuario} {addr} {status}\n')
        self.status_mutex.release()

    def sai_usuario(self, u):
        self.status_mutex.acquire()
        with open(self.status_arq, 'r') as f:
            linhas = f.readlines()
        with open(self.status_arq, 'w') as f:
            for l in linhas:
                linha = l.split(' ')
                usuario = linha[0]
                if usuario != u:
                    f.write(l)
        self.status_mutex.release()

    def lista_status(self):
        self.status_mutex.acquire()
        lista = ""
        with open(self.status_arq, 'r') as f:
            linhas = f.readlines()
            if not linhas:
                lista = "Lista de status vazia."
            else:
                for l in linhas:
                    linha = l.split(' ')
                    usuario = linha[0]
                    status = linha[3]
                    lista += f'Usuário: {usuario}, Status: {status[:-1]}\n'
        self.status_mutex.release()
        return lista
    
    def verifica_status(self, usuario):
        self.status_mutex.acquire()
        with open(self.status_arq, 'r') as f:
            linhas = f.readlines()
            for l in linhas:
                linha = l.split(' ')
                if linha[0] == usuario:
                    status = linha[3]
                    self.status_mutex.release()
                    return status[:-1]
        self.status_mutex.release()
        return f'Não encontrado'

def cria_socket_ouvinte() -> Tuple[socket.socket, str]:
    s_ouvinte = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_ouvinte.bind(('', 0))
    s_ouvinte.listen(5)
    _, port1 = s_ouvinte.getsockname()
    str_port1 = '%05d' % port1
    return s_ouvinte, str_port1

def envia_comando_ao_socket(s: socket.socket, msg: str):
    s.sendall(bytearray(msg.encode()))

usuarios = Usuarios()
status =  Status()
clientes = list()
    
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