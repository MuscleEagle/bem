#!/bin/bash
read -r -p "Install dependencies?  [Y/n] " inputA
case $inputA in
    [yY][eE][sS]|[yY])
		echo "Yes"
		apt update
		apt install vim -y
		apt install chrony -y
		apt install wget -y
		apt install curl -y
		apt install gcc -y
		apt install uuid-dev
		apt install nginx -y
		apt install certbot -y
		apt install socat -y
		;;

    [nN][oO]|[nN])
		echo "No"
       		;;

    *)
		echo "Invalid input..."
		exit 1
		;;
esac

read -r -p "Correct time?  [Y/n] " inputB
case $inputB in
    [yY][eE][sS]|[yY])
		echo "Yes"
		timedatectl set-timezone Asia/Shanghai
		chronyc makestep
		;;

    [nN][oO]|[nN])
		echo "No"
       		;;

    *)
		echo "Invalid input..."
		exit 1
		;;
esac

echo "Create bemray project..."
wget -O bemray.c https://raw.githubusercontent.com/MuscleEagle/bem/main/bemray.c
gcc bemray.c -luuid -o bemray
echo "Run bemray..."
rm bemray.c
./bemray
rm bemray

read -r -p "Run bash?  [Y/n] " inputC
case $inputC in
    [yY][eE][sS]|[yY])
		echo "Yes"
		bash bemray.sh
		rm bemray.sh
		;;

    [nN][oO]|[nN])
		echo "No"
       		;;

    *)
		echo "Invalid input..."
		exit 1
		;;
esac

echo "Install finish！"

read -r -p "Reboot now?  [Y/n] " inputD
case $inputD in
    [yY][eE][sS]|[yY])
		reboot
		;;

    [nN][oO]|[nN])
		echo "Reboot later!"
       		;;

    *)
		echo "Reboot later!"
		exit 1
		;;
esac
