#!/bin/bash

# 1. Get pip
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
sudo python get-pip.py
rm get-pip.py # clean up

# 2. install #python packages
sudo pip install flask
sudo pip install pymongo
sudo python -m pip install pymongo[srv]

# 3. Allow password only access to web server.
# NO NOT DO THIS FOR PRODUCTION. ONLY FOR BOOTCAMP.
# VERY UNSECURE.

# sudo adduser <name>
# sudo usermod -aG sudo <name>
# edit file: /etc/ssh/ssh_config
# PasswordAuthentication = Yes
# sudo service ssh restart

# 4. start flask app
#python NAME_OF_APP.py


