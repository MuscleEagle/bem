apt update
apt install ntpdate
apt install wget
apt install curl
apt install gcc
apt install nginx
apt install certbot
wget -O install-release.sh https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh
bash install-release.sh
rm install-release.sh
wget -O install-dat-release.sh https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-dat-release.sh
bash install-dat-release.sh
rm install-dat-release.sh
