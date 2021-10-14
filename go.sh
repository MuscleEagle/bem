#!/bin/bash
YourDomain="xxx.com"
YourPort="6543"
YourCachePath="cache"
NginxDefaultFile="/etc/nginx/conf.d/default.conf"
NginxCustomFile="/etc/nginx/conf.d/custom.conf"

echo "Set Nginx Default Config"
read ContinueDefaultConfig
if(($ContinueDefaultConfig == "Y") || ($ContinueDefaultConfig == "y"))
{
  rm -f $NginxDefaultFile
  wget -O $NginxDefaultFile https://raw.githubusercontent.com/MuscleEagle/zzinzzuptest/main/default.conf
  sed -i "s/YourDomainName/${YourDomain}/g" $NginxDefaultFile
}else{
  exit 1
}

certbot certonly --webroot -w /usr/share/nginx/html/ --email admin@$YourDomain -d $YourDomain

echo "Set Nginx Custom Config"
read ContinueCustomConfig
if(($ContinueCustomConfig == "Y") || ($ContinueCustomConfig == "y"))
{
  rm -f $NginxCustomFile
  wget -O $NginxCustomFile https://raw.githubusercontent.com/MuscleEagle/zzinzzuptest/main/new.conf
  sed -i "s/YourDomainName/${YourDomain}/g" $NginxCustomFile
  sed -i "s/YourCachePath/${YourCachePath}/g" $NginxCustomFile
  sed -i "s/YourPort/${YourPort}/g" $NginxCustomFile
}else{
  exit 1
}
