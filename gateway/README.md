# Gateway Overview

The gateway consists of a receiver (LoRa32u4) and a bridge to WiFi (RaspberryPi3). The LoRa32u4 serves as a receiver for the 915MHz signal coming from the node. It receives the payload of data, and then prints it over USB where the RPi3 is listening. A Python script on the RPi3 catches the packet coming over USB and then sends it on to the web server.
