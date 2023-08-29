15 de agosto

## SHAPE ACQUISITION AND PROCESSING (chap3.pdf)

### Image Formation

- Passagem do contínuo para o discreto
- Processo de discretização
    - Processo espacial: **sampling**
        - Quantidade de fotoreceptores finita
        - Quantidade de luz varia dentro da célula
    - domínio: amostragem (qtd de pixels(quantidade de células)
        - **resolução espacial**
        - **escala**
        - bordas
        - serrilhado; diminuição da qtd de pixels; aliasing; anti-aliasig
        - piramides de imagens; ex: transmissão de imagens
    - Processo radiométrico
    - contradomínio: quantização (qnt de cores)
        - diminuição da qtd de cores cria curvas de nível
     
### Image segmentation

- Separação de elementos

### Shape sampling

- Abordagem dual (maneiras diferntes de ver a mesma coisa)
    - cada célula possui uma aresta de um grafo
    - quare-box
    - grid intersect

### Exerício

- 3 etapas
    - Gerar o sinal
        - Gera um numpy array de tamanho 1xN (1D) ou NXN (2D)
        - Como gerar o sinal

        main:
        sinal = geraSinal(N) #sintetiza o sinal e volta numpy array
        piramide(sinal)
        quantizacoes(sinal)

        1D:
        gerar senoide de N pontos
        com frequência w (omega)
        SIN(2pi.w.t/N)
        retorna a senoide como numpy

        2D:
        imagem com cada linha sendo uma senoide

        amostragem:
        f(t) = (f(t) + f(t+1))
        n/2, n/4, n/8

        quantização:
        função numpy
  

    - Gerar a pirâmie
    - Gerar as quantizaçõe

22 de agosto

- 4-neighborhood
- 8-neighborhood
    - há vizinhos com distancia diagonal
- dependendo da implementação o número de objetos é diferente
- **labeling algorithm**
    - rotula objetos diferentes
 
## Processamento de imagens

Dados -> Imagens: CG, síntese de imagens, visualização

Dados -> Dados: processamento de dados

Imagens -> Dados: visão

Imagens -> Dados: processamento de dados

- Transformações T
    - Io -> T -> Is
    - Pontuais de intensidade
        - O valor de saída depende do pixel de entrada
    - Locais
        - O valor do pixel de saída depende do pixel de entrada e da vizinhança dele

- Histograma não é utilizado para caracterizar formas
- log: valores pequenos são espalhados rapidamente
    - contraste em regiões escuras
    - saturação em regiões claras
 
### Ex 3

- Transformar a imagem em float e somar 0.1 para não ter log de 0
- O mesmo com a soma, para não somar mais que 256 e subtrair menos que 0

29 de agosto

- Transformações locais
    - Shift variant
    - Shift invariant
        - linear: T(af + bg) = aT(f) + bT(g)
            - todo filtro linear é implementada com uma convolução
            - toda **convolução** gera um filtro linear
        - não-linear
            - filtro da mediana

- Filtro da média
    - define uma região (janela/kernel/núcleo/operador) em volta do pixel
    - valor do pixel de saída é igual a média dos pixels na janela
    - pesos
    - borrar imagem
    - produto escalar entre dois vetores
 
- Free variable trasnformations
    -  Deslocamento:
    -  adicionar move a função para a esquerda
    -  subtrair move a função para a direita
    -  desloca janela ao longo da imagem; translações em x e y
    -  Mudança de escala:
    -  espalha o sinal (ex: a = 1/2)
    -  encolhe o sinal (ex: a = 2)
    -  multiplicação por -1: reflexão
    -  desvio padrão da gaussiana

- Convolution
    - * = operação entre dois sinais
    - gera um sinal
    - série de produtos escalares/internos
    - comutativa: tanto faz quem é a imagem (g(t)) ou filtro (h(T-t))
 
### Ex 4

- G(o, o): numero aleatorio com distribuição normal para cada sin(t)
- função de convolução
- 1) h(t): filtro da média
- 2) h(t): gaussiana
- para cada sinal usa os 3 filtros 




