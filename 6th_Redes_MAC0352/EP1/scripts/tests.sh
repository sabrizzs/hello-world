#!/bin/bash

# Define os cenários (0, 10, 100 clientes)
scenarios=(0 10 100)

for NUM_CLIENTS in "${scenarios[@]}"; do
  num_queues=$((NUM_CLIENTS / 2))
  num_publishers=$((NUM_CLIENTS / 2))
  num_consumers=$((NUM_CLIENTS / 2))

  docker run -d --name servidor -p 5672:5672 testes

  sleep 10

  # Nome do arquivo de saída para os resultados
  output_file="results_${NUM_CLIENTS}_clients.txt"
  echo "docker stats:" > "$output_file"

  i=0

  # Executa medições por 60 segundos
  for ((j = 0; j < 60; j++)); do
    queue_name="queue_$i"
    message="message_$i"

    if [ $i -lt $num_queues ]; then
      # Declara a fila e inicia os publishers e consumers
      amqp-declare-queue -q "$queue_name"
      amqp-publish -r "$queue_name" -b "$message"
      amqp-consume -q "$queue_name" -c 5 cat &
      i=$((i + 1))
    fi

    # Aguarda 1 segundo e coleta estatísticas do Docker
    sleep 1
    docker stats servidor --no-stream --format "{{.CPUPerc}} {{.NetIO}}" >> "$output_file"
  done

  # Encerra o container do servidor RabbitMQ
  docker stop servidor
  docker rm servidor

  # Calcula a média do uso de CPU
  cpu_average=$(awk '{ total += $1 } END { print total / NR }' "$output_file")

  # Calcula a soma dos bytes transmitidos e recebidos
  net_io_sum=$(awk -F'[/ ]+' '{ sum += $2; sum2 += $3 } END { print "Sum In: " sum " Sum Out: " sum2 }' "$output_file")

  # Registra os resultados no arquivo de saída
  echo "Média da CPUPerc: $cpu_average" >> "$output_file"
  echo "Soma dos bytes da NetIO: $net_io_sum" >> "$output_file"

done
