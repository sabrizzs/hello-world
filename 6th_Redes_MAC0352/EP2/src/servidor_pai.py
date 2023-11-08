#!/usr/bin/python3

import ssl
import socket
import sys
import threading
import time
import os
from typing import List, Tuple

class clientManager:
    def __init__(self, socket: socket.socket, addr):
        self.s = socket
        self.addr = addr

        s_listen, port = create_listener_socket()
        send_command_to_socket(self.s, port)

        self.s_sender, addr_background = s_listen.accept()

        self.ss, addr_SSL = setup_SSL_socket(s_listen)

        client_answer = self.ss.recv(1024).decode('utf-8')

        #"ok" caso nova conexão
        if client_answer == 'ok':
            print(f'Cliente {(addr, addr_SSL, addr_background)} conectou')
            #log.client_connected(addr[0])

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

def send_command_to_socket(s: socket.socket, msg: str):
    s.sendall(bytearray(msg.encode()))


'''fpid = os.fork()
if fpid!=0:
  # "Daemon"
  sys.exit(0)'''

main()