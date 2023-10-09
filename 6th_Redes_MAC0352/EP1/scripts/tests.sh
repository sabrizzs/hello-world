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

  # Create queues
  for i in $(seq 1 $num_queues); do
    queue_name="queue_$i"
    amqp-declare-queue -q "$queue_name"
  done

  # Execute the publishers
  for i in $(seq 1 $num_publishers); do
    queue_name="queue_$i"
    message="message_$i"
    amqp-publish -r "$queue_name" -b "$message"
  done

  sleep 10

  # Execute the consumers
  for i in $(seq 1 $num_consumers); do
    queue_name="queue_$i"
    amqp-consume -q "$queue_name" -c 5 cat &
  done

  output_file="results_${NUM_CLIENTS}_clients.txt"
  echo "0s: " > "$output_file"
  docker stats servidor --no-stream --format "table {{.Container}}\t{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.NetIO}}" >> "$output_file"

  sleep 15
  echo "15s: " >> "$output_file"
  docker stats servidor --no-stream --format "table {{.Container}}\t{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.NetIO}}" >> "$output_file"
  
  sleep 15
  echo "30s: " >> "$output_file"
  docker stats servidor --no-stream --format "table {{.Container}}\t{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.NetIO}}" >> "$output_file"

  docker stop servidor
  docker rm servidor
done
