
echo "Input App Name:"
read YourApp
DefaultFile="/usr/local/etc/${YourApp}/config.json"
echo "Download config.json"
wget -O $NginxDefaultFile https://raw.githubusercontent.com/MuscleEagle/zzinzzuptest/main/config.json

echo "Setting WS:"
echo "Input Your Port:"
read YourPortWS
echo "Input Your Cache Path:"
read YourPathWS
echo "Input Your Id:"
read YourIdWS

echo "Fill Custom Setting"
sed -i "s/YourPortWS/${YourPortWS}/g" $DefaultFile
sed -i "s/YourPathWS/${YourPathWS}/g" $DefaultFile
sed -i "s/YourIdWS/${YourIdWS}/g" $DefaultFile

echo "Setting KCP:"
echo "Input Your Port:"
read YourPortKCP
echo "Input Your Id:"
read YourIdKCP

echo "Fill Custom Setting"
sed -i "s/YourPortKCP/${YourPortKCP}/g" $DefaultFile
sed -i "s/YourIdKCP/${YourIdKCP}/g" $DefaultFile
