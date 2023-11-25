import sys
import socket
import threading
from typing import Tuple, List


'''
TO-DO
- servidor udp
- arquivo log
- servidor daemon, segundo plano invocado por &
- heartbeat
- latencia
- servidor cair, esperar 20s

- addr background
- testar jogo com cliente tcp e cliente udp
- udp e tcp devem estar em uma thread?

- video
- makefile
- leiame
'''


class ServidorTCP:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def inicia(self):
        print(f"[S] TCP: Servidor TCP rodando na porta {self.port} e no host {self.host}")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s_ouvinte:
            s_ouvinte.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s_ouvinte.bind((self.host, self.port))
            s_ouvinte.listen()
            try:
                while(True):                
                    print("[S] TCP: Esperando conexão com algum cliente")
                    s, addr = s_ouvinte.accept()
                    print(f"[S] TCP: Conexão estabelecida com {addr}")
                    
                    cliente = Cliente(s, addr, 'tcp')
                    clientes.append(cliente)
                    cliente.threads()
            except:
                print("[S] TCP: Servidor finalizado")
                status.reseta_status()
                exit(0)

class ServidorUDP:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def inicia(self):
        print(f"[S] UDP: Servidor UDP rodando na porta {self.port} e no host {self.host}")
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.bind((self.host, self.port))
            try:
                while True:
                    print("[S] UDP: Esperando conexão com algum cliente")
                    msg, addr = s.recvfrom(1024)
                    mensagem = msg.decode('utf-8')
                    if mensagem == "conectado":
                        print(f"[S] UDP: Conexão estabelecida com {addr}: {mensagem}")
                    
                    cliente = Cliente(s, addr, 'udp')
                    #clientes.append(cliente)
                    #cliente.threads()
            except:
                print("[S] UDP: Servidor finalizado")
                status.reseta_status()
                exit(0)

