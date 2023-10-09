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

  for ((j = 0; j < 60; j++)); do
    sleep 1
    docker stats servidor --no-stream --format "{{.CPUPerc}} {{.NetIO}}" >> "$output_file"
  done

  docker stop servidor
  docker rm servidor

  cpu_average=$(awk '{ total += $1 } END { print total / NR }' "$output_file")

  net_io_sum=$(awk -F'[/ ]+' '{ sum += $2; sum2 += $3 } END { print "Sum In: " sum " Sum Out: " sum2 }' "$output_file")

  echo "Média da CPUPerc: $cpu_average" >> "$output_file"
  echo "Soma dos bytes da NetIO: $net_io_sum" >> "$output_file"
done
