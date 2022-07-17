import RPi.GPIO as GPIO
from time import sleep
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11,GPIO.OUT)
pwm_obj = GPIO.PWM(11,400)
while True:
	i=0
	while i<100:

		pwm_obj.start(i)
		sleep(0.05)
		i+=1
	while i>0:
		pwm_obj.start(i)
		sleep(0.05)
		i-=1
