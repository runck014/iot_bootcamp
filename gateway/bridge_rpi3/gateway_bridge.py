'''
Bryan C. Runck
GEMS Agroinformatics Initiative

Purpose: This script creates the bridge functionality
by reading from serial and then using HTTP to post
to the web server.

Dependency: have LoRa32u4 node and receiver set up.
LoRa32u4 receiver printing data to USB.
'''

import serial
import requests

# Open serial connection
ser = serial.Serial(
        port='/dev/ttyACM0', 
        baudrate=9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=0)

while 1:
  data = ser.readline()
  if len(data) > 55:
      print(data)
      print("-------------")
      print(" ")

      POST_ADDRESS = 'http://35.223.208.199:5000/print_data'
      print("Made it")
      r = requests.post(url = POST_ADDRESS, data=str(data))
      print('REST response: ', r.text)
