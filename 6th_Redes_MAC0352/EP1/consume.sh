#!/bin/bash

num_consumers=$1

for i in $(seq 1 $num_consumers); do
  sleep 1
  queue_name="queue_$i"
  amqp-consume -q "$queue_name" -c 5 cat &
done