class Cliente:
    def __init__(self, socket: socket.socket, addr, protocolo):
        self.s = socket
        self.addr = addr

        self.logado = False
        self.usuario = None

        self.caixa_de_entrada = None
        self.desafiado = False
        self.desafiando = None
        self.desafiante_addr = None

        if protocolo == "tcp":
            s_ouvinte, porta = cria_socket_ouvinte()
            envia_comando_ao_socket(self.s, porta)
            print(f"[T] porta servidor: {porta}")

            self.ss, addr_background = s_ouvinte.accept()
            resposta = self.ss.recv(1024).decode('utf-8')
            envia_comando_ao_socket(self.ss, "ok")
            
            print(f"[S] Recebeu resposta do cliente: {resposta}")

            #"ok" caso nova conexão
            if resposta == "ok":
                print(f"[S] Cliente {addr} conectou")
        
        elif protocolo == "udp":
            print("[T] teste")
            msg, addr = self.s.recvfrom(1024)
            resposta = msg.decode('utf-8')
            print("[T] teste 2")
            print(f"[S] Recebeu resposta do cliente: {resposta}")

            #"ok" caso nova conexão
            if resposta == "ok":
                print(f"[S] Cliente {addr} conectou")


    def reseta_cliente(self):
        self.logado = False
        self.caixa_de_entrada = None
        self.desafiado = False
        self.desafiando = None
        self.desafiante_addr = None
        self.reseta_jogo()
        status.sai_usuario(self.usuario)
        print("[T] Cliente resetado com sucesso")

    def reseta_jogo(self):
        self.caixa_de_entrada = None
        self.desafiado = False
        self.desafiando = None
        self.desafiante_addr = None
        status.altera_status(self.usuario, self.addr, 'Disponível')

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
                    self.reseta_cliente()
                    break

                comando = comando.split()

                if len(comando) > 0 and comando[0] == 'caixadeentrada':
                    if self.caixa_de_entrada is not None and not self.desafiado:
                        envia_comando_ao_socket(s, f"{self.caixa_de_entrada}")
                        self.desafiado = True
                        print("[T] Leu desafio da caixa de entrada")
                    else:
                        envia_comando_ao_socket(s, "0")

    def envia_desafio(self, oponente):
        print("[T] Encontrando oponente...")
        for cliente in clientes:
            if cliente.usuario == oponente:
                print(f"[T] {self.usuario} achou oponente {oponente} na lista de clientes.")
                if cliente.caixa_de_entrada == None:
                    prompt = "Pac-Man> "
                    cliente.desafiante_addr = self.addr
                    cliente.caixa_de_entrada = f"\nDesafio: {self.usuario} {cliente.desafiante_addr} te desafiou  e irá entrar na partida como um fantasma!\n{prompt}"    
                    print("[T] desafio foi enviado para a caixa de entrada!")
                    return 1
                else: 
                    print("[T] caixa de entrada cheia!")
                    return 0

    def interpretador(self):
        with self.ss as ss:
            while True:
                comando = ''
                try:
                    comando = ss.recv(1024).decode('utf-8')
                except:
                    print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    envia_comando_ao_socket(ss, 'tchau')
                    self.reseta_cliente()
                    break

                comando = comando.split()

                if not comando or comando[0] == 'tchau':
                    print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    envia_comando_ao_socket(ss, 'tchau')
                    self.reseta_cliente() 
                    break

                elif comando[0] == 'caixadeentrada':
                    if self.caixa_de_entrada != None:
                        envia_comando_ao_socket(ss, f"[S] {self.caixa_de_entrada}")
                    else: envia_comando_ao_socket(ss, "0")

                elif comando[0] == 'pontuacao':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    envia_comando_ao_socket(ss, f"Você ganhou {comando[1]} pontos! Pontuação total: {classificacao.obtem_pontuacao(self.usuario)} pontos.")
                    classificacao.atualiza_pontuacao(self.usuario, comando[1])
                    
                    # caso o jogador 2 saia no meio da partida, o jogador 1 não está mais sendo desafiado
                    for cliente in clientes:
                        if cliente.usuario == self.desafiando:
                            cliente.caixa_de_entrada = None
                            cliente.desafiado = False

                    self.reseta_jogo()

                elif comando[0] == 'l':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    lista = status.lista_status()
                    envia_comando_ao_socket(ss, lista)

                elif comando[0] == 'lideres':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    lideres = classificacao.lista_classificacao()
                    envia_comando_ao_socket(ss, lideres)

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
                                classificacao.adiciona_usuario(usuario)
                                envia_comando_ao_socket(ss, "[S] Usuário criado com sucesso!")
                            else:
                                envia_comando_ao_socket(ss, "[S] Nome de usuário já existente.")

                        elif len(comando) == 2 or len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Erro: Número inválido de argumentos. Use: novo <usuario> <senha>")

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
                            envia_comando_ao_socket(ss, f"[S] Erro: Número inválido de argumentos. Use: entra <usuario> <senha>")
                    
                    else:
                        print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                        envia_comando_ao_socket(ss, "[S] Erro: Comando não reconhecido para cliente não logado")

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
                            envia_comando_ao_socket(ss, f"[S] Erro: Número inválido de argumentos. Use: entra <usuario> <senha>")

                    elif comando[0] == 'sai':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        self.reseta_cliente()
                        envia_comando_ao_socket(ss, f"[S] Usuário deslogado com sucesso!")

                    elif comando[0] == 'inicia':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        status.altera_status(self.usuario, self.addr, 'Jogando')
                        envia_comando_ao_socket(ss, f"[S] Jogo iniciado.")

                    elif comando[0] == 'desafio':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 2:
                            oponente = comando[1]

                            if oponente == self.usuario:
                                envia_comando_ao_socket(ss, f"[S] Erro: Você não pode se desafiar! Escolha um oponente válido. Use o comando <l> para encontrar os usuários disponíveis.")

                            elif status.verifica_status(oponente) == "Disponível":
                                envia_comando_ao_socket(ss, f"[S] Erro: O usuário {oponente} não está em uma partida neste momento!")

                            elif status.verifica_status(oponente) == "Não encontrado":
                                envia_comando_ao_socket(ss, f"[S] Erro: O usuário {oponente} não existe ou não está em uma partida.")    
                                
                            elif status.verifica_status(oponente) == "Jogando":
                                if self.envia_desafio(oponente) == 1:
                                    self.desafiando = oponente
                                    status.altera_status(self.usuario, self.addr, 'Jogando')
                                    envia_comando_ao_socket(ss, "[S] Desafio enviado.")
                                else: envia_comando_ao_socket(ss, f"[S] Erro: O jogador {oponente} já está sendo desafiado.")

                        elif len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Erro: Número inválido de argumentos. Use: desafio <oponente>")

                    elif comando[0] == 'desafiado':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        
                        jogo_porta = comando[1] #recebo a porta do jogo do desafiado
                        mensagem = f"Conexão: desafiante {jogo_porta} {self.addr[0]}" #mandar para o desafiante

                        for cliente in clientes:
                            if cliente.addr == self.desafiante_addr:
                                cliente.caixa_de_entrada = mensagem

                        envia_comando_ao_socket(ss, "ok") #manda ao desafiado que a porta foi enviada ao desafiante

                    else:
                        print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                        envia_comando_ao_socket(ss, "[S] Erro: Comando não reconhecido para cliente logado")

                else:
                    print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                    envia_comando_ao_socket(ss, "[S] Erro: Comando não reconhecido")

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

    def altera_status(self, usuario, addr, novo_status):
        alterou = False
        self.status_mutex.acquire()
        with open(self.status_arq, 'r') as f:
            linhas = f.readlines()
        with open(self.status_arq, 'w') as f:
            for l in linhas:
                linha = l.split(' ')
                if linha[0] == usuario:
                    f.write(f'{usuario} {addr} {novo_status}\n')
                    alterou = True
                else:
                    f.write(l)
        self.status_mutex.release()
        return alterou

    def reseta_status(self):
        self.status_mutex.acquire()
        with open(self.status_arq, 'w') as f:
            pass
        self.status_mutex.release()

