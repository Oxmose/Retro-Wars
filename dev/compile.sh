mkdir -p BUILD;
cd BUILD;

platform='unknown';
unamestr=`uname`;
if [[ "$unamestr" == 'Linux' ]]; then
	cp -f ../CMakeLinux/CMakeLists.txt .;
elif [[ "$unamestr" == 'Darwin' ]]; then
   	cp -f ../CMakeOSX/CMakeLists.txt .;
fi

cmake .;

make;
rm CMakeLists.txt;

