# Matéria passada ou virtual (?)

> 5. (F) Controladores são dispositivos lógicos que emitem sinais analógicos para os
dispositivos. A comunicação com os controladores é feita nos sistemas
operacionais através de sinais especiais associados a instruções distintas de
harware. (F-2)

> 7. Em Unix/Minix/Linux os dispositivos são identificados por dois números:
major device number e minor device number. O primeiro identifica o tipo de
dispositivo e o segundo identifica o dispositivo individual.

> 8. Na arquitetura DMA (abreviação de “Disk Management Access”) podemos
aumentar a eficiência de proteção no sistema operacional, pois podemos locar
um bit de acesso nas instruções de entrada e saída quando queremos permitir
acesso apenas pelo kernel. (F-3)

> 15. (F) Uma das funções dos drivers é a criação de buffers para, utilizando o princípio
da localidade, diminuir o tempo de acesso a requisições seguidas ao mesmo
setor do disco.

> 16. O Minix tem quatro discos RAM. Uma das funções dos discos RAM é
implementar sistemas de arquivo na memória. Outra é possibilitar a escrita em
área da memória de programas como se fosse escrita em arquivos.

> 21. (F) Os jogos de seu computador estão lentos, uma das alternativas que você deve
considerar éo aumento de seu swap. (F-8)

> 25. A única maneira de se dificultar os ataques do tipo “bomba lógica” é com o
aumento da equipe de manutenção do sistema.

> 28. (F) Num canal oculto (covert channel), o software servidor mantém uma porta não
declarada com comunicação direta ao software malicioso. Este esquema pode
ser controlado encapsulando as comunicações do processo servidor (F-11).

> 36. O algoritmo do elevador simples favorece as trilhas do meio do disco

> 24. Os sistemas com arquitetura ARMV4 podem utilizar páginas de tamanhos
diferentes na tabela de páginas.

# EP3

> 30. (F) No EP3, mesmo modificando o esquema de alocação de memória, não é
necessário modificar o Kernel.

> 31. No EP3, é necessário alterar a forma como o Minix escolhe os buracos da
memória para implementar os diferentes algoritmos de alocação de memória, .

# Memória virtual 

- Permite acesso a um espaço de endereçamento maior do que a quantidade física de memória RAM disponível, ao armazenar partes do programa que não estão sendo utilizadas em um dispositivo de armazenamento secundário (swap space).
- Ilusão de que cada programa tem seu próprio espaço de endereçamento, que pode não ser o mesmo do endereço físico real da memória
- Tradução de endereços virtuais para endereços físicos,  geralmente implementado em hardware com o MMU - Memory Management Unit.
- Memória é organizada em blocos, páginas de tamanho fixo ou segmentos de tamanho variável.
- Blocos muito pequenos: alto custo de gerenciamento, blocos muito grandes: mais tempo para transferência e número menor de blocos na memória real.
- Endereço virtual composto por: base e deslocamento.
- Tradução de endereços: tabela de mapeamento.
- Registrador especial: indica o início da tabela de tradução.
- Funcionamento básico: Hardware verifica tabela de indexação. Se página está na memória, acessa o endreço real. Se não, lê seu conteúdo da memória secundária. Se memória cheia: substituição de página (LRU, FIFO).
- Tabela de indexação:
  - Endereço na memória real (RAM): endereço físico do início do bloco de memória virtual.
  - Endereço na memória secundária (SSD): Armazena o endereço da página na memória secundária.
  - Dirty bit: página foi modificada, precisa ser escrita de volta na memória secundária antes de ser substituída.
  - Residence bit: página é residente na memória física/real.
  - Reference bit: página foi acessada.

> 27. O grande problema com a memória virtual em computadores de 32 e 64 bits é
o tamanho da tabela de páginas. Na prática o overhead de espaço é tão grande
(1 milhão de entradas por processo de temos computador de 32 bits e páginas
de 4k), que torna inviável a utilização de um espaço de memória virtual por
processo (F-10)

> 32. (F) O uso de memória virtual não pode causar o bloqueio de um processo.(F12)

## Paginação

- Blocos de tamanhos fixos.
- Alinhadas em endereços múltiplos do tamanho da página.
- Endereço real: concatena num da pág real com o deslocamento.
- Tabela de mapeamento: residence bit, endereço da pág a memória secundária, num da pág na memória real.
- Fragmentação interna: em média 1/2 da pág.
- Mapeamento direto: endereço virtual traduzido diretamente para o físico com tabela de mapeamento, dois acessos a memória, melhorar performance: memória cache.
- Mapeamento associativo: busca feita em todas as entradas da tabela, paralelo, princípio da localidade.

