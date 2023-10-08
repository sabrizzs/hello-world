#!/bin/bash

# Array of scenarios (0, 10, and 100 clients)
scenarios=(0 10 100)

for NUM_CLIENTS in "${scenarios[@]}"; do
  num_queues=$((NUM_CLIENTS / 2))
  num_publishers=$((NUM_CLIENTS / 2))
  num_consumers=$((NUM_CLIENTS / 2))

  # Start the server in a container based on the image built
  docker run -d --name servidor -p 5672:5672 amqp

  # Wait for a few seconds to ensure the server is fully started
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

  # Wait for a period for the publishers to finish sending messages
  sleep 10

  # Execute the consumers
  for i in $(seq 1 $num_consumers); do
    queue_name="queue_$i"
    amqp-consume -q "$queue_name" -c 5 cat &
  done

  output_file="results_${NUM_CLIENTS}_clients.txt"
  docker stats servidor --no-stream --format "table {{.Container}}\t{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.NetIO}}" > "$output_file"

  # Wait for execution
  sleep 30

  # Collect network and CPU usage metrics from the server container
  output_file="results_${NUM_CLIENTS}_clients.txt"
  docker stats servidor --no-stream --format "table {{.Container}}\t{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.NetIO}}" >> "$output_file"

  # Stop and remove the server container
  docker stop servidor
  docker rm servidor
done
