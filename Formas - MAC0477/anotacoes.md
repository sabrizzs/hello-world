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
