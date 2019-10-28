'''
Bryan C. Runck
GEMS Agroinformatics Initiative

Purpose: This script prints from USB to screen.
It illustrates the basic usage of the serial
library in Python.

Dependency: have LoRa32u4 node and receiver set up.
LoRa32u4 receiver printing data to USB.
'''

import serial

print(serial_port)
ser = serial.Serial(
        port='/dev/ttyACM0', 
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=0)

while 1:
  x=ser.readline()
  if len(x) > 55:
      print(x)
      print("-------------")
