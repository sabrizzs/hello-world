#!/bin/bash

# Define os cenários (0, 10, 100 clientes)
scenarios=(0 10 100)

for NUM_CLIENTS in "${scenarios[@]}"; do
  num_queues=$((NUM_CLIENTS / 2))
  num_publishers=$((NUM_CLIENTS / 2))
  num_consumers=$((NUM_CLIENTS / 2))

  docker run -d --name server -p 5672:5672 testes

  for i in $(seq 1 $num_queues); do
    queue_name="queue_$i"
    amqp-declare-queue -q "$queue_name"
  done

  for i in $(seq 1 $num_publishers); do
    queue_name="queue_$i"
    message="message_$i"
    amqp-publish -r "$queue_name" -b "$message"
  done

  sleep 10

  for i in $(seq 1 $num_consumers); do
    queue_name="queue_$i"
    amqp-consume -q "$queue_name" -c 5 cat &
  done

    # Aguarda 1 segundo e coleta estatísticas do Docker
    sleep 1
    docker stats server --no-stream --format "{{.CPUPerc}} {{.NetIO}}" >> "$output_file"
  done

  docker stop testes
  docker rm testes

  # Calcula a média do uso de CPU
  cpu_average=$(awk '{ total += $1 } END { print total / NR }' "$output_file")

  # Calcula a soma dos bytes transmitidos e recebidos
  net_io_sum=$(awk -F'[/ ]+' '{ sum += $2; sum2 += $3 } END { print "Sum In: " sum " Sum Out: " sum2 }' "$output_file")

  # Registra os resultados no arquivo de saída
  echo "Média da CPUPerc: $cpu_average" >> "$output_file"
  echo "Soma dos bytes da NetIO: $net_io_sum" >> "$output_file"

done