> 3. (V) O princípio da localidade pode ter influência no escalonamento de disco.

> 18. Em sistemas de memória virtual, sistemas de paginação pura tem
fragmentação interna.

## TLBs

- Memórias de acesso rápido.
- Acelera processo de tradução.
- Mapeamento direto: uma página para cada posição da TLB, é possível substituir.
- Mapeamento totalmente associativo: busca simultânea em todas as entradas, sistemas modernos.
- Mapeamento N associativo: TLB dividida em bancos com N entradas, busca no banco é simultânea, cada página pode estar em N posições.
- Não é necessário esvaziar a TLB para escalonar outro processo, pois páginas antigas não são mais referenciadas, substituídas gradualmente.

> 9. (F) O uso de TLBs é quase universal em processadores modernos. Porém seu
sucesso é limitado pelo fato que uma página só pode ocupar uma entrada
determinada dentro da TLB e, se esta entrada estiver ocupada, temos uma
falha de TLB. Desta maneira TLBs tem sucesso limitado quando temos vários
programas pequenos.(F-4)
R: só substituir a pag.

> 33. Sistemas modernos de memória virtual usam esquemas complexos de TLBs
envolvendo TLBs totalmente associativas combinadas com esquemas de
bancos associados a determinados endereços

> 34. (F) Os esquemas de TLB, por envolverem uma "cache" global para tradução de
um número de página virtual para um número de pagina real, sempre devem
garantir que, na mudanća de processos, as TLBs devem ser esvaziadas para
que o próximo processo a ser escalonado não utilize páginas do processo
anterior. Isso indica que as fatias de tempo devem ser maiores para diminuir o
overhead de limpeza de TLB. (F13)

## Segmentação

- Segmentos de tamanhos variáveis.
- Parte lógica, código, dados, pilha, etc.
- Elimina fragmentação interna, ocorre externa.
- Proteção de acesso por segmento.
- Tabela de segmentos: residence bit, tam do segmento, bits de acesso, endereço do início do seg na memória física e secundária.
- Endereçamento associativo.
- Endereçamento direto: end físico = valor da base + deslocamento (mais lento que concatenação, paginação)

## Compartilhamento de memória

- Entradas em tabelas de blocos diferentes apontam para o mesmo segmento ou página.
- Redução do uso de memória.
- Código reentrante: usado simultâneamente em vários processos.
- Melhora velocidade de exec, reduz falhas de página.
- Mais fácil implementado em segmentos, divisão lógica.
- Complexo em páginas, fragmentação interna com crescimento dinâmico.

## Segmentação + Paginação

- Memória dividida em páginas, páginas agrupadas em segmentos (unidades lógicas).
- Tabela de segmentos (cada segmento) -> tabela de páginas -> páginas virtuais para físicas.
- Memória maior que a física disponível.
- Sem fragmentação externa.
- Overhead (custo adicional) minimizado pelas TLBs.
- Endereço dividido em segmento, página e deslocamento.

## Administração de memória

### Estratégias de carregamento

- Quando e como as páginas são carregadas na memória.
- Comum: paginação por demanda.
- Carregamento preventivo ou antecipatório.

### Estratégias de colocação

- Qual espaço vago na memória uma página será colocada.
- Sistemas segmentados: first fit, best fit (mais próxima do tamanho, bom em sistemas com tamanhos padronizados), worst fit (maior posição vaga).
- Sistemas paginados (pura ou S+P): indiferente. 

> 19. Em sistemas de memória real, a estratégia de alocação "best fit" deve ter bom
desempenho em sistemas com programas de tamanhos padronizados.

> 26. Uma das maneiras mais fáceis de se obter informação interessante é investigar
blocos de memória e setores de disco aleatoriamente alocados.

### Estratégias de reposição de páginas

- Escolha de qual bloco deve ser substituído.
- Páginas.
- Princípio da localidade (padrão de acesso à memória).

> 38. (F) Os esquemas de reposição de páginas em memória costumam, para aumentar a
segurança, repor primeiro as páginas modificadas da memória.(F15)

#### Randômica

