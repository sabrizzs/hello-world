# Protocolo

## Estrutura do pacote

### Header

Todo pacote possui um header fixo, definido como:

| Byte   | Content           |
| ------ | ----------------- |
| Byte 1 | Tipo de Pacote    |
| Byte 2 | Sessão de usuário |

## Payload

Alguns pacotes podem possuir um payload. Cada informação presente no payload deve ser precedida por 1 byte
especificando o seu tamanho. Por exemplo:

| Byte   | Content |
| ------ | ------- |
| Byte 1 | 2       |
| Byte 2 | 'o'     |
| Byte 3 | 'i'     |

Por conta desta convenção, o número máximo de bytes que uma informação pode ter são 256 bytes.

## Tipos de pacotes

### Ping (1)

Cliente - Cliente / Servidor - Cliente

Realiza o heartbeat.

Não possui payload.

Uso iterativo:
Não é enviado pelo usuário.

### Ping Resp (2)

Cliente - Cliente / Cliente - Servidor

Resposta do heartbeat. Também informa a latência entre os hosts.

Não possui payload.

Uso iterativo:
Não é enviado pelo usuário.

### New (3)

Cliente - Servidor

Cria um novo usuário. Em caso de sucesso, responde com o pacote `New Resp`.
Caso contrário, responde com o pacote `Fail`.

O payload será:

| Byte     | Content            |
| -------- | ------------------ |
| Byte 1   | Username Length(U) |
| Byte 2   | Username[0]        |
| ...      | ...                |
| Byte U+2 | Password Length    |
| Byte U+3 | Password[0]        |
| ...      | ...                |

Uso iterativo:

```bash
$ new <usuario> <senha>
```

### New Resp (4)

Servidor - Cliente

Informa que a operação `New` foi realizada com sucesso.

O payload será composto por um texto de sucesso.

### In (5)

Cliente - Servidor

Faz o login de um usuário. Em caso de sucesso, responde com o pacote `In Resp`.
Caso contrário, responde com o pacote `Fail`.

O payload será o mesmo do pacote `new`, porém, informará também qual é a
porta em que esta ouvindo por oponentes (P2P). A tabela abaixo demonstra o payload:

| Byte       | Content            |
| ---------- | ------------------ |
| Byte 1     | Port Length (P)    |
| Byte 2     | Port[0]            |
| ...        | ...                |
| Byte P+2   | Username Length(U) |
| Byte P+3   | Username[0]        |
| ...        | ...                |
| Byte P+U+3 | Password Length    |
| Byte P+U+4 | Password[0]        |
| ...        | ...                |

Uso:

```bash
$ in <usuario> <senha>
```

### In Resp (6)

Servidor - Cliente

Informa que a operação `In` foi realizada com sucesso. A sessão será retornada no header.
Essa sessão deve ser usada nos futuros pacotes enviados.
Uma sessão é expirada somente se o servidor receber o pacote `Out`.

O payload será composto por um texto de sucesso.

### Pass (7)

Cliente - Servidor

Muda a senha do usuário. Em caso de sucesso, responde com o pacote `Success`.
Caso contrário, responde com o pacote `Fail`.

O payload será:

| Byte     | Content                    |
| -------- | -------------------------- |
| Byte 1   | Current Password Length(C) |
| Byte 2   | Current Password[0]        |
| ...      | ...                        |
| Byte C+2 | New Password Length        |
| Byte C+3 | New Password[0]            |
| ...      | ...                        |

Uso:

```bash
$ pass <senha antiga> <senha nova>
```

### Pass Resp (8)

Servidor - Cliente

Informa que a operação `Pass` foi realizada com sucesso.

O payload será composto por um texto de sucesso.

### Out (9)

Cliente - Servidor

Desloga. Em caso de sucesso, responde com o pacote `Success`.
Caso contrário, responde com o pacote `Fail`.

Não possui payload.

Uso:

```bash
$ out
```

### Out Resp (10)

Servidor - Cliente

Informa que a operação `Out` foi realizada com sucesso.

O payload será composto por um texto de sucesso.

### Fail (11)

Servidor - Cliente

Informa que não foi possível criar um novo usuário e/ou realizar o login.

O payload será um único byte contendo um dos status definidos abaixo.

| Status | Resultado               |
| ------ | ----------------------- |
| 1      | Pacote malformado       |
| 2      | Usuário não existe      |
| 3      | Usuário já existe       |
| 4      | Usuário não está logado |
| 5      | Usuário já está logado  |
| 6      | Senha inválida          |
| 7      | Servidor cheio\*        |

