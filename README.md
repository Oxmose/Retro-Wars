# Projet Retro-Wars
Retro Wars is an "Advance Wars" reboot developed in C++ by Tristan Stérin and Alexy Torres for a school project at the ENS de Lyon year 2015/2016

#To compile:
run "./compile.sh"
	-Don't forget to use chmod +x compile.sh

#To run:
go to : bin/[Linux][OSX]Release/
run ". prelaunch.sh" (not ./prelaunch.sh)
run ./Retrowars <port> to be host
OR
run ./Retrowars <ip> <port> to join a server

#Dependencies: (tested on debian Jessie)

freetype (libfreetype6-dev for linux)
jpeg (libjpeg-dev and libjpeg8-dev fot linux)
x11 (x11-common for linux)
xrandr (libxrandr-dev for linux)
xcb	(xcb for linux)
x11-xcb
xcb-randr (libxcb-randr0-dev for linux)
xcb-image (libxcb-image0-dev for linux)
opengl (freeglut3-dev for linux)
flac (libflac-dev for linux)
ogg (libogg-dev for linux)
vorbis (libvorbis-dev for linux)
udev (libudev-dev for linux)
vorbis (libvorbis-dev for linux)
openal (libopenal-dev for linux)
pthread
tinyxml2 (libtinyxml2-dev for linux)

#ERRORS:
##In case of error at while linking (compilation)
Compile all the the lib in the lib folder with your compiler
(All the lib where compiled with g++4.9)


*** Error in `./RetroWars': corrupted double-linked list: 0x0000000001fbe2f0 ***
In this case, please recompile all the libs and be sure to copy all *.so and *.a in the bin/[Linux][OSX]/lib/[correspondinglib] folder.


#INFORMATION:

All code in src/ was writtent by Tristan Stérin and Alexy Torres except the code contained in MD5Engine folder.
