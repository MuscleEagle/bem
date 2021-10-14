#!/bin/bash
YourDomain="xxx.com"
YourPort="6543"
YourCachePath="cache"
NginxDefaultFile="/etc/nginx/conf.d/default.conf"
NginxCustomFile="/etc/nginx/conf.d/custom.conf"

echo "Delete Old Nginx Default Config File!"
rm -f $NginxDefaultFile
echo "Download default.conf"
wget -O $NginxDefaultFile https://raw.githubusercontent.com/MuscleEagle/zzinzzuptest/main/default.conf
echo "Fill Custom Setting"
sed -i "s/YourDomainName/${YourDomain}/g" $NginxDefaultFile

certbot certonly --webroot -w /usr/share/nginx/html/ --email admin@$YourDomain -d $YourDomain

echo "Delete Old Nginx Custom Config File!"
rm -f $NginxCustomFile
echo "Download custom.conf"
wget -O $NginxCustomFile https://raw.githubusercontent.com/MuscleEagle/zzinzzuptest/main/new.conf
echo "Fill Custom Setting"
sed -i "s/YourDomainName/${YourDomain}/g" $NginxCustomFile
sed -i "s/YourCachePath/${YourCachePath}/g" $NginxCustomFile
sed -i "s/YourPort/${YourPort}/g" $NginxCustomFile
