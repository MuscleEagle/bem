#!/bin/bash
echo "Install dependencies and correct time！"
apt update
apt install ntpdate -y
apt install wget -y
apt install curl -y
apt install gcc -y
apt install nginx -y
apt install certbot -y
wget -O install-release.sh https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh
bash install-release.sh
rm install-release.sh
wget -O install-dat-release.sh https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-dat-release.sh
bash install-dat-release.sh
rm install-dat-release.sh
echo "Install finish！"