class Classificacao:
    def __init__(self):
        self.classificacao_arq = 'classificacao.txt'
        self.classificacao_mutex = threading.Lock()
        with open(self.classificacao_arq, 'a') as f:
            pass

    def adiciona_usuario(self, usuario):
        self.classificacao_mutex.acquire()
        with open(self.classificacao_arq, 'a') as f:
            f.write(f'{usuario} 0\n')
        self.classificacao_mutex.release()

    def lista_classificacao(self):
        self.classificacao_mutex.acquire()
        lista = ""
        with open(self.classificacao_arq, 'r') as f:
            linhas = f.readlines()
            if not linhas:
                lista = "Lista de classificação vazia."
            else:
                linhas_ordenadas = sorted(linhas, key=lambda x: int(x.split()[1]), reverse=True)
                for l in linhas_ordenadas:
                    usuario, classificacao = l.split()
                    lista += f'Usuário: {usuario}, Pontuação: {classificacao}\n'
        self.classificacao_mutex.release()
        return lista

    def atualiza_pontuacao(self, usuario, pontos):
        self.classificacao_mutex.acquire()
        linhas = []
        with open(self.classificacao_arq, 'r') as f:
            linhas = f.readlines()
        for i, linha in enumerate(linhas):
            u, pontuacao = linha.split()
            if u == usuario:
                pontuacao_atual = int(pontuacao)
                pontos_int = int(pontos)
                nova_pontuacao = pontuacao_atual + pontos_int
                linhas[i] = f'{usuario} {nova_pontuacao}\n'
                break
        with open(self.classificacao_arq, 'w') as f:
            f.writelines(linhas)
        self.classificacao_mutex.release()

    def obtem_pontuacao(self, usuario):
        self.classificacao_mutex.acquire()
        pontuacao = None
        with open(self.classificacao_arq, 'r') as f:
            linhas = f.readlines()
            for linha in linhas:
                u, pontos = linha.split()
                if u == usuario:
                    pontuacao = int(pontos)
                    break
        self.classificacao_mutex.release()
        return pontuacao

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
classificacao = Classificacao()
    
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

    print(f"[S] Servidor irá rodar na porta {porta_tcp} do UDP.")

    servidor_tcp = ServidorTCP('', porta_tcp)
    servidor_tcp.inicia()

    #servidor_udp = ServidorUDP('', porta_tcp)
    #servidor_udp.inicia()
    
    #servidor_udp = ServidorUDP('127.0.0.1', porta_udp)

if __name__ == "__main__":
    main()