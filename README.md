### MAC0218 - Técnicas de Programação II
### Sabrina Araujo da Silva - n°USP 12566182

#### Mini EP1

```python
# Define um dicionário para armazenar os valores já calculados
memo = {0: 0, 1: 1}

# Calcula a sequência de Fibonacci
def fibonacci(n):
    # Verifica se o valor já foi calculado e armazenado no dicionário
    if n in memo:
        return memo[n]
    
    # Se o valor ainda não foi calculado, utiliza a recursão para calcular
    resultado = fibonacci(n-1) + fibonacci(n-2)
    
    memo[n] = resultado
    
    return resultado

# Lista de números para calcular a sequência de Fibonacci
numeros = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40]

# Calcula a sequência de Fibonacci para cada número da lista usando a função
for n in numeros:
    resultado = fibonacci(n)
    print("O resultado para o número", n, "é", resultado)
```

Neste código, a função fibonacci() utiliza recursão e memoização para armazenar os valores já calculados e melhorar a eficiência do código, sem chamadas desnecessárias. Ainda mais, as variáveis são nomeadas de forma clara e expressam o seu propósito de maneira objetiva, o que torna o código fácil de ler e entender. Portanto, considero este código muito bom.

### MAC0218 - Técnicas de Programação II
### Sabrina Araujo da Silva - n°USP 12566182

#### Mini EP2

```python
def fib(n):
    if n < 0:
        print("Número inválido")
    elif n == 0:
        return 0
    elif n == 1:
        return 1
    elif n == 2:
        return 1
    else:
        a = fib(n - 1)
        b = fib(n - 2)
        c = a + b
        return c
```

Nesse código, há muitas condições de verificação e linhas desnecessárias, o que torna o código maior e menos direto do que poderia ser.

Um exemplo do que poderia ser feito é o seguinte:
```python
def fibonacci(n):
    if n <= 1:
        return n
    else:
        return fibonacci(n-1) + fibonacci(n-2)
```
