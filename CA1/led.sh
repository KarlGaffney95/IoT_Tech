#!/bin/bash

echo out > /sys/class/gpio/gpio60/direction

while true
do
	echo 1 > /sys/class/gpio/gpio60/value
	echo 0 > /sys/class/gpio/gpio60/value
done
