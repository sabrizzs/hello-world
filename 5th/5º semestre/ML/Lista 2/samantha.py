'''
Usando o dataset da íris, só com sepal e petal length, classes setosa (-1) e versicolor (+1),
criar uma função que recebe X, y, w_inicial, b_inicial e random_state, embaralhando
a cada época caso seja pedido com numpy.random.shuffle(), inicializando com o valor
de random_state (numpy.random.seed(random_state)) uma única vez no início da função.
Os valores de w e b devem ser atualizados cada vez que um ponto da amostra estiver 
classificado errado até que não haja mais erros.
O programa ao final deverá imprimir uma lista com o número de atualizações em cada 
época, os valores de w e b da fronteira de decisão.
obs: embaralhe X e y juntos se não vai ficar tudo errado. 
Melhor embaralhar os números dos índices ao invés de embaralhar o próprio dataset in place.

Exemplo de execução:

digite w0: 1,1
digite b0: 1
random_state: False
[2, 2, 3, 1, 0]
[-3.3 8.1] -1.0

'''
# seu código aqui:
# importar módulos numpy e pandas
import numpy as np
import pandas as pd

# definir a função do perceptron
def perceptron(X, y, w_inicial, b_inicial, random_state):
    # Inicializa o gerador de números aleatórios
    np.random.seed(random_state)
    
    # Inicializa os pesos e o bias
    w = np.array(w_inicial)
    b = b_inicial
    
    # Inicializa a lista com o número de atualizações em cada época
    n_atualizacoes = []
    X_indices = np.arange(len(X))
    
    # Executa o algoritmo até que não haja mais erros
    fica = True
    while fica:
        fica = False
        
        # Embaralha os dados (se necessário)
        if random_state:
            np.random.shuffle(X_indices)
        
        # Itera sobre todos os pontos da amostra
        n_erros = 0
        for i in X_indices:
            # Verifica se o ponto está classificado corretamente
            if y[i] * (np.dot(w, X[i]) + b) <= 0:
                # Atualiza os pesos e o bias
                w += y[i] * X[i]
                b += y[i]
                fica = True
                n_erros += 1
        
        # Adiciona o número de atualizações nesta época à lista
        n_atualizacoes.append(n_erros)
    
    return n_atualizacoes, w, b

def main():
  # importar o dataset da íris e armazenar nas variáveis X e y o que for necessário
  df = pd.io.parsers.read_csv(
      filepath_or_buffer='https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data',
      header=None,
      sep=',',
      )
  # extract sepal length and petal length
  X = df.iloc[0:100, [0, 2]].values

  # select setosa and versicolor
  y = df.iloc[0:100, 4].values
  y = np.where(y == 'Iris-setosa', -1, 1)

  # pedir para o usuário inserir os dados
  # le w como string e converte para um array de floats
  w0_input = input()
  input_list = w0_input.split(",")
  w = np.array([float(num) for num in input_list])
  # le b
  b = input()
  b = float(b)
  # le random_state
  random_state = input()
  if (random_state == "False"):
      random_state = None
  else:
      random_state = int(random_state)

  # calcular os resultados usando a função
  numero_atualizacoes, w, b = perceptron(X, y, w, b, random_state)

  # imprimir resultados
  print(numero_atualizacoes)
  print(w, b)
    

if __name__=="__main__":
  main()