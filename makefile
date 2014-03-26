start:
	g++ -g Main.cpp land.cpp PerlinNoise.cpp Util.cpp org.cpp -I /usr/include/SDL `sdl-config --libs`  Init.cpp -lSDL -lSDL_image -lSDL_ttf 
