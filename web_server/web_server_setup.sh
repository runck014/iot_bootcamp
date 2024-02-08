#!/bin/bash
  

# 1. Get pip
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3.8 get-pip.py
rm get-pip.py
export PATH=~/.local/bin:$PATH

# 2. install #python packages
pip install flask
pip install pymongo

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
