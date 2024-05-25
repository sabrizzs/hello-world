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

# importar o dataset da íris e armazenar nas variáveis X e y o que for necessário
def dataset():
    
    url = 'https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data'
    iris = pd.read_csv(url, header=None)
    
    #seleciona apenas as amostras das classes Setosa e Versicolor
    specie_mask = (iris[4] != 'Iris-virginica')
    setosa_versicolor_data = iris.loc[specie_mask, :]
    
    #seleciona apenas as colunas correspondentes às medidas da sépala e da pétala
    X = setosa_versicolor_data.iloc[:, [0, 2]].values
    y = setosa_versicolor_data.iloc[:, 4].values
    
    # Atualiza o array y para armazenar -1 para Setosa e +1 para Versicolor
    y = np.where(y == 'Iris-setosa', -1, 1)
    
    return X, y

#definir a função do perceptron
def perceptron(X, y, w_inicial, b_inicial, random_state):
    np.random.seed(random_state)
    
    #Inicialização dos parâmetros do modelo
    w = w_inicial
    b = b_inicial

    #Lista que armazena o número de atualizações que o algoritmo do Perceptron realiza em cada época
    num_updates = []
    
    #Embaralha os índices para a escolha aleatória dos dados
    indices = np.arange(len(X))
    
    if random_state:
        np.random.shuffle(indices)
        
    #Loop principal do perceptron
    num_erros = 1
    while num_erros > 0:
        num_erros = 0
        if random_state:
            np.random.shuffle(indices)
        for i in indices:
            xi = X[i]
            yi = y[i]
            z = (np.dot(xi, w)+b)*yi
            if z <= 0:
                w += yi*xi
                b += yi
                num_erros += 1
        num_updates.append(num_erros)
    
    #Retorna os valores atualizados de w, b e o número de atualizações em cada época
    return w, b, num_updates

def main():
    
    X, y = dataset()
    
    #pedir para o usuário inserir os dados
    w0 = np.array(input("Digite w0: ").split(","), dtype=float)
    b0 = float(input("Digite b0: "))
    random_state = (input("Random state: "))
    
     #calcular os resultados usando a função
    if random_state.lower() == 'false':
        w, b, num_updates = perceptron(X, y, w0, b0, 0)
    else:
        w, b, num_updates = perceptron(X, y, w0, b0, int(random_state))
    
    #imprimir resultados
    print(num_updates)
    print(w, b)
    
if __name__ == '__main__':
    main()