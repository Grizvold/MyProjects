#!/bin/sh
#$echo <password> | sudo -S <command>
#echo ct,h kvmkhj | sudo -S sudo apt-get update

#creating runnable script on linux
#chmod +x ubuntu_program_installation_script.sh
#./ubuntu_program_installation_script.sh

PASS="$1"
GIT_NAME="$2" 
GIT_EMAIL="$3"

Red='\e[0;31m';
RCol='\e[0m';
#echo -e "${Red}this is red text${RCol}"

# update & upgrade #
echo -e "${Red}sudo apt-get update -y${RCol}"
echo $PASS | sudo -S sudo apt-get update -y

echo -e "${Red}sudo apt-get upgrade -y${RCol}"
echo $PASS | sudo -S sudo apt-get upgrade -y

#installing tree
echo -e "${Red}sudo apt-get install tree -y${RCol}"
echo $PASS | sudo -S sudo apt-get install tree -y

#installing git (via ubuntu guide)
echo -e "${Red}sudo apt update -y${RCol}"
echo $PASS | sudo -S sudo apt update -y

echo -e "${Red}sudo apt install git -y${RCol}"
echo $PASS | sudo -S sudo apt install git -y

#setting up user for git
echo -e "${Red}git config --global user.name GIT_NAME${RCol}"
git config --global user.name GIT_NAME

echo -e "${Red}git config --global user.email GIT_EMAIL${RCol}"
git config --global user.email GIT_EMAIL

#installing ssh on ubuntu 
echo -e "${Red}sudo apt update -y${RCol}"
echo $PASS | sudo -S sudo apt update -y

echo -e "${Red}sudo apt install openssh-server -y${RCol}"
echo $PASS | sudo -S sudo apt install openssh-server -y

#installing htop 
echo -e "${Red}sudo apt install htop -y${RCol}"
echo $PASS | sudo -S sudo apt install htop -y

#installing ubuntu restricted areas:
echo -e "${Red}sudo apt-get install ubuntu-restricted-extras -y${RCol}"
echo $PASS | sudo -S sudo apt-get install ubuntu-restricted-extras -y

#installing shutter (LightShot of Windows)
echo -e "${Red}sudo apt-get install shutter -y${RCol}"
echo $PASS | sudo -S sudo apt-get install shutter -y

#install OpenJDK 8
echo -e "${Red}sudo apt update${RCol}"
sudo apt update

echo -e "${Red}sudo apt install openjdk-8-jdk${RCol}"
sudo apt install openjdk-8-jdk

#installing visual studio code
echo -e "${Red}sudo apt update -y${RCol}"
echo $PASS | sudo -S sudo apt update -y

echo -e "${Red}sudo apt install software-properties-common apt-transport-https wget -y${RCol}"
echo $PASS | sudo -S sudo apt install software-properties-common apt-transport-https wget -y

echo -e "${Red}wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -${RCol}"
wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -

echo -e "${Red}sudo add-apt-repository 'deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main'${RCol}"
echo $PASS | sudo -S sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"

echo -e "${Red}sudo apt update -y${RCol}"
echo $PASS | sudo -S sudo apt update -y

echo -e "${Red}sudo apt install code -y${RCol}"
echo $PASS | sudo -S sudo apt install code -y

#installing make
echo -e "${Red}sudo apt install make -y${RCol}"
echo $PASS | sudo -S sudo apt install make -y

#installing gcc
echo -e "${Red}sudo apt install gcc -y${RCol}"
echo $PASS | sudo -S sudo apt install gcc -y

echo -e "${Red}sudo apt-get install build-essential g++ -y${RCol}"
echo $PASS | sudo -S sudo apt-get install build-essential g++ -y

#installing Tilda terminal
echo -e "${Red}sudo apt-get update -y${RCol}"
echo $PASS | sudo -S sudo apt-get update -y

echo -e "${Red}sudo apt-get install -y tilda${RCol}"
echo $PASS | sudo -S sudo apt-get install -y tilda

#installing vpn
echo -e "${Red}sudo apt-get install network-manager-openvpn network-manager-openvpn-gnome network-manager-pptp network-manager-pptp-gnome network-manager-strongswan network-manager-vpnc network-manager-vpnc-gnome${RCol}"
echo $PASS | sudo -S sudo apt-get install network-manager-openvpn network-manager-openvpn-gnome network-manager-pptp network-manager-pptp-gnome network-manager-strongswan network-manager-vpnc network-manager-vpnc-gnome

#install sound-switch 
echo -e "${Red}sudo apt-get install chrome-gnome-shell -y${RCol}"
echo $PASS | sudo -S sudo apt-get install chrome-gnome-shell -y

#installing Adobe Flash for browser
echo -e "${Red}sudo add-apt-repository 'deb http://archive.canonical.com/ $(lsb_release -sc) partner'${RCol}"
sudo add-apt-repository "deb http://archive.canonical.com/ $(lsb_release -sc) partner"

echo -e "${Red}sudo apt update${RCol}"
sudo apt update

echo -e "${Red}sudo apt install flashplugin-installer${RCol}"
sudo apt install flashplugin-installer -y

#install promodoro (timer for work)
echo -e "${Red}sudo apt-get install gnome-shell-pomodoro -y${RCol}"
echo $PASS | sudo -S sudo apt-get install gnome-shell-pomodoro -y

#installing eclipse
echo -e "${Red}sudo -S sudo apt update -y${RCol}"
echo $PASS | sudo -S sudo apt update -y

echo -e "${Red}sudo apt install openjdk-8-jdk -y${RCol}"
echo $PASS | sudo -S sudo apt install openjdk-8-jdk -y

#installing Programs
#Discord
echo -e "${Red}sudo snap install discord${RCol}"
echo $PASS | sudo -S sudo snap install discord

echo -e "${Red}sudo apt install libgconf-2-4 libappindicator1${RCol}"
echo $PASS | sudo -S sudo apt install libgconf-2-4 libappindicator1

#Spotify
echo -e "${Red}sudo apt install snapd${RCol}"
echo $PASS | sudo -S sudo apt install snapd

echo -e "${Red}sudo snap install spotify${RCol}"
echo $PASS | sudo -S sudo snap install spotify

#HardInfo on Linux
echo -e "${Red}sudo apt-get install hardinfo${RCol}"
echo $PASS | sudo -S sudo apt-get install hardinfo

#Peek (gif recorder)
echo -e "${Red}sudo add-apt-repository ppa:peek-developers/stable${RCol}"
echo $PASS | sudo -S sudo add-apt-repository ppa:peek-developers/stable

echo -e "${Red}sudo apt-get update${RCol}"
sudo apt-get update

echo -e "${Red}sudo apt-get install peek -y${RCol}"
sudo apt-get install peek -y

#Telegram
echo -e "${Red}sudo snap install telegram-desktop${RCol}"
echo $PASS | sudo -S sudo snap install telegram-desktop

#VLC
echo -e "${Red}sudo snap install vlc${RCol}"
echo $PASS | sudo -S sudo snap install vlc

#Zoom
echo -e "${Red}sudo apt -y install wget${RCol}"
echo $PASS | sudo -S sudo apt -y install wget

echo -e "${Red}wget https://zoom.us/client/latest/zoom_amd64.deb${RCol}"
echo $PASS | sudo -S wget https://zoom.us/client/latest/zoom_amd64.deb

echo -e "${Red}sudo apt install ./zoom_amd64.deb -y${RCol}"
sudo apt install ./zoom_amd64.deb -y
