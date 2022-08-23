read -r -p "Have you turned off the DNS proxy and disabled SSL / TLS encryption?  [Y/n] " input
case $input in
    [yY][eE][sS]|[yY])
		echo "Yes"
		;;

    [nN][oO]|[nN])
		echo "No"
		exit 1
       		;;

    *)
		echo "Invalid input..."
		exit 1
		;;
esac

echo "Remove default.conf!"
rm /etc/nginx/conf.d/default.conf

echo "Remove custom.conf!"
rm /etc/nginx/conf.d/custom.conf

echo "Create default.conf!"

NginxDefaultFile="/etc/nginx/conf.d/default.conf"

echo "server {" > $NginxDefaultFile
echo "    listen        80;" >> $NginxDefaultFile
echo "    server_name   YourDomain;" >> $NginxDefaultFile
echo "    location / {" >> $NginxDefaultFile
echo "        root   /usr/share/nginx/html;" >> $NginxDefaultFile
echo "        index  index.html index.htm;" >> $NginxDefaultFile
echo "    }" >> $NginxDefaultFile
echo "    error_page   500 502 503 504  /50x.html;" >> $NginxDefaultFile
echo "    location = /50x.html {" >> $NginxDefaultFile
echo "        root   /usr/share/nginx/html;" >> $NginxDefaultFile
echo "    }" >> $NginxDefaultFile
echo "}" >> $NginxDefaultFile

echo "Restart nginx!"
systemctl restart nginx

echo "Install ACME!"
wget -O -  https://get.acme.sh | sh -s email=admin@YourDomain
/root/.acme.sh/acme.sh --issue  -d YourDomain   --nginx
/root/.acme.sh/acme.sh --upgrade --auto-upgrade
echo "ACME is ready!"
