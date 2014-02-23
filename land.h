#include <SDL_image.h>
#ifndef LAND_H
#define LAND_H
 
class land
{
private:
    float height;
	//for the character association with type:W=deep water w=shallow water s=sand
	//g=grassland h=low hills H=highhills P=peak f=forrest e=eruptive D=deadlands 
	char type,status;
	//status holds things that my change throughout the game this will be used for water,eruption,flooded maybe
	SDL_Surface* surf;
 
public:
    char setheighttype(float);
	char settype(char);
	char gettype();
	char getstatus();
	void setstatus(char);
	void setsurf(SDL_Surface*);
 	SDL_Surface* getsurf();
};
 
#endif