#!/bin/bash

CONTAINER_NAMES=($(docker ps --format "{{.Names}}"))

make -C ./scripts/ statsGenerator
for SCENARIO in {1..3}; do
  FOLDER=$(pwd)/results/results-$SCENARIO
  for NAME in ${CONTAINER_NAMES[@]}; do
    ./scripts/statsGenerator $FOLDER ${NAME:0:11}
  done
done

make -C ./scripts/
