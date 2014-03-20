The aim of this project is to make a suitable game that utilized the process of random generation while learning the language of C++.

The libraries I installed with sdl are: 
$ sudo apt-get install build-essential libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev \ 
libsdl-ttf2.0-dev libboost-dev

The environment I am working on this project in is Ubuntu 12.11

The whole program peices together all other files it is compiled via the command:
g++ -I /usr/include/SDL -o b.out Main.cpp -lSDL -lSDL_image land.cpp PerlinNoise.cpp Util.cpp org.cpp

Perlin Noise.cpp and Perlin Noise.h were not created by me