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
read -r -p "Please enter the domain name: " DomainName
NginxDefaultFile="/etc/nginx/conf.d/default.conf"

echo "server {" > $NginxDefaultFile
echo "    listen        80;" >> $NginxDefaultFile
echo "    server_name   ${DomainName};" >> $NginxDefaultFile
echo "    location / {" >> $NginxDefaultFile
echo "        root   /usr/share/nginx/html;" >> $NginxDefaultFile
echo "        index  index.html index.htm;" >> $NginxDefaultFile
echo "    }" >> $NginxDefaultFile
echo "    error_page   500 502 503 504  /50x.html;" >> $NginxDefaultFile
echo "    location = /50x.html {" >> $NginxDefaultFile
echo "        root   /usr/share/nginx/html;" >> $NginxDefaultFile
echo "    }" >> $NginxDefaultFile
echo "}" >> $NginxDefaultFile
certbot certonly --quiet --non-interactive --agree-tos --webroot -w /usr/share/nginx/html/ --email admin@$DomainName -d $DomainName
certbot renew  --quiet  --no-self-upgrade
