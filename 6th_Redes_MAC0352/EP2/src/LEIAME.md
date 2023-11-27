# MAC0352 - Redes de Computadores e Sistemas Distribuídos - 2s2023 - EP2

Neste EP, foi implementado um sistema distribuído que possibilita uma partida multi-player de Pac-Man em modo texto em uma arquitetura híbrida (P2P e cliente/servidor)

## Como executar

Execute o servidor fornecendo as portas TCP e UDP como argumentos da linha de comando:

```bash
python servidor.py <porta TCP> <porta UDP>
```

Execute o cliente fornecendo três argumentos na linha de comando: o IP do servidor, a porta a ser usada e o protocolo (TCP ou UDP). Por exemplo:

```bash
python client.py <IP_do_Servidor> <Porta> <Protocolo>
```

Um Makefile foi fornecido para facilitar a execução do servidor e clientes com portas pré-definidas. Você pode usar os seguintes comandos:

- make servidor: Inicia o servidor com os argumentos: 8080 8080
- make cliente_tcp: Inicia o cliente usando TCP com os argumentos: localhost 8080 tcp
- make cliente_udp: Inicia o cliente usando UDP com os argumentos: localhost 8080 udp

O comando make clean remove os arquivos classificacao.txt, status.txt, usuarios.txt e log.txt gerados pelo servidor.

## Jogo (Pac-Man)

O jogo é implementado no arquivo pacman.py. Ele possui uma arena, onde o Pac-Man e o fantasma (local e remoto) se movimentam. O objetivo do Pac-Man é coletar todos os pacdots sem colidir com o Fantasma.

- O Pac-Man é representado por 'C', o fantasma local por 'F', o fantasma remoto por 'f' e a sobreposição de dois fantasmas por 'H'.
- Os pacdots são representados por '.' e as paredes por '*'.
- O Pac-Man pode se movimentar nas direções 'w' (cima), 'a' (esquerda), 's' (baixo) e 'd' (direita).
- O fantasma local se movimenta aleatoriamente, enquanto o fantasma remoto é controlado pelo jogador oponente remotamente.
- Se o Pac-Man colidir com qualquer fantasma, o jogo termina.

## Como jogar

Utilize os comandos abaixo para interagir com o servidor:

- novo <usuario> <senha>: Cria um novo usuário.
- senha <senha antiga> <senha nova>: Altera a senha do usuário.
- entra <usuario> <senha>: O usuário faz login no servidor.
- lideres: Informa a tabela de pontuação de todos os usuários registrados no sistema.
- l: Lista todos os usuários conectados no momento e indica se estão jogando ou não.
- inicia: O jogador inicia uma nova partida como Pac-Man.
- desafio <oponente>: Entra na partida sendo jogada pelo outro jogador. Nesse caso, entrará como fantasma. É permitido no máximo 1 fantasma remoto por partida, além do fantasma local.
- sai: Desloga.
- tchau: Finaliza a execução do cliente e retorna para o shell do sistema operacional.

Utilize os comandos abaixo para jogar Pac-Man:

- move <direcao>: movimenta o Pac-Man, use as teclas a - esquerda, s - baixo, d - direita e w - cima.
- move <direcao>: movimenta o fantasma remoto (no modo multiplayer), use as teclas a - esquerda, s - baixo, d - direita e w - cima.
- encerra: Encerra uma partida antes do término.

## Implementação

O servidor inicia duas threads principais:

- Thread do servidor TCP: responsável por aceitar conexões TCP.
- Thread do servidor UDP: responsável por aceitar conexões UDP.

Duas threads são responsáveis pela leitura comandos:

- Leitura de comandos dos clientes: lê os comandos enviados pelos clientes via sockets.
- Leitura de heartbeats e desafios: monitora os heartbeats dos clientes e lê desafios enviados por outros oponentes.

O servidor utiliza quatro classes que criam arquivos para persistência de dados:

- Usuarios: cria um arquivo persistente de usuários criados no servidor.
- Status: mostra os usuários logados atualmente.
- Classificacao: persiste e mostra a classificação de todos os usuários já criados.
- Log: armazena informações de log do servidor.

No lado do cliente, existem dois loops principais:

- Loop de comandos: lê os comandos do usuário, envia ao servidor por sockets e recebe as respostas.
- Loop de heartbeats e desafios: escuta os heartbeats e verifica desafios de oponentes.

O código do cliente também lida com a conexão dos dois jogadores em um jogo do Pac-Man. Um socket TCP é criado e conecta os dois jogadores. Cada movimento é enviado para o outro jogador pelo socket criado para o jogo para que fiquem sincronizados. Quando o jogo termina, a pontuação e o vencedor são enviados para o servidor e atualizados na classificação.

## Dificuldades de implementação

Tive dificuldades em implementar a verificação periódica da latência entre os clientes, assim como a execução do comando <atraso> que depende dessa implementação. Consegui implementar o início do servidor UDP, porém ao lidar com comandos dos clientes, algum erro ocorre e o servidor não consegue interpretá-los.

