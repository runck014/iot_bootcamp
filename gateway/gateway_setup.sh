#!/bin/bash
sudo apt update
#sudo apt install realvnc-vnc-server real-vnc-vnc-viewer
sudo apt-get install tightvncserver -y
sudo apt-get install vim -y


## Create and edit autostart options for Rpi
## Will make VNC Server run at startup
## so RPi is still accessible from VNCViewer with reboot
## if/then ensures process doesn't rewrite directories
## if the directory already exists
DIR = "/home/pi/.config/autostart"
if [ -d "$DIR" ]; then
  echo "VNC autostartup already exists in ${DIR}..."
else
  echo "Creating autostartup directory at ${DIR}"
  cd /home/pi
  cd .config
  mkdir autostart
  cd autostart
  echo -e "[Desktop Entry]\nType=Application\nName=TightVNC\nExec=vncserver :1\nStartupNotify=false" > tightvnc.desktop
fi


vncserver :1
