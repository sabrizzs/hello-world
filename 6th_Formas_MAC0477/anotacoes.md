## 15 de agosto

### SHAPE ACQUISITION AND PROCESSING (chap3.pdf)

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

## 22 de agosto

- 4-neighborhood
- 8-neighborhood
    - há vizinhos com distancia diagonal
- dependendo da implementação o número de objetos é diferente
- **labeling algorithm**
    - rotula objetos diferentes
 
### Processamento de imagens

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

## 29 de agosto

- Transformações locais
    - Shift variant
    - Shift invariant
        - linear: T(af + bg) = aT(f) + bT(g)
            - todo filtro linear é implementada com uma convolução
            - toda **convolução** gera um filtro linear
            - função do espalhamento
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
    - com tal fixo: série de produtos escalares/internos
    - comutativa: tanto faz quem é a imagem (g(t)) ou filtro (h(T-t))
 
### Ex 4

- G(o, o): numero aleatorio com distribuição normal para cada sin(t)
- função de convolução
- 1) h(t): filtro da média
- 2) h(t): gaussiana
- para cada sinal usa os 3 filtros 

## 12 de setembro

- Filtros gaussianos: mais importãncia para quem está perto do meio; média.
- Quando funções gaussianas se encontram, significa que o produto escalar das duas funções é o máximo, com isso encontramos objetos
- Template matching

- Correlation
    - operador bolinha
    - asterisco: complexo conjulgado (para números complexos)
        - faz com que a correlação não seja comutativa
    - encontra regiões parecidas em imagens
 
- Object detection: yolo v2

### EP

- 1 parte: gera dataset .zip com diretórios e csv
- 3 parte: le nuvem e roda

## 19 de setembro

[****](https://www.minijogos.com.br/jogo/the-great-kitchen-escape)

- Template matching
- produto escalar
- Reconhecimento de formas:
    - Região 2D (f(x,y))
    - Contorno 1D (x(t), y(t))
- Fourier
    - Domínio do sinal: transformações levam o sinal até outro domínio que facilita certas coisas
        - Transformada
        - Transformada de Fourier
    - Para transmitir um cosseno, basta transmitir a frequência
        - Um gráfico com picos de acordo com o número de frequências
        - Representação do domínio mais barata
        - Transformada do cosseno
    - Qualquer sinal pode ser representado por uma combinação linear de senos e cossenos
    - Sinal discreto (t não é real) e finito
    - Mudança de base
    - f(t) -> F(w)
    - A base é seno e cossenos
    - convolução no dominio do tempo é equivalente ao F(w) multiplicado pelo G(w) (teorema da convolução)
    - f(t) * w(t) <-> F(w) * G(w)
    - f(t) <-> H(w)
        - f(t): transformada inversa de H(w)
        - H(w): transformada de fourier de f(t)

slide 115

## 24 de outubro

### Relembrando

- Filtro linear
    - g(t) = f(t) * h(t)
    - filtro de espalhamento
    - f(t) -> filtro -> g(t)
    - domínio do tempo (1D): variavel independente t (domínio do espaço (2D))
 
### Pipeline de classificação de formas

- Imagem original -> Forma do objeto
    -  A forma pode ser representada como imagem binária (pixels representando imagem de interesse)
    -  Segmentação de imagens
    -  Divisão da imagem em segmentos conectados (ex: fundo (background) e objeto (foreground); 2 segmentos)

#### Componente conectada

-  Componentes conectadas
    - Dado qualquer par de pixels: existe um caminho (sequencia de pixels um é vizinho do outro) que pertence ao conjunto

#### Segmentação

- Segmentação: gera segmentos que são componentes conectadas
- Segmentação semântica: atribui sentido ao pixel
- Segmentação de instâncias: numeração de cada objeto (arvore 1, arvore 2,...)

#### Image Thresholding

- algoritmo de limiarização
- com base em um histograma, define um limiar, pontos a direita sao um objeto e a esquerda sao outro
- pode ter mais de um limiar
- preto:0, branco: 255
- gimp: software de edição de imagem: varinha mágica

![image](https://github.com/sabrizzs/hello-world/assets/93349105/994ae14b-eb13-420a-b9be-7e7e2ec647e5)

#### Edge Detection

- podemos pensar na borda dos objetos em vez da região do objeto

### Exercício

- Implementar a convolução com o teorema da convolução, domínio de Fourier
- em cada caso temos um g(t) e um h(t)
- f(t) = g(t) * h(t) <-> F(w) = G(w) . H(w)
- no outro exercicio implementamos f(t) = g(t) * h(t)
- g, h --- FFT (transformada de fourier) ---> G, H ---- G.H (multiplicação) ----> F --- IFFT (inversa) ----> f(fourier)(t) (convolução baseado em fourier)
- visualizar: G, H, F (são complexos)
    - parte real: a
    - parte imaginaria: b
    - módulo |F|: tamanho da reta
    - fase: angulo
- comparar f e f(fourier)(t), colocar sobrepostos, comparar só a parte real do f(fourier)(t) complexo


