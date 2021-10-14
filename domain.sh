NginxDefaultFile="/etc/nginx/conf.d/default.conf"
echo "Delete Old Nginx Default Config File!"
rm -f $NginxDefaultFile
echo "Download default.conf"
wget -O $NginxDefaultFile https://raw.githubusercontent.com/MuscleEagle/zzinzzuptest/main/default.conf
echo "Input your Domain Name:"
read YourDomain
sed -i "s/YourDomainName/${YourDomain}/g" $NginxDefaultFile
