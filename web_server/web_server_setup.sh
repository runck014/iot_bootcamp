#!/bin/bash

# 1. Get pip
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
sudo python get-pip.py
rm get-pip.py # clean up

# 2. install #python packages
sudo pip install flask
sudo pip install pymongo

#3. start flask app
#python NAME_OF_APP.py


