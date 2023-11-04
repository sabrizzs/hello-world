#!/bin/bash

ARGS_NUM=$#

if [[ $ARGS_NUM -lt 2 ]]; then
  echo "Wrong number of arguments!"
  echo "Usage: bash $0 <SCENARIO> <INDEX>"
  exit 1
fi

SCENARIO=$1
INDEX=$2

TEST_FOLDER=results-$SCENARIO
mkdir -p results
mkdir -p results/$TEST_FOLDER

docker-compose up -d server
CONTAINER_NAMES=($(docker ps --format "{{.Names}}"))
sleep 0.5

for NAME in "${CONTAINER_NAMES[@]}"; do
  rm -f results/$TEST_FOLDER/${NAME:0:11}-$INDEX.txt
  touch results/$TEST_FOLDER/${NAME:0:11}-$INDEX.txt
done

while true; do
  for NAME in "${CONTAINER_NAMES[@]}"; do
    docker stats --no-stream --format "{{.CPUPerc}} | {{.NetIO}}" $NAME >> results/$TEST_FOLDER/${NAME:0:11}-$INDEX.txt
  done
done
