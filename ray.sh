
echo "Create ray..."
wget -O ray.c https://raw.githubusercontent.com/MuscleEagle/bem/main/ray.c
gcc ray.c -luuid -o fuckray
./fuckray
