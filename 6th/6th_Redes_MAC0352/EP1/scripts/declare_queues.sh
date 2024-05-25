#!/bin/bash

num_queues=$1

for i in $(seq 1 $num_queues); do
  queue_name="queue_$i"
  amqp-declare-queue -q "$queue_name"
  sleep 1
done
