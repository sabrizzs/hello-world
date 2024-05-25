### Exercício Programa 1 ######################################################
#  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP,             #
#  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA.             #
#  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM              #
#  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES               #
#  DESSE EP E QUE PORTANTO NÃO CONSTITUEM DESONESTIDADE ACADÊMICA             #
#  OU PLÁGIO.                                                                 #
#  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS AS CÓPIAS                     #
#  DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A                       #
#  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO E                    #
#  DESONESTIDADE ACADÊMICA SERÃO TRATADOS SEGUNDO OS CRITÉRIOS                #
#  DIVULGADOS NA PÁGINA DA DISCIPLINA.                                        #
#  ENTENDO QUE EPS SEM ASSINATURA NÃO SERÃO CORRIGIDOS E,                     #
#  AINDA ASSIM, PODERÃO SER PUNIDOS POR DESONESTIDADE ACADÊMICA.              #
#                                                                             #
#  Nome : Sabrina Araujo da Silva                                                                     #
#  NUSP : 12566182                                                                    #
#  Turma: MAC0460                                                                    #
#  Prof.: Ronaldo Fumio Hashimoto                                                                    #
###############################################################################

import numpy as np


""" programa ep01.py

Simular a diferença entre erro in e erro out a partir de um Universo (pré-estabelecido:
dados X pertencente a R² e Y: {-1,+1} com N pontos)
e um conjunto de hipóteses bem definido e finito!
LEIA O ENUNCIADO COMPLETO NO ARQUIVO EM  PDF

"""

#padroniza os dados OK
def standardization(X): # valor:0.5
  ''' 
    Given a np.array X returns X_std: mean = 0, std = 1 (not inplace - pure function)
  '''
  # seu código aqui
  
  mean = np.mean(X, axis=0)  #para cada coluna calcula a média
  std = np.std(X, axis=0)    #para cada coluna calcula o desvio padrão
  
  X_std = (X - mean) / std
  
  return X_std
 
#erro normalizado OK
def calc_error(Y,Y_hat): # valor:1.0
  ''' 
    Given Y (labels) and Y_hat(predicts), returns normalized error
    Inputs:
      Y: np.array or list
      Y_hat: np.array or list
  '''
  # seu código aqui
  
  #converte para np.array
  Y = np.array(Y)
  Y_hat = np.array(Y_hat)
  
  #compara elemento por elemento e calcula a média dos elementos booleanos
  #norm_error = np.mean(Y != Y_hat)
  norm_error = np.mean(np.not_equal(Y, Y_hat))
  
  return norm_error

#amostra aleatória OK
def sampling(N,X,Y,random_state=42): # valor:0.5
  '''
    Given the N #of samples (to sampling), X (np.array) and Y (labels - np.array)
    returns N random samples (X,y) type: np.array
  '''
  # seu código aqui
  
  np.random.seed(random_state)
  indices = np.random.randint(0, len(X), size=N)
  X_sample = X[indices]
  Y_sample = Y[indices]
  
  return (X_sample, Y_sample)