- Poucos processos com uso intenso de memória, maioria não está sendo utilizada (princípio da localidade).
- Raramente utilizada, pois não considera frequência de uso.

#### FIFO

- Página com mais tempo na memória já foi muito utilizada, pode ser substituída.
- Problema: página com muito tempo pode estar sendo muito utilizada.
- Anomalia FIFO: mais memória mais falhas de páginas.
- FIFO segunda chance: só substitui quando bit reference está desligado (página não foi acessada).

> 40. No esquema de reposição de páginas FIFO segunda chance

#### LRU (Least Recently Used)

- Substitui página menos utilizada recentemente.
- Boa política, mas pode ter overhead (armazenar informações de acesso).
- Implementações com contadores ou pilhas.
- Falhas: loop, "deeply nested call".

#### NUR (Not Used Recently)

- LRU com menos sobrecarga.
- Substitui páginas que não foram modificadas.
- Ordem: não referenciada, referenciada mas não modificada, referenciada e modificada.
- Bits podem ser zerados quando todas são referenciadas (access bit, dirty bit, ou até sem estes).

> 23. (F) O algoritmo de reposição de páginas NUR (not used recently), apesar de
apresentar bom funcionamento, necessita que o hardware do computador tenha
dirty bit e reference bit. (F-9)
R: usa access bit e dirty bit.

> 39. O esquema de reposição de páginas NRU (not recently used) procura
aproximar o esquema LRU (least recently used) utilizando o dirty bit e o
access bit da página. Além disso pode ser implementado mesmo sem estes bits

#### Working Set

- Cada programa tem um conjunto de trabalho (páginas frequentemente usadas).
- Mantém o conjunto de trabalho sempre a memória e outros processos fora.
- Evita thrashing.
- Working set: WSClock: combinação de WS e FIFO segunda chance, residence bits, dirty bit, lista circular.

## Outros mecanismos de paginação

### Paginação em múltiplos níveis

- Diminui uso de uma tabela de página por processo ocupando muita memória.
- Tabela primária e várias secundárias, terciárias.
- Endereço virtual dividido em seções para cada tabela.
- Tabelas secundárias são mantidas na memória.

### Tabela de páginas invertida

- Tabela global para mapear endereços.
- Entradas para todas as páginas de todos os processos.
- Entrada: num página virtual e id do processo.
- É possível otimizar o tempo linear de acesso usando hash

> 10. (F) O esquema de memória virtual de tabelas de páginas invertidas tem a
vantagem de reduzir muito o uso de espaço para tabelas de páginas, mas não é
utilizado devido ao seu tempo de acesso linear na memória (overhead de
médio de n/2*100%, onde n é o número de páginas da memória). (F-5)
R: é possível otimizar o tempo linear de acesso usando hash

## Esquema de memória em processadores atuais

### ARMv7

- Paginação com dois níveis
- RISC, 32 bits, dispositivos móveis.
- MMU, seções e superseções.
- TLB em 2 níveis, micro TLB, main TLB.

