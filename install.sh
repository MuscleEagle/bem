#!/bin/bash
echo "Install dependencies..."
apt update
apt install vim -y
apt install ntpdate -y
apt install wget -y
apt install curl -y
apt install gcc -y
apt install uuid-dev
apt install nginx -y
apt install certbot -y
echo "Correct time..."
ntpdate cn.pool.ntp.org
cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
wget -O install-release.sh https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh
bash install-release.sh
rm install-release.sh
wget -O install-dat-release.sh https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-dat-release.sh
bash install-dat-release.sh
rm install-dat-release.sh
echo "Install finish！"
