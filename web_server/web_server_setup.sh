#!/bin/bash

# 1. Get pip
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
sudo python get-pip.py
rm get-pip.py # clean up

# 2. install python packages
sudo pip install flask
#mongodb interface

#3. start flask app
export FLASK_APP= #name of app
flask run --host=0.0.0.0


