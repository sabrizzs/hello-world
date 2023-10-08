#!/bin/bash

# Check the correct number of arguments
if [[ $# -ne 1 ]]; then
  echo "Incorrect usage! Please provide the number of clients to be executed."
  echo "Example: $0 10"
  exit 1
fi

# Number of clients
NUM_CLIENTS=$1

num_queues=$((NUM_CLIENTS / 2))
num_publishers=$((NUM_CLIENTS / 2))
num_consumers=$((NUM_CLIENTS / 2))

# Start the server in a container based on the image builted
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

# Wait for execution
sleep 30

# Collect network and CPU usage metrics from the server container
docker stats servidor --no-stream --format "table {{.Container}}\t{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.NetIO}}"

# Stop and remove the server container
docker stop servidor
docker rm servidor
