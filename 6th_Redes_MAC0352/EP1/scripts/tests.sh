#!/bin/bash

# Verifica o número correto de argumentos
if [[ $# -ne 1 ]]; then
  echo "Uso incorreto! Forneça o número de clientes a serem executados."
  echo "Exemplo: $0 10"
  exit 1
fi

# Número de clientes fornecido como argumento
NUM_CLIENTES=$1

num_queues=$((NUM_CLIENTES / 2))
num_publishers=$((NUM_CLIENTES / 2))
num_consumers=$((NUM_CLIENTES / 2))

# Iniciar o servidor em um contêiner com base na imagem que você construiu
docker run -d --name servidor -p 5672:5672 amqp

# Aguarde alguns segundos para garantir que o servidor esteja totalmente iniciado
sleep 10

# Criar filas
for i in $(seq 1 $num_queues); do
  queue_name="queue_$i"
  amqp-declare-queue -q "$queue_name"
done

# Executar os publishers
for i in $(seq 1 $num_publishers); do
  queue_name="queue_$i"
  message="message_$i"
  amqp-publish -r "$queue_name" -b "$message"
done

# Executar os consumers
for i in $(seq 1 $num_consumers); do
  queue_name="queue_$i"
  amqp-consume -q "$queue_name" -c 5 cat &
done

# Aguarde a execução por um período de tempo (ajuste conforme necessário)
sleep 30

# Coletar métricas de uso de rede e CPU do contêiner
docker stats servidor --no-stream --format "table {{.Container}}\t{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.NetIO}}"

# Parar e remover o contêiner do servidor
docker stop servidor
docker rm servidor

