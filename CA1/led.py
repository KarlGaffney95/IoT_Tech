#!/usr/bin/python
import Adafruit_BBIO.GPIO as GPIO

while True:
	GPIO.setup("P9_27",GPIO.OUT)
	GPIO.output("P9_27",GPIO.HIGH)
	GPIO.output("P9_27",GPIO.LOW)
