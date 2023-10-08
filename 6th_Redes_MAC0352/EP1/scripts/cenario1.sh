#!/bin/bash

# Inicie o servidor em um contêiner com base na imagem que você construiu
docker run -d --name servidor -p 5672:5672 amqp

# Aguarde alguns segundos para garantir que o servidor esteja totalmente iniciado
sleep 10

# Execute suas métricas de uso de rede e CPU aqui (por exemplo, uso do 'docker stats')
# Exemplo: Execute seus testes de servidor AMQP aqui

# Coletar métricas de uso de rede e CPU do contêiner
docker stats servidor

# Pare e remova o contêiner do servidor
docker stop servidor
docker rm servidor