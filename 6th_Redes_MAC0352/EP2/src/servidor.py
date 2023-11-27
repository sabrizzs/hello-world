import sys
import socket
import threading
import os
from typing import Tuple, List
from datetime import datetime


'''
TO-DO
- servidor udp
- servidor daemon, segundo plano invocado por &

- heartbeat
- latencia
- servidor cair, esperar 20s

- testar jogo com cliente tcp e cliente udp

- video
- makefile
- leiame
'''


class ServidorTCP:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def inicia(self):
        #print(f"[S] TCP: Servidor TCP rodando na porta {self.port} e no host {self.host}")
        log.servidor_iniciado('TCP', True, False)

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s_ouvinte:
            s_ouvinte.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s_ouvinte.bind((self.host, self.port))
            s_ouvinte.listen()
            try:
                while(True):                
                    #print("[T] TCP: Esperando conexão com algum cliente")
                    s, addr = s_ouvinte.accept()
                    #print(f"[S] TCP: Conexão estabelecida com {addr}")
                    log.conexao_cliente(addr[0], 'tcp')
            
                    cliente = Cliente(s, addr, 'tcp')
                    clientes.append(cliente)
                    cliente.threads()
            except:
                #print("[S] TCP: Servidor finalizado")
                log.servidor_finalizado()
                status.reseta_status()
                exit(0)

class ServidorUDP:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def inicia(self):
        #print(f"[S] UDP: Servidor UDP rodando na porta {self.port} e no host {self.host}")
        log.servidor_iniciado('UDP', True, False)

        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.bind((self.host, self.port))

            #PAREI EM CLIENTE THREADS
            try:
                while True:
                    #print("[T] UDP: Esperando conexão com algum cliente")
                    msg, addr = s.recvfrom(1024)
                    mensagem = msg.decode('utf-8')
                    if mensagem == "conectado":
                        #print(f"[S] UDP: Conexão estabelecida com {addr}: {mensagem}")
                        log.conexao_cliente(addr[0], 'udp')
                    
                    cliente = Cliente(s, addr, 'udp')
                    clientes.append(cliente)
                    cliente.threads()
            except:
                #print("[S] UDP: Servidor finalizado")
                log.servidor_finalizado()
                status.reseta_status()
                exit(0)

