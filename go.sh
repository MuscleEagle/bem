#!/bin/bash
NginxDefaultFile="/etc/nginx/conf.d/default.conf"
NginxCustomFile="/etc/nginx/conf.d/custom.conf"

echo "Input Your Domain Name:"
read YourDomain
echo "Input Your Port:"
read YourPort
echo "Input Your Cache Path:"
read YourCachePath

echo "Delete Nginx Default Config File!"
rm -f $NginxDefaultFile
echo "Download new.conf"
wget -O $NginxDefaultFile https://raw.githubusercontent.com/MuscleEagle/bem/main/new.conf
echo "Fill Custom Setting"
sed -i "s/YourDomainName/${YourDomain}/g" $NginxDefaultFile

echo "Delete Old Nginx Custom Config File!"
rm -f $NginxCustomFile
echo "Download custom.conf"
wget -O $NginxCustomFile https://raw.githubusercontent.com/MuscleEagle/bem/main/custom.conf
echo "Fill Custom Setting"
sed -i "s/YourDomainName/${YourDomain}/g" $NginxCustomFile
sed -i "s/YourCachePath/${YourCachePath}/g" $NginxCustomFile
sed -i "s/YourPort/${YourPort}/g" $NginxCustomFile
