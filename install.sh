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
echo "Create bemray project..."
wget -O bemray.c https://raw.githubusercontent.com/MuscleEagle/bem/main/bemray.c
gcc ray.c -luuid -o bemray
./bemray
bash dependencies.sh
bash modifyconfig.sh
echo "Install finish！"