class Cliente:
    def __init__(self, s: socket.socket, addr, protocolo):
        self.s = s
        self.protocolo = protocolo
        self.addr = addr
        self.s_porta = addr[1]
        self.ss_porta = None

        self.logado = False
        self.usuario = None

        self.caixa_de_entrada = None
        self.desafiado = False
        self.desafiando = None
        self.desafiante_addr = None

        if protocolo == "tcp":
            s_ouvinte, porta = cria_socket_ouvinte()
            envia_comando_ao_socket(self.s, porta, self.protocolo, None)

            self.ss, addr_ouvinte = s_ouvinte.accept()
            resposta = self.ss.recv(1024).decode('utf-8')
            envia_comando_ao_socket(self.ss, "ok", self.protocolo, None)
            
            #print(f"[T] TCP: Recebeu resposta do cliente: {resposta}")

            if resposta == "ok":
                print(f"[S] TCP: Cliente {addr} conectou")
        
        elif protocolo == "udp":
            self.ss = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.ss.bind(('', 0))
            self.ss_porta = str(self.ss.getsockname()[1]).encode('utf-8')
            self.s.sendto(self.ss_porta, self.addr)

            self.ss_porta = int(self.ss_porta.decode('utf-8'))
            #print(f"[T] UDP: porta ss_porta servidor: {self.ss_porta}") #envia porta
            #print(f"[T] UDP: porta s_porta servidor: {self.s_porta}")

            msg, addr = self.ss.recvfrom(1024)
            resposta = msg.decode('utf-8')
            #print(f"[S] UDP: Recebeu resposta do cliente: {resposta}")

            if resposta == "ok":
                print(f"[S] UDP: Cliente {addr} conectou")


    def reseta_cliente(self):
        self.logado = False
        self.caixa_de_entrada = None
        self.desafiado = False
        self.desafiando = None
        self.desafiante_addr = None
        self.reseta_jogo()
        status.sai_usuario(self.usuario)
        log.desconexao_cliente(self.addr[0], self.protocolo)
        #print("[T] Cliente resetado com sucesso")

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
                    #print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    self.reseta_cliente()
                    break

                comando = comando.split()

                if len(comando) > 0 and comando[0] == 'caixadeentrada':
                    if self.caixa_de_entrada is not None and not self.desafiado:
                        envia_comando_ao_socket(s, f"{self.caixa_de_entrada}", self.protocolo, self.s_porta)
                        self.desafiado = True
                    else:
                        envia_comando_ao_socket(s, "0", self.protocolo, self.s_porta)
                    
    def envia_desafio(self, oponente):
        #print("[T] Encontrando oponente...")
        for cliente in clientes:
            if cliente.usuario == oponente:
                #print(f"[T] {self.usuario} achou oponente {oponente} na lista de clientes.")
                if cliente.caixa_de_entrada == None:
                    prompt = "Pac-Man> "
                    cliente.desafiante_addr = self.addr
                    cliente.caixa_de_entrada = f"\nDesafio: {self.usuario} {cliente.desafiante_addr} te desafiou  e irá entrar na partida como um fantasma!\n{prompt}"
                    return 1
                else: 
                    return 0

    def interpretador(self):
        with self.ss as ss:
            while True:
                comando = ''
                try:
                    if self.protocolo == "tcp":
                        comando = self.ss.recv(1024).decode('utf-8')
                    elif self.protocolo == "udp":
                        comando, _ = self.ss.recvfrom(1024)
                        comando = comando.decode('utf-8')
                except:
                    #print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    envia_comando_ao_socket(ss, 'tchau', self.protocolo, self.ss_porta)
                    self.reseta_cliente()
                    break

                comando = comando.split()

                if not comando or comando[0] == 'tchau':
                    #print(f'[S] Cliente {self.addr} encerrou a conexão. Desconectando...')
                    envia_comando_ao_socket(ss, 'tchau', self.protocolo, self.ss_porta)
                    self.reseta_cliente() 
                    break

                elif comando[0] == 'caixadeentrada':
                    if self.caixa_de_entrada != None:
                        envia_comando_ao_socket(ss, f"[S] {self.caixa_de_entrada}", self.protocolo, self.s_porta)
                    else: envia_comando_ao_socket(ss, "0", self.protocolo, self.s_porta)

                elif comando[0] == 'pontuacao':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    envia_comando_ao_socket(ss, f"Você ganhou {comando[2]} pontos! Pontuação total: {classificacao.obtem_pontuacao(self.usuario)} pontos.", self.protocolo, self.ss_porta)
                    classificacao.atualiza_pontuacao(self.usuario, comando[2])

                    vitoria = False
                    if comando[1] == 'vitoria': vitoria = True
                    
                    if self.desafiado == False:
                        enderecos_ip = [self.addr[0]]
                        nomes_usuarios = [self.usuario]
                        vencedor = f"{self.usuario} de Pac-Man" if vitoria else "Fantasma"
                        log.finalizacao_partida(enderecos_ip, nomes_usuarios, vencedor)

                    # caso o jogador 2 saia no meio da partida, o jogador 1 não está mais sendo desafiado
                    for cliente in clientes:
                        if cliente.usuario == self.desafiando:
                            cliente.caixa_de_entrada = None
                            cliente.desafiado = False
                            log.entrada_saida_fantasma(self.addr[0], self.usuario, False)

                            enderecos_ip = [cliente.addr[0], self.addr[0]]
                            nomes_usuarios = [cliente.usuario, self.usuario]
                            vencedor = f"{self.usuario} de Fantasma" if vitoria else f"{cliente.usuario} de Pac-Man"
                            log.finalizacao_partida(enderecos_ip, nomes_usuarios, vencedor)

                    self.reseta_jogo()

                elif comando[0] == 'l':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    lista = status.lista_status()
                    envia_comando_ao_socket(ss, lista, self.protocolo, self.ss_porta)

                elif comando[0] == 'lideres':
                    print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                    lideres = classificacao.lista_classificacao()
                    envia_comando_ao_socket(ss, lideres, self.protocolo, self.ss_porta)

                elif not self.logado:

                    if comando[0] == 'teste':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        envia_comando_ao_socket(ss, f"[S] Cliente <não logado> enviou: {comando}", self.protocolo, self.ss_porta)
                    
                    elif comando[0] == 'novo':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 3:
                            usuario = comando[1]
                            senha = comando[2]

                            if usuarios.novo_usuario(usuario, senha):
                                classificacao.adiciona_usuario(usuario)
                                envia_comando_ao_socket(ss, "[S] Usuário criado com sucesso!", self.protocolo, self.ss_porta)
                            else:
                                envia_comando_ao_socket(ss, "[S] Nome de usuário já existente.", self.protocolo, self.ss_porta)

                        elif len(comando) == 2 or len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Erro: Número inválido de argumentos. Use: novo <usuario> <senha>", self.protocolo, self.ss_porta)

                    elif comando[0] == 'entra':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 3:
                            usuario = comando[1]
                            senha = comando[2]

                            if usuarios.entra_usuario(usuario, senha):
                                self.logado = True
                                self.usuario = usuario
                                status.entra_usuario(usuario, self.addr)
                                envia_comando_ao_socket(ss, "[S] Usuário logado com sucesso!", self.protocolo, self.ss_porta)
                                log.login(self.usuario, self.addr[0], True)
                            else:
                                envia_comando_ao_socket(ss, "[S] Usuário e senha não encontrados.", self.protocolo, self.ss_porta)
                                log.login(self.usuario, self.addr[0], False)

                        elif len(comando) == 2 or len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Erro: Número inválido de argumentos. Use: entra <usuario> <senha>", self.protocolo, self.ss_porta)
                    
                    else:
                        print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                        envia_comando_ao_socket(ss, "[S] Erro: Comando não reconhecido para cliente não logado", self.protocolo, self.ss_porta)

                elif self.logado:

                    if comando[0] == 'teste':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        envia_comando_ao_socket(ss, f"[S] Cliente <logado> enviou: {comando}", self.protocolo, self.ss_porta)

                    elif comando[0] == 'senha':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 3:
                            senha_antiga = comando[1]
                            senha_nova = comando[2]

                            if usuarios.altera_senha(senha_antiga, senha_nova, self.usuario):
                                envia_comando_ao_socket(ss, "[S] Senha alterada com sucesso!", self.protocolo, self.ss_porta)
                            else:
                                envia_comando_ao_socket(ss, "[S] Não foi possível alterar a senha.", self.protocolo, self.ss_porta)

                        elif len(comando) == 2 or len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Erro: Número inválido de argumentos. Use: entra <usuario> <senha>", self.protocolo, self.ss_porta)

                    elif comando[0] == 'sai':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        self.reseta_cliente()
                        envia_comando_ao_socket(ss, f"[S] Usuário deslogado com sucesso!", self.protocolo, self.ss_porta)

                    elif comando[0] == 'inicia':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        status.altera_status(self.usuario, self.addr, 'Jogando')
                        envia_comando_ao_socket(ss, f"[S] Jogo iniciado.", self.protocolo, self.ss_porta)
                        log.inicio_partida(self.addr[0], self.usuario)

                    elif comando[0] == 'desafio':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        if len(comando) == 2:
                            oponente = comando[1]

                            if oponente == self.usuario:
                                envia_comando_ao_socket(ss, f"[S] Erro: Você não pode se desafiar! Escolha um oponente válido. Use o comando <l> para encontrar os usuários disponíveis.", self.protocolo, self.ss_porta)

                            elif status.verifica_status(oponente) == "Disponível":
                                envia_comando_ao_socket(ss, f"[S] Erro: O usuário {oponente} não está em uma partida neste momento!", self.protocolo, self.ss_porta)

                            elif status.verifica_status(oponente) == "Não encontrado":
                                envia_comando_ao_socket(ss, f"[S] Erro: O usuário {oponente} não existe ou não está em uma partida.", self.protocolo, self.ss_porta)
                                
                            elif status.verifica_status(oponente) == "Jogando":
                                if self.envia_desafio(oponente) == 1:
                                    self.desafiando = oponente
                                    status.altera_status(self.usuario, self.addr, 'Jogando')
                                    envia_comando_ao_socket(ss, "[S] Desafio enviado.", self.protocolo, self.ss_porta)
                                    log.entrada_saida_fantasma(self.addr[0], self.usuario, True)
                                else: envia_comando_ao_socket(ss, f"[S] Erro: O jogador {oponente} já está sendo desafiado.", self.protocolo, self.ss_porta)

                        elif len(comando) == 1:
                            print(f"[S] Cliente {self.addr} mandou um comando com número inválido de argumentos: {comando}")
                            envia_comando_ao_socket(ss, f"[S] Erro: Número inválido de argumentos. Use: desafio <oponente>", self.protocolo, self.ss_porta)

                    elif comando[0] == 'desafiado':
                        print(f"[S] Cliente {self.addr} mandou: {comando[0]}")
                        
                        jogo_porta = comando[1] 
                        mensagem = f"Conexão: desafiante {jogo_porta} {self.addr[0]}" #mandar para o desafiante

                        for cliente in clientes:
                            if cliente.addr == self.desafiante_addr:
                                cliente.caixa_de_entrada = mensagem

                        envia_comando_ao_socket(ss, "ok", self.protocolo, self.ss_porta) #manda ao desafiado que a porta foi enviada ao desafiante

                    else:
                        print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                        envia_comando_ao_socket(ss, "[S] Erro: Comando não reconhecido para cliente logado", self.protocolo, self.ss_porta)

                else:
                    print(f"[S] Cliente {self.addr} mandou um comando desconhecido: {comando[0]}")
                    envia_comando_ao_socket(ss, "[S] Erro: Comando não reconhecido", self.protocolo, self.ss_porta)

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

