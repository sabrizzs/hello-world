#!/bin/bash

output_file="$1"
duration=$2
NUM_CLIENTS=$3

output_file="results_${NUM_CLIENTS}_clients.txt"
  echo "docker stats:" > "$output_file"

for ((j = 0; j < duration; j++)); do
  docker stats server --no-stream --format "{{.CPUPerc}} {{.NetIO}}" >> "$output_file"
  sleep 1
done