#cada hipótese representa uma diagonal OK
def diagonais(X,M,b): # valor:2.5
  '''
    Função Diagonais: retas 45º (coeficiente angular +1 e -1  variando bias 
    um tanto para frente e um tanto para trás - passo do bias (b passado por parâmetro) 
    definido pelo intervalo [-M//4,M//4)

    Sabendo que: 
      x0 * w[0] + x1 * w[1] + bias = 0 e que
      w = [1,1] no caso da reta com inclinação negativa e
      w = [1,-1] no caso da reta com inclinação positiva

    A seguinte ordem deve ser utilizada:
      bias partindo de -(M//4) * b até (M//4) * b (exclusive)
      A reta com inclinação negativa (coef == -1), vetor w = [1,1] (perpendicular a reta), e bias é calculda primeiro 
      e a na sequência reta com inclinação positiva, vetor w = [1,-1], e o mesmo bias.
      Conforme mostrado nos plots!

	parâmetros:
		X: np.array
		M: número de hipóteses do universo (número inteiro) - espera-se um múltiplo de 4
	Retorna 
		predict: np.array de np.array de y_hat, um y_hat para cada hipótese (reta), deve ter tamanho M
   '''
  # seu código aqui
  
  predicts = []
  
  #itera sobre os valores do bias no intervalo [-M//4, M//4) 
  for i in range(-M // 4, M // 4):
    bias = i * b

    #reta com inclinação negativa
    w_negativo = np.array([1, 1])
    y_hat_neg = np.dot(X, w_negativo) + bias

    #reta com inclinação positiva
    w_positivo = np.array([1, -1])
    y_hat_pos = np.dot(X, w_positivo) + bias

    #cada elemento tem dois conjunto de previsões, um para cada hipótese (reta)
    y_hat_neg = np.where(y_hat_neg >= 0, 1, -1)
    y_hat_pos = np.where(y_hat_pos >= 0, 1, -1)
    predicts.append(np.array(y_hat_neg))
    predicts.append(np.array(y_hat_pos))

  return np.array(predicts)
 
#verifica se a predição é positiva ou negativa OK
def euclidean_dist(p,q): # valor:0.5
  '''
    Given two points (np.array) returns the euclidean distance between them
  '''
  # seu código aqui
  p = np.array(p)
  q = np.array(q)
  
  dif = p - q                       #calcula a diferença entre os pontos P e Q
  dist = np.sqrt(np.dot(dif, dif))  #calcula o produto escalar e depois a raiz quadrada do resultado
  
  return dist

#conjunto de hipóteses de circunferências OK
def egocentric(X,C,r): # valor:2.0
  '''
    Given a dataset X (np.array), C (np.array) are the points that will be used as centers, and a radius r: 
      For each point in C, Creates a circumference c, each center works as an hypothesis, and classify points inside c as +1
      otherwise -1.
      Returns all predicts (an list for each point (used as center) )
  '''
  # seu código aqui
  
  predicts = []
  
  #para cada ponto em C, cria uma circunferência com centro em c_point e raio r
  for c_point in C:
    predict = []
    #classifica os pontos de acordo com a circunferência
    for x_point in X:
        if euclidean_dist(c_point, x_point) <= r:
            predict.append(1)
        else:
            predict.append(-1)
    predicts.append(predict)
  
  return predicts

def calc_freq(N,H_set,eps,X,Y,M=100,b=0.05,r=1,random_state = 42): # valor:3.0
  '''
  Given N # of samples(integer), H_set name of the hypotheses set 
  (string <diagonais> or <egocentric> error will be returned otherwise)
  eps: epsilon (abs(error_in - error_out) desired), X from the Universe data (np.array - complete dataset),
  Y is all label from theentire Universe(np.array), M # of hypotheses used if <diagonais> is chosen, 
  B: is the bias used when <diagonais> is chosen, r radius of the circumference if <egocentric> is chosen, 
  random_state to set the seed

  Returns:
    bound: theoretical bound for Pr[abs(error_in - error_out) > eps]
    probs: approximated probability of Pr[abs(error_in - error_out) <= eps] by the frequency 
      (# of occurancies (abs(error_in - error_out) <= eps) / # of hipotheses)
  '''
  # seu código aqui
  
  #padroniza os dados de entrada
  X_std = standardization(X)  
  
  #amostra aleatória
  X_amostra, Y_amostra = sampling(N, X_std, Y, random_state)
  
  #erro in
  if H_set == "diagonais":
    hypotheses_in = diagonais(X_amostra, M, b)
    hypotheses_out = diagonais(X_std, M, b)
    
  elif H_set == "egocentric":
    hypotheses_in = egocentric(X_amostra, X_amostra, r)
    hypotheses_out = egocentric(X_std, X_amostra, r)
    
  else:
    return "Error."
    
  error_in = calc_error(Y, hypotheses_in)
  error_out = calc_error(Y, hypotheses_out)


  bound = np.abs(error_in - error_out)
  print("error_in: " + str(error_in) + " error_out: " + str(error_out))
  
  #bound = 3
  probs = 2
  return (bound,probs)

############## Função principal - não será avaliada. ###########################
def main():
    # você pode criar ou importar um dataset qualquer e testar as funções
    # não importe o matplotlib no moodle porque dá erro pois não tem interface gráfica
    
    #X = np.asarray([[0,0],[1,0],[3,1],[3,2],[4,4]])
    M = 8
    b = 1
    #print(diagonais(X,M,b))
    
    C = np.ones(2)
    r = 1
    #print(egocentric(X,C,r))
    
    # Definir dados de entrada
    N = 100  # Número de amostras
    H_set = "diagonais"  # Conjunto de hipóteses: "diagonais" ou "egocentric"
    eps = 0.1  # Epsilon desejado
    X = np.random.rand(100, 2)  # Dados de entrada X (exemplo aleatório)
    Y = np.random.randint(2, size=100)  # Rótulos de classe Y (exemplo aleatório)
    M = 100  # Número de hipóteses se H_set for "diagonais" (opcional)
    b = 0.05  # Viés se H_set for "diagonais" (opcional)
    r = 1  # Raio se H_set for "egocentric" (opcional)
    random_state = 42  # Seed aleatória para reprodutibilidade (opcional)
    
    # Chamar a função calc_freq
    bound, probs = calc_freq(N, H_set, eps, X, Y, M, b, r, random_state)
    
    # Exibir os resultados
    print("Bound:", bound)
    print("Probs:", probs)
    
    return
############## chamada da função main() ########################################
if __name__ == "__main__":
    main()