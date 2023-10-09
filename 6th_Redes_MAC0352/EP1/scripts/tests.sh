#!/bin/bash

scenarios=(0 10 100)

for NUM_CLIENTS in "${scenarios[@]}"; do
  num_queues=$((NUM_CLIENTS / 2))
  num_publishers=$((NUM_CLIENTS / 2))
  num_consumers=$((NUM_CLIENTS / 2))

  docker run -d --name servidor -p 5672:5672 amqp

  sleep 10

  output_file="results_${NUM_CLIENTS}_clients.txt"
  echo "docker stats:" > "$output_file"

  i=0 

  for ((j = 0; j < 60; j++)); do
    queue_name="queue_$i"
    message="message_$i"

    if [ $i -lt $num_queues ]; then
      amqp-declare-queue -q "$queue_name"
      amqp-publish -r "$queue_name" -b "$message"
      amqp-consume -q "$queue_name" -c 5 cat &
      i=$((i + 1))
    fi

    docker stats servidor --no-stream --format "{{.CPUPerc}} {{.NetIO}}" >> "$output_file"
    sleep 1
  done

  docker stop servidor
  docker rm servidor

  cpu_average=$(awk '{ total += $1 } END { print total / NR }' "$output_file")

  net_io_sum=$( awk '{ split($2, arr, "/"); sum += arr[1]; sum2 += arr[2] } END { print "Sum In: " sum " Sum Out: " sum2 }' "$output_file")

  echo "Média da CPUPerc: $cpu_average" >> "$output_file"
  echo "Soma dos bytes da NetIO: $net_io_sum" >> "$output_file"

done
