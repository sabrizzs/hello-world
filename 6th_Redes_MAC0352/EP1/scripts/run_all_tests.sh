#!/bin/bash

SAMPLE_SIZE=100
MESSAGES=30
docker start servidor;
echo "Started docker container";
sleep 5;
./declare-queue.sh $1;
./publish.sh $1 $MESSAGES & 
./consume.sh $1 1 &
echo "Started get_cpu_network_from_docker"
./get_cpu_network_from_docker.sh $SAMPLE_SIZE $1
pkill -TERM -g $$
docker kill servidor;
echo "Killed docker container";
sleep 5;
