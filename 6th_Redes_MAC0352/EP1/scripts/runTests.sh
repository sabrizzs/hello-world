#!/bin/bash

# Execute o script principal para 0 clientes e redirecione a saída para um arquivo
bash tests.sh 0 > resultados_0_clientes.txt

# Execute o script principal para 10 clientes e redirecione a saída para um arquivo
bash tests.sh 10 > resultados_10_clientes.txt

# Execute o script principal para 100 clientes e redirecione a saída para um arquivo
bash tests.sh 100 > resultados_100_clientes.txt
