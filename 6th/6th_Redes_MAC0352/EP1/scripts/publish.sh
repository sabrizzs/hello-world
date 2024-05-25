#!/bin/bash

num_publishers=$1

for i in $(seq 1 $num_publishers); do
  queue_name="queue_$i"
  message="message_$i"
  amqp-publish -r "$queue_name" -b "$message"
  sleep 2
done
