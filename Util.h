#include <vector>
#include <string>
#include "land.h"
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

#ifndef __UTIL_H__ 
#define __UTIL_H__ 
std::vector<string> textureland();
std::vector<string> textureteam();
int seed();//used to enter the seed into the media layer
int zoom(bool, vector< vector< land > >*); //zooms in and out, the bool determines if it is going in or out,returns 0 if settings changed returns 1 if nothing was changed
int slide(char,vector< vector< land > >*); //slides screen left right up down returns 0 if changed, 1 if didn't 
int loadapplySurface(int, int, SDL_Surface*, SDL_Surface*); // Applies image, but does not refresh screen
void close(vector<SDL_Surface*>); //deletes an SDL surface
bool init(); //inits the sdl screen
#endif