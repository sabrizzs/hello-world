## Dificuldades encontradas para o desenvolvimento do trabalho
Durante a elaboração do trabalho sobre implementação de um sistema de provas, algumas dificuldades surgiram desde as primeiras ideias para a lógica a ser aplicada até a construção de métodos e funções dentro do código. A exemplo, destacam-se os seguintes aspectos: compreensão das primeiras informações, transformação da lógica em algoritmo, acertar retornos de recursão e conflito de marcação.

### Compreensão das primeiras informações
Mais especificamente sobre à compreensão das primeiras informações, constata-se que a princípio tivemos que entender qual seria o objetivo da nossa implementação e deduzimos que teríamos que implementar um algoritmo para o cálculo proposicional que encontrasse uma contradição o mais rápido e eficiente possível. A partir disso, procuramos entender as estruturas, classes e funções do `código base` fornecido, para isso, criamos uma breve documentação que descreve partes desse algoritmo para nos ajudar a entender melhor.

### Transformação da lógica em algoritmo
Sobre a transformação da lógica em algoritmo cabe comentar que, após entendermos o objetivo do algoritmo, buscamos pensar em métodos para a implementação. Diante disso, após algumas pesquisas e ideias, decidimos seguir o algoritmo descrito no `material complementar` fornecido. Esse material descreve uma _estratégia de busca em profundidade_, baseado nisso, começamos a construir a lógica do nosso algoritmo e nesse contexto encontramos algumas dificuldades para assimilar as estruturas de dados para o provador de teoremas.
> Este tipo de busca tende a expandir um ramo até a saturação. No caso de tableux, isto significa expandir um ramo até que ele esteja fechado ou saturado.

### Acertar retornos de recursão
Durante a elaboração do nosso algoritmo, utilizamos funções recursivas, como a `expand()`, para expansões de ramos. Porém, encontramos alguns problemas de lógica na implementação que causaram certa confusão nos valores booleanos `True`e `False` e implicaram na identificação de contradições.

```
def expand(mp:MarkedProposition, branch, betas):
    '''
    Função recursiva de expansão de um filho de uma regra beta.
    Verifica tipo do filho e se houve contradição nesse ramo da beta. 
    '''
```

### Conflito de marcação
Ao longo da implementaçãos encontramos um conflito de marcação dos átomos, no qual , por exemplo, `TQ` e `FQ` não indicavam contradição quando deveriam. Observamos que esse erro era causado pela classe Preposition e optamos por criar a classe `MarkedProposition` que conversa o valor de cada preposição devidamente.
```
class MarkedProposition:
...
```
