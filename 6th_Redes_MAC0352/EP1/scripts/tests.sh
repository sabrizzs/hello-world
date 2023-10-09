#!/bin/bash

# Define os cenários (0, 10, 100 clientes)
scenarios=(0 10 100)

for NUM_CLIENTS in "${scenarios[@]}"; do
  num_queues=$((NUM_CLIENTS / 2))
  num_publishers=$((NUM_CLIENTS / 2))
  num_consumers=$((NUM_CLIENTS / 2))

  docker run -d --name server -p 5672:5672 testes



  .script/declare_queues.sh $num_queues

  .script/publish.sh $num_publishers &

  .script/consume.sh $num_consumers &

  .script/docker_stats.sh "$output_file" 60 $NUM_CLIENTS

  docker stop server
  docker rm server

  # Calcula a média do uso de CPU
  cpu_average=$(awk '{ total += $1 } END { print total / NR }' "$output_file")

  # Calcula a soma dos bytes transmitidos e recebidos
  net_io_sum=$(awk -F'[/ ]+' '{ sum += $2; sum2 += $3 } END { print "Sum In: " sum " Sum Out: " sum2 }' "$output_file")

  # Registra os resultados no arquivo de saída
  echo "Média da CPUPerc: $cpu_average" >> "$output_file"
  echo "Soma dos bytes da NetIO: $net_io_sum" >> "$output_file"

done
