#!/bin/bash
sudo apt update
#sudo apt install realvnc-vnc-server real-vnc-vnc-viewer
sudo apt-get install tightvncserver
sudo apt-get install vim


## Create and edit autostart options for Rpi
## Will make VNC Server run at startup
## so RPi is still accessible from VNCViewer with reboot
cd /home/pi
cd .config
mkdir autostart
cd autostart
echo -e "[Desktop Entry]\nType=Application\nName=TightVNC\nExec=vncserver :1\nStartupNotify=false"




vncserver:1
