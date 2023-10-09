#!/bin/bash

# Array of scenarios
scenarios=(0 10 100)

for NUM_CLIENTS in "${scenarios[@]}"; do
  num_queues=$((NUM_CLIENTS / 2))
  num_publishers=$((NUM_CLIENTS / 2))
  num_consumers=$((NUM_CLIENTS / 2))

  # Start the server in a container based on the image built
  docker run -d --name servidor -p 5672:5672 amqp

  sleep 10

  output_file="results_${NUM_CLIENTS}_clients.txt"
  echo "docker stats:" > "$output_file"

  i=0 

  for ((j = 0; j < 60; j++)); do
    queue_name="queue_$i"
    message="message_$i"

    # Verifique se i é menor que num_queues
    if [ $i -lt $num_queues ]; then
      # Criação de fila
      amqp-declare-queue -q "$queue_name"

      # Publicação de mensagem
      amqp-publish -r "$queue_name" -b "$message"

      # Consumo de mensagem
      amqp-consume -q "$queue_name" -c 5 cat &

      i=$((i + 1))
    fi

    # Executa docker stats
    docker stats servidor --no-stream --format "table {{.Container}}\t{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.NetIO}}" >> "$output_file"
    sleep 1
  done

  docker stop servidor
  docker rm servidor
done
