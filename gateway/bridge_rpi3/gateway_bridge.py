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
      
      print(" ")
      
      '''
      Web server has multiple end points. The first for testing
      is /print_data. This illustrates how information can be
      passed from the gateway to the webserver.

      The second is /post_data. This posts data to an endpoint
      that publishes to a database.

      System IP Addresses:
      Group1 - 35.233.208.199
      G2 - 35.184.81.61  
      G3 - 35.223.173.114
      G4 - 35.223.181.147 
      G5 - 35.225.125.238
      G6 - 34.70.175.183 
      G7 - 35.192.193.176
      
      Port 5000 is open on all of them.

      Two end points:
      - /print_data (for testing)
      - /post_data (for posting to database)
      
      '''

      POST_ADDRESS = 'http://35.223.208.199:5000/print_data'
      r = requests.post(url = POST_ADDRESS, data=str(data), timeout=10)
      print('Posting data to: ', POST_ADDRESS)
      print(' ')
      print('Data: ', data)
      print(' ')
      print('REST response: ', r.text)
      print('----------------------------')
      print(' ')
