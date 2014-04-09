#include <SDL_image.h>
#include <queue>
#ifndef ORG_H
#define ORG_H
 
 class org
 {
 private:
 	//priority_queue<int> q1; queue which holds the goals of organism
 	int vector[2]; //direction and magnitude, vector[0] is direction 0-15 vector[1] is magnitude 0-3
 	int red,green,blue; //for the color wheel
 	char threat; //this determines how the organism interacts on a single organism basis, 0 runs from everything 100 chases
 public:
 	int i,j; //location of organism relative to the map
 	nextposition(int*,int*);//returns where the position of the organism would be next, 3x3 array of land that surrounds the current position
 	org(int,int); 
 	org(int,int,int,int,int);
 	void setrgb(int,int,int);//change the color of the sdl pixel generated -1 allows for the color the be unedited
 	void getrgb(int*,int*,int*); //returns the current rgb to the pointers
 	SDL_Surface* getsurf(int width,int height);//specify width 
 };
 #endif