\*Como a sessão de usuário é representada somente por 1 byte, o número máximo de usuários ativos que o sistema
suporta são 256.

### List (12)

Cliente - Servidor

Pede para o servidor uma lista com todos os usuários conectados.

Não possui payload.

Uso:

```bash
$ l
```

### List Resp (13)

Servidor - Cliente

Lista todos os usuários conectados com seus respectivos IP/Porta e se estão ocupados (em partida) ou não. É importante notar que a porta fornecida é a porta em que o usuário conectado está esperando por conexões dos oponentes (P2P).

O payload será composto por dados de todos os usuários conectados no sistema, em sequência. Os dados de cada usuário
serão:

| Byte       | Content            |
| ---------- | ------------------ |
| Byte 1     | 1                  |
| Byte 2     | Status             |
| Byte 3     | Username Length(U) |
| Byte 4     | Username[0]        |
| ...        | ...                |
| Byte 4+U   | IP Length (I)      |
| Byte 5+U   | IP[0]              |
| ...        | ...                |
| Byte 5+U+I | Port Length (P)    |
| Byte 6+U+I | Port[0]            |
| ...        | ...                |

### Call (14)

Cliente - Cliente

Convida um oponente conectado para jogar. Em seguida, o oponente recebe uma solicitação de jogo e
responde com um `Call Resp`.

Uso:

```bash
$ call <oponente>
```

O payload será composto pelo nome do usuário chamador

### Call Resp (15)

Cliente - Cliente

O pacote informa se uma requisição de `Call` foi aceita (1), e o oponente deseja jogar com o X, (2) aceita e o oponente deseja jogar com o O, ou recusada (0). Em caso de aceite, o cliente receptor envia o pacote `Start` para o servidor com a sessão dos clientes.

Uso:
Não é enviado pelo usuário.

### Start (16)

Cliente - Servidor

Em caso de início de partida, o primeiro cliente a jogar envia para o servidor o nome do usuários envolvidos na partida. Em caso de sucesso, responde com o pacote `Start Rep`.
Caso contrário, responde com o pacote `Fail`.

O payload será composto pelos dados de sessão dos dois usuários.

Uso:
Não é enviado pelo usuário.

### Start Resp (17)

Informa que a operação `Start` foi realizada com sucesso.

Não possui payload.

### Play (18)

Cliente - Cliente

Após realizar uma jogada e atualizar o seu próprio tabuleiro, o cliente informa para o seu oponente a sua jogada
atual. O jogador que recebeu o resultado após a última jogada deve informar o servidor sobre o termino da partida.

Uso:

```bash
$ play <linha> <coluna>
```

### End (19)

Cliente - Servidor

Informa que uma partida foi encerrada. Em caso de sucesso, responde com o pacote `End Resp`.
Caso contrário, responde com o pacote `Fail`.

O payload será composto pelo status do jogo, seguido dos dados da sessão do usuário e da sessão do seu
adversário, respectivamente. Os status possíveis são:

| Status | Resultado              |
| ------ | ---------------------- |
| 0      | Partida não finalizada |
| 1      | Empate                 |
| 2      | Vitória do cliente     |
| 3      | Derrota do cliente     |

Uso:
Não é enviado pelo usuário.

### End Resp (20)

Servidor - Cliente

Informa que a operação `End` foi realizada com sucesso.

O payload será composto por um texto de sucesso.

### Over (21)

Cliente - Cliente

Informa um adversário que deseja encerrar a partida antes da hora. O adversário deve
receber este pacote e avisar o servidor sobre o encerramento.

Uso:

```bash
$ over
```

### Halloffame (22)

Cliente - Servidor

Pede a tabela de pontuação de todos os usuários registrados no sistema.

Não possui payload.

Uso:

```bash
$ halloffame
```

### Halloffame Resp (23)

Servidor - Cliente

Informa a tabela de pontuação de todos os usuários registrados no sistema.

O payload será composto por dados de todos os usuários do sistema, em sequência. Os dados de cada usuário
serão:

| Byte     | Content            |
| -------- | ------------------ |
| Byte 1   | Username Length(U) |
| Byte 2   | Username[0]        |
| ...      | ...                |
| Byte 2+U | Score Length       |
| Byte 3+U | Score Length[0]    |
| ...      | ...                |

### Disconnect (24)

Cliente - Cliente / Cliente - Servidor

Informa ao cliente/servidor que deseja encerrar a conexão. No caso do servidor, se a sessão de usuário for diferente de 0, irá deslogar o usuário representado por aquela sessão.

Não possui payload.

Uso:

```bash
$ bye
```
