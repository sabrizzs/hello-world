#!/bin/bash

num_publishers=$1

for i in $(seq 1 $num_publishers); do
  queue_name="queue_$i"
  for j in $(seq 1 $num_publishers); do
    message="message_$j"
    amqp-publish -r "$queue_name" -b "$message"
    sleep 1
  done
done
