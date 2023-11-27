from typing import Tuple
import socket
import random
import time

'''
TO-DO:
- fantasma local persegue o pacman?
- mudar o game over para vitoria?
- quantos pontos o fantasma ganha?
'''

class PacMan:
    def __init__(self):

        self.arena = [
            "******.**....... .....**.******",
            "******.**.*******.**.*******.**",
            "******.**.*.. ..*.**.*******.**",
            "..... ....*.....*..............",
            "******.**.*.. ..*.**.*******.**"
        ]
        self.arena_com_personagens = None

        self.pacman = (len(self.arena) // 2, len(self.arena[0]) // 2)
        self.fantasma_local = self.posicao_aleatoria()
        self.fantasma_remoto = None

        self.game_over = False
        self.vitoria = False
        self.pacman_pontuacao = 0
        self.fantasma_remoto_pontuacao = 0

        print("[P] PacMan iniciado!")

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
        if self.fantasma_local == self.fantasma_remoto:
            arena_com_personagens[x] = (
                arena_com_personagens[x][:y] + 'H' + arena_com_personagens[x][y + 1:]
            )
        else:
            x, y = self.fantasma_local
            arena_com_personagens[x] = (
                arena_com_personagens[x][:y] + 'F' + arena_com_personagens[x][y + 1:]
            )

            if self.fantasma_remoto != None:
                x, y = self.fantasma_remoto
                arena_com_personagens[x] = (
                    arena_com_personagens[x][:y] + 'f' + arena_com_personagens[x][y + 1:]
                )

        if self.checa_colisao():
            x, y = self.pacman
            arena_com_personagens[x] = arena_com_personagens[x][:y] + 'X' + arena_com_personagens[x][y + 1:]
            self.game_over = True
            print("[P] Pac-Man colidiu com um fantasma! GAME-OVER!")

        self.arena_com_personagens = arena_com_personagens
        return '\n'.join(arena_com_personagens)

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

        self.checa_vitoria()

    def move_fantasma_remoto(self, direcao):
        x, y = self.fantasma_remoto
        if direcao == 'w':
            x = (x - 1) % len(self.arena)
        elif direcao == 's':
            x = (x + 1) % len(self.arena)
        elif direcao == 'a':
            y = (y - 1) % len(self.arena[0])
        elif direcao == 'd':
            y = (y + 1) % len(self.arena[0])

        if self.arena[x][y] != '*':
            self.fantasma_remoto = (x, y)
        else: print("[P] O fantasma remoto bateu na parede")

    def move_fantasma_local(self, i, x, y):
        if i: # jogador 1 é responsável pela movimentação do fantasma local
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

        else: # o jogador 2 apenas recebe a posição que o jogador 1 setou
            self.fantasma_local = (x, y)

        return (x, y)

    def checa_colisao(self):
        if self.pacman == self.fantasma_local:
            return True
        elif self.pacman == self.fantasma_remoto:
            self.fantasma_remoto_pontuacao = 10
            x, y = self.pacman
            self.arena[x] = self.arena[x][:y] + 'X' + self.arena[x][y + 1:]
            return True

    def checa_vitoria(self):
        if all(row.count('.') == 0 for row in self.arena):
            self.vitoria = True 

    def remove_fantasma_remoto(self):
        self.fantasma_remoto = None
        self.fantasma_remoto_pontuacao = 0

    def pontuacoes(self):
        if self.vitoria: print("Parabéns! Você venceu!")
        else: print("Que azar! Você perdeu!")
        return self.pacman_pontuacao, self.fantasma_remoto_pontuacao, self.vitoria

    def turno(self):
        print(self.mostra_arena())
        time.sleep(1)

        print("[P] Fantasma local fez uma movimentação!")
        self.move_fantasma_local(1, -1, -1)
        print(self.mostra_arena())       
        time.sleep(1)
        
        direcao = input("Pac-Man> Digite a direção para mover o Pac-Man (w/a/s/d):\nPac-Man> ")
        self.move_pacman(direcao)





