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
  
  # Run operations alternately with intervals
  for ((i = 1; i <= NUM_CLIENTS / 2 ; i++)); do
    case $i in
      1)
        for j in $(seq 1 $num_queues); do
          queue_name="queue_$j"
          amqp-declare-queue -q "$queue_name"
        done
        sleep 1
        ;;
      2)
        # Execute the publishers
        for j in $(seq 1 $num_publishers); do
          queue_name="queue_$j"
          message="message_$j"
          amqp-publish -r "$queue_name" -b "$message"
        done
        sleep 1
        ;;
      3)
        # Execute the consumers
        for j in $(seq 1 $num_consumers); do
          queue_name="queue_$j"
          amqp-consume -q "$queue_name" -c 5 cat &
        done
        sleep 1
        ;;
      4)
        # Run 'docker stats' for 10 seconds
        echo "Running 'docker stats' for 10 seconds..." >> "$output_file"
        docker stats servidor --no-stream --format "table{{.CPUPerc}}\t{{.NetIO}}" >> "$output_file"
        sleep 2
        ;;
    esac
  done

  docker stop servidor
  docker rm servidor
done
