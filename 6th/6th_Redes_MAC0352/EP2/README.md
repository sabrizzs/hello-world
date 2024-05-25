EP2 - REDES

## Problema

- Sistema distribuído: 
	- partida multiplayer de pacman
	- modo texto
	- arquitetura hibrída (P2P e cliente/servidor)
		- ações do cliente (cliente/servidor)
		- partida (P2P)
	- diversas máquinas em uma rede local (3 máquinas)
	
- Primeiro código (servidor):
	- parâmetro: porta(s) 
	- irá escutar por conexões do clientes
	- precisa suportar conexões TCP e UDP
		- comunicação direta entre cliente e servidor (TCP e UDP)
		- entre clientes (TCP)
	- funções:
		- monitorar se os clientes estão conectados
		- autenticar usuários
		- manter uma tabela de classificação (pacdots comidos)
		- registrar todas as ações da partida em um arquivo log
	- usuários do sistema e tabela de classificação são persistentes (arquivo)
	- servidor não tem tarefa de receber e enviar comandos do jogo
	- executa sem necessidade de interação:
		- daemon: plano de fundo
		- pode estar em segundo plano e invocado por '&' no shell
	- máquina de estado pode ser usada
	- comandos do protocolo de rede em ASCII:
		- verificação periódica de clientes conectados: heartbeat (sem interação do usuário)
		- verificação periódica entre clientes da latência durante partida (sem interação do usuário)
		- criação de usuário
		- login
		- mudança de senha
		- logout
		- lista de usuários conectados
		- início de uma partida (pelo pacman)
		- participação de uma partida em andamento
		- envio de uma jogada
		- encerramento de uma partida
		- recebimento da arena atualizada (tratamento de erro) (sem interação do usuário)
		- envio do resultado da partida (tratamento de erro) (sem interação do usuário)
		- solicitação da classificação
		- troca de mensagens em texto entre cliente/servidor e cliente/cliente

- Segundo código (cliente):
	- parâmetro: endereço IP e porta(s) do servidor
	- precisa informar o protocolo desejado como parâmetro a mais
	- clientes executarão o jogo conectando-se entre si
	- comandos do jogo são enviados entre os clientes
	- exibe o prompt para o usuário: Pac-Man>
	
## Requisitos

- Componentes do tabuleiro:
	- *: parede
	- .: pacdot
	- C: pacman (iniciado no centro da arena)
	- F: fantasma local
	- f: oponente (iniciado em qualquer espaço em branco) (1 por partida)
	- H: f e F no mesmo espaço
	- espaço em branco
	- arena cíclica
	
- Ordem de ações:
	1. fantasma local
	2. verifica colisão com pacman
	3. fantasma remoto
	4. verifica colisão com pacman
	5. pacman
	6. verifica se comeu pacdot e colisão com fantasma
	- espera de 1s entre ações
	- loop
	
## Entrega

- fonto do cliente e servidor
- MAKEFILE
- LEIAME.md com link para o vídeo

	
	

