'''
Bryan C. Runck
GEMS Agroinformatics Initiative

Purpose: Illustrate how to post to the webserver.

Dependency: None
'''
import requests
from time import sleep

while 1:
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
    
    Port 5000 is open on all of them
    Two end points:
    - /print_data (for testing)
    - /post_data (for posting to database)
    
    '''
    
    data = "Hello World from RPi Post Script!"
    POST_ADDRESS = 'http://35.223.208.199:5000/print_data'
    r = requests.post(url = POST_ADDRESS, data=str(data))
    print('REST response: ', r.text)
    print('----------------------------')
    print(' ')
    sleep(3.0) #seconds

