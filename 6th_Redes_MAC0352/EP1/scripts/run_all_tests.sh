#!/bin/bash

SAMPLE_SIZE=100
MESSAGES=30
docker start amqp;
echo "Started docker container";
sleep 5;
./scripts/declare-queue.sh $1;
./scripts/publish.sh $1 $MESSAGES & 
./scripts/consume.sh $1 1 &
echo "Started get_cpu_network_from_docker"
./get_cpu_network_from_docker.sh $SAMPLE_SIZE $1
pkill -TERM -g $$
docker kill amqp;
echo "Killed docker container";
sleep 5;
