#!/bin/bash

CONTAINER_NAMES=($(docker ps --format "{{.Names}}"))
N=10

make -C ./scripts/ agregateStats
for SCENARIO in {1..3}; do
  FOLDER=$(pwd)/results/results-$SCENARIO
  for NAME in "${CONTAINER_NAMES[@]}"; do
    for I in $(seq 1 $N); do
      ./scripts/agregateStats $FOLDER ${NAME:0:11}-$I.txt
    done
  done
done

make -C ./scripts/ clean