![image](https://github.com/sabrizzs/hello-world/assets/93349105/ca6941c4-07d8-4814-9d2c-897ef2268d99)

### Intel IA-32

- Segmentação
- 3 modos de endereçamento: flat memory, end segmentado, end segmentado-paginado.
- Paginação pode ser desabilitada.

![image](https://github.com/sabrizzs/hello-world/assets/93349105/5010848a-6404-4fac-bd30-e655ffc8c71a)

### Intel IA-64

- Paginação, suporta emulação de segmentação, 3 modos de paginação.
- Utiliza TLB
- 4 unidades lógicas, ITLB (instruções), DTLB (dados)

![image](https://github.com/sabrizzs/hello-world/assets/93349105/53c27373-2578-4915-97de-6e945a1514a7)

> 24. Os sistemas com arquitetura ARMV4 podem utilizar páginas de tamanhos
diferentes na tabela de páginas.

# Arquivos

## Sistemas de arquivos

- Gerencia memóoria secundária (SSD).
- MULTICS: organizar no espaço de endereçamento, não utilizada agora.
- Hierarquia de memória: caches, memória primária, memória secundária.
- LOG: número de modificações grande em arquivos, escrita em vários blocos.
  
> 13. Sistemas de arquivos organizados em LOG realizam escrita de vários blocos
de uma vez, otimizando o acesso a disco em sistemas onde o número de
modificações em arquivos é grande.

## Funções do sistema de arquivos

- Criação, eliminação e modificação de arquivos
- Compartilhamento
- Controle de acesso
- Backup e recuperação
- Acesso simbólico (por nomes)
- Estruturação (ex. Sequencial, aleatório, etc.)
- Visão lógica (não física)
- Segurança (criptografia)
- Integridade de arquivos

> 22. Uma das funções potenciaois de sistemas de arquigos é lidar com rotinas de
segurança e criptografia

## Organização de arquivos

- Blocos de tamanho fixo: registros (mainframes, antigos), bytes (unix, minix).
- Métodos de acesso: sequencial (Unix/Minix, ex: character), indexado (indice), aleatório (Unix/Minix - block, lidos ou gravados em qualquer posição) 

### Organização de arquivos: organização interna

- Unix block: sequência de blocos por bytes, comandos read, write, seek (posicionar cursor em byte)
- QSAM (Queued Sequencial Access Method): blocos físicos, acesso registro lógico
- ISAM (Indexed Sequencial Access Method): árvore (blocos com num fixo de registros, cada bloco tem apontadores para outros blocos, acesso sequencial, busca rápida em arquivos grandes.
- Acesso aleatório, leitura e grav de qualquer lugar.
- SSTF (Shortest Seek Time First): melhor em fluxo, mas causa adiamento indefinido.

![image](https://github.com/sabrizzs/hello-world/assets/93349105/bc403b95-e76a-43f7-9020-798152b32bec)


> 37. O esquema de escalonamento de disco do menor tempo de "seek" primeiro é
o melhor em termos de fluxo (throughput), mas pode causar um adiamento
indefinido

## Tipos de arquivos

- Regulares: ASCII (linha terminada em line feed ou carriage return, linhas de tamanhos variáveis, úteis pois usam pipes), binários (código executável).
- Archive (UNIX): coleção de módulos de biblioteca compilados, mas não linkados.
- Problema: arquivos "fortemente tipados".

## Atributos comuns em arquivos

- Proteção
- Senha
- Criador
- Dono
- Flags: leitura/escrita, “hidden file”, System, ASCII/Binary, Archive (backup), Random acess, Temporary, Lock
- Tamanho do registro
- Key position, length
- Criação
- Último acesso, alteração
- Tamanho atual, máximo

## Operações em arquivos

- Criação
- Remoção
- Abertura
- Fechamento
- Leitura
- Escrita
- Append
- Seek
- Pega atributos
- Seta atributos
- Renomear
- Lock

## Diretórios

- Unix: Diretórios podem ser arquivos 
- Variações: um diretório por sistema, um diretório por usuário, estrutura hierárquica (árvore ou DAG (grafo)) 

### Operações em diretórios

- Criação
- Remoção
- Abertura
- Fechamento
- Leitura (readdir)
- Renomear
- Link: hard links, soft links.
- Unlink

> 4. (V) “Soft links” são muito mais usados em Unix do que “hard links”, isso se deve
em grande parte à generalidade de seu uso.

## Implementação de sistemas de arquivos

- Layout comum:  Master Boot Record (MBR)(primeiro setor do disco, código de inicialização, tabela de partições) seguido pela tabela de partições.
- Partições primárias (máximo 4 entradas) e lógicas.
- Unix estrutura: BootBlock (inicialização), SuperBlock (informações), Free Space Management, I-nodes, RootDir, Arquivos e Diretórios.

![image](https://github.com/sabrizzs/hello-world/assets/93349105/7c278dea-1bc4-49fe-b0ea-418a6be738a9)

- Alocação de arquivos Contínua: blocos em sequencia, fragmentação (externa?), conhecimento do tamanho do arq, foi usado em fitas magnéticas.
- Alocação de arquivos em lista ligada: sem fragmentação externa, acesso sequencial, péssimo em acesso aleatório, fragmentação interna.

### FAT

- Muito utilizado, simples e eficiente.
- Blocos do disco são reservados para armazenar uma tabela que contém informações sobre a alocação dos blocos de arquivos.
- Acesso aleatório rápido.
- Limitações de tamanhos de blocos suportados.
- Fragmentação interna (blocos fixos).

> 17. O sistema de arquivos FAT é adequado para sistemas de acesso aleatório

### I-nodes

- Unix.
- Compartilhamento de arquivos
- Cada arquivo é associado a um registro chamado I-Node, que contém informações e ponteiros para os blocos de dados do arquivo.
- Ponteiros para os primeiros blocos de dados do arquivo, com acesso direto e indireto (arquivos maiores, single indirect, double indirect e triple indirect).
- Baixo overhead para arquivos pequenos.
- Lento para arquivos grandes.
- Tamanho do arquivo escalável.
- Mais seguro que FAT, no FAT podemos recuperar arquivos recém eliminados percorrendo a lista livre.


> 1. (V) O sistema de arquivos de I-nodes facilita o compartilhamento de arquivos.

> 2. (F) O sistema de arquivos de I-nodes tem SEMPRE acesso aleatório menos
eficiente do que o sistema FAT. (F-1)

> 11. (V) Em Unix/Minix/Linux o programa fsck tem como objetivo deixar o sistema de
arquivos consistente. Para isso, verifica o número de referências aos I-nodes e
aos blocos dos arquivos.

> 12. O sistema de arquivos de I-nodes é mais seguro que o FAT, pois no FAT
podemos recuperar arquivos recém eliminados percorrendo a lista livre.

> 20. O uso de I-nodes ao invés de FAT não deve melhorar o desempenho de
programas com uso intensivo de I/O de acesso sequencial.

> 35. (F) Em esquemas de I-node o acesso aleatório em arquivos grandes é mais
eficiente que na FAT, pois não envolve o uso de uma lista ligada, com
complexidade linear de busca. (F14)

## Implementação de diretórios

### CP/M

- 8 bits, um diretório com todas as entradas de arquivos.

### DOS (precursor do Windows)

- 16 bits, diretório raiz é fixo e possui 112 entradas para floppies (discos flexíveis).
- Diretórios são tratados como arquivos normais.
- Estrutura hierárquica de diretórios
- Não possui suporte para atributos de usuário e hard links.

> 29. O sistema de diretórios do DOS com arquivos FAT-32 dificulta o uso de "hard
links".

### Windows 95

- Dois tipos de entrada de diretório para garantir compatibilidade com sistemas anteriores.
- Entradas adicionais para suportar nomes de arquivos grandes.

### Unix

- Tabela de I-nodes
- Diretórios são tratados como arquivos normais, cada um com I-node e Nome.
- Busca de arquivo recursiva.

### NTFS (Windows 2000 e depois)

- Arquivo é composto por um conjunto de atributos (fluxo de bytes).
- Master File Table (MFT), arquivo especial.

## Administração de espaço

- sequência contígua de bytes: arquivos armazenados como uma sequência contínua de bytes no disco.
- sequência de blocos: os arquivos são divididos em blocos de tamanho fixo.
- Tamanho do bloco: setor, trilha e cilindro.
- desperdício de espaço (-blocos maiores/+menores) X taxa de transferência de dados (-blocos maiores/+menores)
- Tamanho dos arquivos: Unix mediana de 2 KB.
- Espaço livre: lista ligada de blocos livres e vetor de bits (0 ou 1, compacta mas busca complexa).

## Compartilhamento de arquivos

- Grafo acíclico direcionado (DAG):
  - Hard links: (duas ou mais entradas no sistema de arquivos apontam para o mesmo descritor de arquivo, removidos se remover todas as entradas, arquivo removido pelo dono continua sendo usado, limitado a 1 sistema de arquivos, ciclos, cobrança de espaço para cada link).
  - Soft links (diretório que contém o endereço de outra entrada em um diretório, diferentes sistemas, arquivo removido = link invalido, sobrecarga de acesso).
- Problemas: backups, reconstituição e unicidade

## Confiabilidade do sistema de arquivos

- Localização dos setores ruins do disco: hardware (setor do disco com lista dos blocos ruins), software (arquivo especial com blocos ruins).
- Atualização atômica: consistência dos arquivos, unidade indivisível.

### RAID

- Operação de vários discos como se fossem apenas um, criando um "disco virtual"
- RAID 0: dois ou mais discos são combinados, não há redundância de dados nem recursos de recuperação nem proteção contra falhas, melhora velocidade de leitura e gravação.
- RAID 1: discos espelhados, recuperação da cópia, leitura rápida.
- RAID 5: stripping, paridade distribuída, recuperação por blocos restantes e paridade, resiste à falha se tiver mínimo de 3 discos.
- RAID 6: semelhante ao 5, paridade dupla distribuída, duas falhas toleradas.

> 6. (V) O sistema RAID1 aumenta a segurança dos dados e a velocidade de acesso.
