from typing import Tuple
import socket
import random
import time

'''
TO-DO:
- cliente nao recebe desafio no meio do jogo
- fantasma local persegue o pacman?

'''

class PacMan:
    def __init__(self):

        # atributos do jogo
        self.arena = [
            "******.**....... .....**.******",
            "******.**.*******.**.*******.**",
            "******.**.*.. ..*.**.*******.**",
            "..... ....*.....*..............",
            "******.**.*.. ..*.**.*******.**"
        ]
        self.pacman = (len(self.arena) // 2, len(self.arena[0]) // 2)
        self.fantasma_local = self.posicao_aleatoria()
        self.fantasma_remoto = self.posicao_aleatoria()
        self.game_over = False
        self.pacman_pontuacao = 0

        # atributos da conexão
        self.socket = None
        self.socket_ouvinte = None
        self.porta = None
        self.addr = None
        print("[P] PacMan iniciado!")

    # métodos do jogo

    def posicao_aleatoria(self):
        while True:
            x = random.randint(0, len(self.arena) - 1)
            y = random.randint(0, len(self.arena[0]) - 1)
            if self.arena[x][y] == ' ':
                return (x, y)

    def mostra_arena(self):
        arena_com_personagens = self.arena.copy()
        x, y = self.pacman
        arena_com_personagens[x] = (
            arena_com_personagens[x][:y] + 'C' + arena_com_personagens[x][y + 1:]
        )

        x, y = self.fantasma_local
        arena_com_personagens[x] = (
            arena_com_personagens[x][:y] + 'F' + arena_com_personagens[x][y + 1:]
        )

        for linha in arena_com_personagens:
            print(linha)
        print()

    def move_pacman(self, direcao):
        x, y = self.pacman
        if direcao == 'w':
            x = (x - 1) % len(self.arena)
        elif direcao == 's':
            x = (x + 1) % len(self.arena)
        elif direcao == 'a':
            y = (y - 1) % len(self.arena[0])
        elif direcao == 'd':
            y = (y + 1) % len(self.arena[0])
        
        if self.arena[x][y] == '.':
            self.pacman_pontuacao += 1
            print(f"[P] Pac-Man comeu um pacdot! Pontuação: {self.pacman_pontuacao}")
            self.arena[x] = self.arena[x][:y] + ' ' + self.arena[x][y + 1:]

        if self.arena[x][y] != '*':
            self.pacman = (x, y)
        else: print("[P] O pacman bateu na parede")

    def move_fantasma_local(self):
        x, y = self.fantasma_local
        movimentacoes = []

        if self.arena[(x - 1) % len(self.arena)][y] != '*':
            movimentacoes.append((-1, 0))
        if self.arena[(x + 1) % len(self.arena)][y] != '*':
            movimentacoes.append((1, 0))
        if self.arena[x][(y - 1) % len(self.arena[0])] != '*':
            movimentacoes.append((0, -1))
        if self.arena[x][(y + 1) % len(self.arena[0])] != '*':
            movimentacoes.append((0, 1))

        if movimentacoes:
            dx, dy = random.choice(movimentacoes)
            x = (x + dx) % len(self.arena)
            y = (y + dy) % len(self.arena[0])
            self.fantasma_local = (x, y)

    def checa_colisao(self):
        if self.pacman == self.fantasma_local:
            print("[P] Pac-Man colidiu com o fantasma local! GAME-OVER!")
            self.game_over = True

    def checa_game_over(self):
        return self.game_over, self.pacman_pontuacao

    def turno(self):
        self.mostra_arena()
        direcao = input("Pac-Man> Digite a direção para mover o Pac-Man (w/a/s/d):\nPac-Man> ")
        self.move_pacman(direcao)
        self.checa_colisao()
        time.sleep(1)
        self.mostra_arena()

        print("[P] Fantasma local fez uma movimentação!")
        self.move_fantasma_local()
        self.checa_colisao()
        time.sleep(1)
             
    # métodos da conexão

    def conexao_desafiado(self):
        self.socket_ouvinte, self.porta = cria_socket_ouvinte()
        self.socket_ouvinte.listen()

        mensagem = f"jogo {porta}"

        envia_comando_ao_servidor(mensagem)



def cria_socket_ouvinte() -> Tuple[socket.socket, str]:
    s_ouvinte = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_ouvinte.bind(('', 0))
    s_ouvinte.listen(5)
    _, port1 = s_ouvinte.getsockname()
    str_port1 = '%05d' % port1
    return s_ouvinte, str_port1

def atualiza_sockets():
    global reconectado

    mutex_reconectado.acquire()
    r = reconectado
    mutex_reconectado.release()
    while r == 0:
        time.sleep(1)
        mutex_reconectado.acquire()
        r = reconectado
        mutex_reconectado.release()

    mutex_reconectado.acquire()
    reconectado = 0
    mutex_reconectado.release()

    if r == 1:
        return 1, ss_g[0]
    else:
        return 0, None

def envia_comando_ao_servidor(comando: str, ss: socket.socket):
    envia_comando_ao_socket(comando, ss)
    resposta = recebe_resposta_do_socket(ss)

    while resposta == '':
        sucesso, ss = atualiza_sockets()
        if not sucesso:
            break
        envia_comando_ao_socket(comando, ss)
        resposta = recebe_resposta_do_socket(ss)

    return resposta





