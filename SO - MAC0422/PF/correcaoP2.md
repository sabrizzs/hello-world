## Revisão P2 SO

6/15

### Questão 1
- **Falsa**
- Marquei: falsa
- A MMU que reedita
- o sistema operacional não viabiliza a memória virtual no reendereçamento
- Hardware faz o endereçamento

### Questão 2
- Verdadeira
- Área de swap: páginas que não estão na memória

### Questão 3
- Verdadeira
- Marquei: falsa

### Questão 4
- **Falsa**
- O tamanho do segmento não é de tamanho variável
- Não dá para implementar o tamanho variável

### Questão 5
- Verdadeira
- É a definição

### Questão 6
- **Falsa**
- O número da página não diz nada sobre o segmento
- Tem que ser o endereço do início do segmento
- Em páginas o número da página diz sobre o endereço, pois são de tamanho fixo e é só multiplicar o tamanho pelo número do bloco
- Em segmentação isso não é possível, pois os tamanhos dos segmnetos são variáveis

### Questão 7
- **Falsa**, prof achava que estava certa
- Falta o endereço na memória real

### Questão 8
- **Falsa**
- Não é possível desfragmentar a paginação, pois é fragmentação interna.
- Somente é possível desfragmentar a segmentação externa

### Questão 9
- Verdadeira
- Marquei: falsa
- A TLB é o hardware específico

### Questão 10
- **Falsa***
- Não é um trecho da tabela, é uma entrada individual
- São entradas completamente separadas
- Não está na cache
- É um hardware específico
- Caro de fazer, por isso é pequeno

### Questão 11
- Verdadeira

### Questão 12
- Verdadeira
- Definição de mapeamento N associativo

### Quetão 13
- Verdadeira
- Motivação da memória segmentada

### Questão 14
- Verdadeira
- SO é mapeado para dentro do programa

### Questão 15
- **Falsa**
- Marquei: falsa

### Questão 16
- **Falsa**
- Marquei: falsa, mas justifiquei errado
- TLB é indexada pelo conjunto página-segmento, número do bloco virtual que inclui todos os níveis de páginas
- A TBL é associada ao conjunto inteiro

### Questão 17
- Verdadeira

### Questão 18
- Verdadeira

### Questão 19
- Verdadeira
- Estratégia de reposição

### Questão 20
- Verdadeira
- FIFO usa bit de acesso

### Questão 21
- **Falsa**
- Não pode zerar o dirty bit

### Questão 22
- Verdadeira
- Marquei: falsa
- Protection bit é essencial

### Questão 23
- Verdadeira

### Questão 24
- Verdadeira, mas aceita como **falsa** se falar que existe páginas invertidas
- Marquei: não lembro o que coloquei, mas não foi verdadeira

### Questão 25
- Verdadeira

### Questão 26
- Verdadeira
- Existem hardwares que possuem TLB para hardware e TLB para dados

### Questão 27
- Verdadeira
- ARM e Intel

### Questão 28
- Verdadeira

### Questão 29
- Verdadeira, mas pode ser considerada **falsa** por causa do DAG
- Marquei: falsa

### Questão 30
- Falsa
- Indexado é por chave
- seek() é acesso aleatório

### Questão 31
- Não peguei a resposta, talvez seja verdadeira

### Questão 32
- **Falsa**, por dois motivos
- O tipo de arquivo fica no número mágico dos primeiros bytes do arquivo

### Questão 33
- Verdadeira

### Questão 34
- Verdadeira

### Questão 35
- Falsa
- Nome simbólico tem um problema seríssimo de ter que acessar totalmente o caminho do arquivo, é muito custoso

### Questão 36
- Verdadeira

### Questão 37
- Verdadeira
- Nem todos os discos precisam ter MBR

### Questão 38
- Verdadeira

### Questão 39
- Verdadeira

### Questão 40
- Não peguei a resposta

### Questão 41
- Verdadeira, mas prof aceitou uma questão como falsa
- Marquei: falsa, mas não sei se minha resposta conta

### Questão 42
- Falsa
- Marquei: falsa!

### Questão 43
- Verdadeira

### Questão
- Falsa
- Não existe setor de lixo em RAID

### Questão 45
- Falsa
- Não tem nenhuma proteção contra vírus
- Feitos para lidar com falha de hardware
