#!/bin/bash

# get_cpu_network_from_docker SAMPLE_SIZE NUMBER_OF_CONSUMERS 
echo "Observing docker stats $1 times and saving in data/$2.txt"

for i in $(seq 1 1 $1)
do
  echo $(docker stats servidor --format "{{.CPUPerc}} | {{.NetIO}}" --no-stream) >> data/$2.txt
done

echo "GET_CPU_FROM_DOCKER ENDED $1"
