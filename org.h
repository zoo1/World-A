#include <SDL_image.h>
#ifndef ORG_H
#define ORG_H
 
 class org
 {
 private:
 	SDL_Surface* surf;
 	char type;
 	char aggression;
 	int currentgoal;
 public:
 	int i;
 	int j;
 	org(int,int);
 	void setsurf(SDL_Surface*);
 	SDL_Surface* getsurf();
 };
 #endif