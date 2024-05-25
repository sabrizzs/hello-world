#!/usr/bin/python3

import ssl
import socket
import sys
import threading
import time
import os
from typing import List, Tuple

managers = list()

ping_timeout = 177
ssl_timeout = 1

class clientManager:
    def __init__(self, socket: socket.socket, addr):
        self.s = socket
        self.addr = addr

        s_listen, port = create_listener_socket()
        send_command_to_socket(self.s, port)

        self.s_sender, addr_background = s_listen.accept()

        self.ss, addr_SSL = setup_SSL_socket(s_listen)
        self.logged = False
        self.user = None
        self.desafiando = None
        self.desafiante = None

        self.buffer = None
        self.escreveu = 0
        self.leu = 1
        self.leu_mutex = threading.Lock()
        self.escreveu_mutex = threading.Lock()

        self.con_down = False
        
        
        
        client_answer = self.ss.recv(1024).decode('utf-8')

        #"ok" caso nova conexão
        if client_answer == 'ok':
            print(f'Cliente {(addr, addr_SSL, addr_background)} conectou')
            #log.client_connected(addr[0])
        
        #user "username" caso reconexão
        '''elif client_answer.split()[0] == 'user':
            state = logged_users.get_state_by_usr_last_exec(client_answer.split()[1])
            if not state:
                log.client_connected(addr[0])
                return
            if state[1] != self.addr[0]:
                #Pessoa modificou o código e está tentando logar no user de alguém por outro ip
                pass

            self.user = state[0]
            self.logged = True
            #print(f'Cliente {self.user} {(addr, addr_SSL, addr_background)} reconectou')
            logged_users.login(self.user, self.addr)
            log.client_reconnected(addr[0])
            if state[2]:
                #Tratar caso em que estavam jogando
                self.desafiando = state[3]
                pass'''
        
        

    def write_buffer(self, manager, msg: str):
        """Recebe um client manager e uma mensagem e a escreve no buffer deste manager.
        Retorna 1 caso tenha conseguido escrever, 0 caso contrário (já possui mensagem 
        não lida no buffer)
        """
        return manager.write_my_buffer(msg)

    def read_buffer(self, manager):
        """Recebe um client manager e retorna a mensagem no buffer desse manager.
        Retorna None caso não tenha nada no buffer
        """
        return manager.read_my_buffer()

    def write_my_buffer(self, msg: str):
        self.escreveu_mutex.acquire()
        if self.escreveu == 0:
            self.buffer = msg
            self.escreveu = 1
            self.escreveu_mutex.release()
            self.reset_my_leu()
            retval = 1
        else:
            #Ainda tem mensagem a ser lida no buffer
            self.escreveu_mutex.release()
            retval = 0
        return retval

    def read_my_buffer(self):
        msg = None
        self.leu_mutex.acquire()
        if self.leu == 0:
            msg = self.buffer
            self.leu = 1
            self.leu_mutex.release()
            self.reset_my_escreveu()
        else:
            self.leu_mutex.release()
        return msg

    def reset_my_leu(self):
        self.leu_mutex.acquire()
        self.leu = 0
        self.leu_mutex.release()
        
    def reset_my_escreveu(self):
        self.escreveu_mutex.acquire()
        self.escreveu = 0
        self.buffer = None
        self.escreveu_mutex.release()

    def interpret_buffer_message(self, msg: str):
        
        if msg.split()[0] == 'begin':
            self.desafiante = msg.split()[1]
            send_begin(self.s_sender, self.desafiante)
            return 'begin'
        
        elif msg.split()[0] == 'accept':
            send_command_to_socket(self.s, msg)
            return 'accept'

        elif msg.split()[0] == 'refuse':
            msg = "Seu desafio foi recusado :("
            send_command_to_socket(self.s, msg)
            return 'refuse'
        else:
            return 'unknown'

    def send_to_manager(self, manager_str: str, msg: str):
        for man in managers:
            if man.user == manager_str:
                while not self.write_buffer(man, msg):
                    #Fica tentando escrever. Não vai dar deadlock pois o server sempre vai limpar o buffer
                    #Uma hora ficará disponível
                    time.sleep(0.01)
                return 1
        return -1

    def interpreter(self):
        sslThread = threading.Thread(target=self.sslInterpreter, args=())
        sslThread.start()
        mainThread = threading.Thread(target=self.manage, args=())
        mainThread.start()

    def manage(self):
        global logged_users
        global log
        global userList
        global leaderboard

        self.s.settimeout(0.01)

        with self.s as s:
            counter = 0
            while True:
                try:
                    command = s.recv(1024).decode('utf-8')
                    command = command.split()
                    if (self.normalInterpreter(command) == -1):
                        break
                except:
                    counter += 1
                    if counter == 300:
                        send_command_to_socket(self.s_sender, 'Ping')
                        self.s_sender.settimeout(ping_timeout)
                        try:
                            resp = self.s_sender.recv(1024).decode()
                        except:
                            log.unexepected_disconnection(self.addr[0])
                            self.con_down = True
                            self.s_sender.close()
                            self.ss.close()
                            break
                        self.s_sender.settimeout(None)
                        counter = 0
                    self.get_and_treat_buffer_content()
    
    def get_and_treat_buffer_content(self):
        buff_content = self.read_my_buffer()
        if buff_content:
            return self.interpret_buffer_message(buff_content)
        return 0
    
    def normalInterpreter(self, command):
        if not command:
            log.client_disconnected(self.addr[0])
            #print(f'Cliente {self.user} {self.addr} encerrou a conexão. Normal saindo')
            logged_users.logout(self.user)
            self.s_sender.close()
            return -1
        

        if self.logged:
            if command[0] == 'logout':
                #print(f'Cliente {self.user} {self.addr} deslogou! Normal saindo')
                logged_users.logout(self.user)
                log.logout(self.user, self.addr[0])
                self.logged = False
                self.user = None
                send_command_to_socket(self.s, 'Logout realizado com sucesso!')

            elif command[0] == 'leaders':
                send_command_to_socket(self.s, leaderboard.get_formatted_leaderboard())

            elif command[0] == 'list':
                send_command_to_socket(self.s, logged_users.get_logged_users())

            elif command[0] == 'begin':
                self.desafiando = command[1]
                msg = command[0] + " " + self.user
                if self.desafiando == self.user:
                    send_command_to_socket(self.s, ">:(")
                    self.desafiando = None
                elif logged_users.usr_is_playing(self.desafiando) == 1:
                    send_command_to_socket(self.s, "Este usuário está em uma partida!")
                    self.desafiando = None
                elif self.send_to_manager(self.desafiando, msg) == -1:
                    send_command_to_socket(self.s, "Este usuário não está logado!")
                    self.desafiando = None
                else:
                    buff = self.get_and_treat_buffer_content()
                    while not buff:
                        time.sleep(0.01)
                        buff = self.get_and_treat_buffer_content()
                    if buff == 'accept':
                        logged_users.change_playing_against(self.user, self.desafiando)
                        logged_users.change_state(self.user, 1)
                        log.start_game(self.addr[0], self.user, logged_users.get_addr_by_user(self.desafiando), self.desafiando)
                    elif buff == 'refuse':
                        self.desafiando = None

            #accept PORTA
            elif command[0] == 'accept':
                if not self.desafiante:
                    send_command_to_socket(self.s, "Você não recebeu nenhum desafio!")
                else:
                    game_port = command[1]
                    msg = command[0] + " " + game_port + " " + self.addr[0]
                    self.send_to_manager(self.desafiante, msg)
                    send_command_to_socket(self.s, 'ok')
                    logged_users.change_state(self.user, 1)

            elif command[0] == 'refuse':
                if not self.desafiante:
                    send_command_to_socket(self.s, "Você não recebeu nenhum desafio!")
                else:
                    self.send_to_manager(self.desafiante, command[0])
                    self.desafiante = None
                    send_command_to_socket(self.s, "ok")

            elif command[0] == 'end':
                send_command_to_socket(self.s, "ok")
                if logged_users.usr_is_playing(self.user):
                    if self.desafiando:
                        log.end_game(self.addr[0], self.user, logged_users.get_addr_by_user(self.desafiando), self.desafiando, 3)
                    self.end_of_game()

            elif command[0] == 'empate':
                send_command_to_socket(self.s, "ok")
                if logged_users.usr_is_playing(self.user):
                    leaderboard.update_score(self.user, 1)
                    if self.desafiando:
                        log.end_game(self.addr[0], self.user, logged_users.get_addr_by_user(self.desafiando), self.desafiando, 0)
                    self.end_of_game()

            elif command[0] == 'vitoria':
                send_command_to_socket(self.s, "ok")
                if logged_users.usr_is_playing(self.user):
                    leaderboard.update_score(self.user, 2)
                    if self.desafiando:
                        log.end_game(self.addr[0], self.user, logged_users.get_addr_by_user(self.desafiando), self.desafiando, 1)
                    self.end_of_game()

            elif command[0] == 'derrota':
                send_command_to_socket(self.s, "ok")
                if logged_users.usr_is_playing(self.user):
                    if self.desafiando:
                        log.end_game(self.addr[0], self.user, logged_users.get_addr_by_user(self.desafiando), self.desafiando, 2)
                    self.end_of_game()

        else:
            send_command_to_socket(self.s, "Você precisa estar logado para usar este comando")

    def sslInterpreter(self):
        global logged_users
        global log
        global userList
        global leaderboard

        with self.ss as ss:
            ss.settimeout(ssl_timeout)
            while True:
                command = ''

                try:
                    command = ss.recv(1024).decode('utf-8')
                except socket.timeout:
                    if self.con_down:
                        break
                    continue
                except:
                    #print(f'Cliente {self.user} {self.addr} encerrou a conexão. SSL saindo')
                    self.logged = False
                    break

                command = command.split()
                if not command:
                    #print(f'Cliente {self.user} {self.addr} encerrou a conexão. SSL saindo')
                    self.logged = False
                    break

                elif not self.logged and len(command) == 3 and command[0] == 'adduser':
                    #print(f'Cliente {command[1]} quer se cadastrar!')
                    username = command[1]
                    passw = command[2]
                    created = userList.createLogin(username, passw)
                    if created:
                        leaderboard.add_user(username)
                        send_command_to_socket(ss, 'Usuário criado com sucesso!')
                    if not created:
                        send_command_to_socket(ss, 'Usuário não foi criado!')

                elif not self.logged and len(command) == 3 and command[0] == 'login':
                    loggedIn = userList.login(command[1], command[2])
                    if loggedIn:
                        self.logged = loggedIn
                        self.user = command[1]
                        logged_users.login(self.user, self.addr)
                        send_command_to_socket(ss, 'Logado com sucesso!')
                    else:
                        send_command_to_socket(ss, 'Usuário ou senha desconhecido!')
                    log.login_attempt(command[1], self.addr[0], loggedIn)

                elif self.logged and len(command) == 3 and command[0] == 'passwd':
                    changed = userList.changePassw(self.user, command[1], command[2])
                    if changed:
                        send_command_to_socket(ss, 'Senha alterada com sucesso!')
                    else:
                        send_command_to_socket(ss, 'Senha não foi alterada!')
                else:
                    send_command_to_socket(ss, 'Comando errado')

def main():
    if (len(sys.argv) != 2):
        print("Execução: " + sys.argv[0] + " porta")
        exit(1)
    
    PORT = int(sys.argv[1])
    HOST = ''


    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s_listen:
        s_listen.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        s_listen.bind((HOST, PORT))
        s_listen.listen()

        #log.init_server(not logged_users.tinha_user)
        try:

            while(True):
                conn, addr = s_listen.accept()
                cm = clientManager(conn, addr)

                #managers.append(cm)
                #cm.interpreter()
        except:
            print("Servidor finalizado")
            #log.terminate_server()


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


def send_begin(s: socket.socket, usr: str):
    msg = 'Desafio: '
    msg += usr + " o desafiou a uma partida! (accept|refuse)"
    send_command_to_socket(s, msg)

def send_command_to_socket(s: socket.socket, msg: str):
    s.sendall(bytearray(msg.encode()))


fpid = os.fork()
if fpid!=0:
  # "Daemon"
  sys.exit(0)

main()