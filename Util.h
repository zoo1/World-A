#include <vector>
#include <string>
#include "land.h"
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

#ifndef __INITIAL_H__ 
#define __INITIAL_H__ 
std::vector< std::vector< land > > initial(int length, int height);
std::vector<string> textureland();
std::vector<string> textureteam();
#endif