class Log:
    def __init__(self):
        self.log_arq = 'log.txt'
        self.log_mutex = threading.Lock()
        with open(self.log_arq, 'a') as f:
            pass

    def servidor_iniciado(self, protocolo, sucesso, partida_em_execucao):
        self.log_mutex.acquire()
        with open(self.log_arq, 'a') as f:
            tempo = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            status_execucao = "com sucesso" if sucesso else "com falha"
            if not sucesso and partida_em_execucao:
                f.write(f"[{tempo}] Servidor {protocolo} iniciado {status_execucao}. Retomando controle da partida em execução.\n")
            else:
                f.write(f"[{tempo}] Servidor {protocolo} iniciado {status_execucao}.\n")
        self.log_mutex.release()
        # falta heartbeats

    def conexao_cliente(self, endereco_ip, protocolo):
        self.log_mutex.acquire()
        with open(self.log_arq, 'a') as f:
            tempo = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            f.write(f"[{tempo}] Conexão realizada por um cliente ({'UDP' if protocolo == 'udp' else 'TCP'}). Endereço IP: {endereco_ip}\n")
        self.log_mutex.release()

    def login(self, usuario, endereco_ip, sucesso):
        self.log_mutex.acquire()
        with open(self.log_arq, 'a') as f:
            tempo = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            status_login = "com sucesso" if sucesso else "sem sucesso"
            f.write(f"[{tempo}] Login de usuário: {usuario}. Endereço IP: {endereco_ip}. Status: {status_login}\n")
        self.log_mutex.release()

    def desconexao_cliente(self, endereco_ip, protocolo):
        self.log_mutex.acquire()
        with open(self.log_arq, 'a') as f:
            tempo = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            f.write(f"[{tempo}] Desconexão realizada por um cliente ({'UDP' if protocolo == 'udp' else 'TCP'}). Endereço IP: {endereco_ip}\n")
        self.log_mutex.release()

    def inicio_partida(self, endereco_ip, usuario):
        self.log_mutex.acquire()
        with open(self.log_arq, 'a') as f:
            tempo = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            f.write(f"[{tempo}] Início de uma partida. Endereço IP: {endereco_ip}, Nome do Usuário: {usuario}\n")
        self.log_mutex.release()

    def entrada_saida_fantasma(self, endereco_ip, usuario, entrada):
        self.log_mutex.acquire()
        with open(self.log_arq, 'a') as f:
            tempo = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            acao = "Entrada" if entrada else "Saída"
            f.write(f"[{tempo}] {acao} de um fantasma da partida existente. Endereço IP: {endereco_ip}, Nome do Usuário: {usuario}\n")
        self.log_mutex.release()

    def finalizacao_partida(self, enderecos_ip, nomes_usuarios, vencedor):
        self.log_mutex.acquire()
        with open(self.log_arq, 'a') as f:
            tempo = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            enderecos_ip_str = ', '.join(enderecos_ip)
            nomes_usuarios_str = ', '.join(nomes_usuarios)
            f.write(f"[{tempo}] Finalização de uma partida. Endereços IP: {enderecos_ip_str}, Nomes dos Usuários: {nomes_usuarios_str}, Vencedor: {vencedor}\n")
        self.log_mutex.release()

    def desconexao_inesperada(self, endereco_ip):
        pass

    def servidor_finalizado(self):
        self.log_mutex.acquire()
        with open(self.log_file, 'a') as f:
            tempo = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            f.write(f"[{tempo}] Servidor finalizado.\n")
        self.log_mutex.release()


