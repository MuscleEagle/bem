echo "Install YourProject!"
wget -O install-release.sh https://raw.githubusercontent.com/YourSwitch/fhs-install-YourProject/master/install-release.sh
wget -O install-dat-release.sh https://raw.githubusercontent.com/YourSwitch/fhs-install-YourProject/master/install-dat-release.sh
bash install-release.sh
rm install-release.sh
bash install-dat-release.sh
rm install-dat-release.sh
echo "YourProject is ready!"