def cria_socket_ouvinte() -> Tuple[socket.socket, str]:
    s_ouvinte = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_ouvinte.bind(('', 0)) #sistema escolhe uma porta disponível
    s_ouvinte.listen(5)
    _, porta = s_ouvinte.getsockname()
    s_porta = '%05d' % porta
    return s_ouvinte, s_porta

def envia_comando_ao_socket(s: socket.socket, comando: str, protocolo, udp_porta):
    comando = bytearray(comando.encode())
    if protocolo == 'tcp':
        s.sendall(comando)
    elif protocolo == 'udp':
        s.sendto(comando, ('', udp_porta))

usuarios = Usuarios()
status =  Status()
clientes = list()
classificacao = Classificacao()
log = Log()
    
def main():
    if len(sys.argv) == 3:
        porta_tcp = int(sys.argv[1])
        porta_udp = int(sys.argv[2])
    else:
        print("[S] Nenhum argumento fornecido. Forneça as portas como argumentos, por exemplo: python servidor.py <porta TCP> <porta UDP>")
        '''print("[S] Rodando o servidor nas portas pré definidas tcp: 8080 e udp: 8081")
        porta_tcp = 8080
        porta_udp = 8080'''
        exit(1)

    print(f"[S] Servidor TCP irá rodar na porta {porta_tcp}.")
    servidor_tcp = ServidorTCP('', porta_tcp)
    thread_tcp = threading.Thread(target=servidor_tcp.inicia)
    thread_tcp.start()

    print(f"[S] Servidor UDP irá rodar na porta {porta_udp}.")
    servidor_udp = ServidorUDP('', porta_udp)
    thread_udp = threading.Thread(target=servidor_udp.inicia)
    thread_udp.start()

if __name__ == "__main__":
    main()