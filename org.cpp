#include "org.h"
#include <SDL_image.h>
#include <iostream>
org::nextposition(int* x,int* y)
{
    if(vector[1])
    {
        switch(vector[0])
        {
            case 0:
                *x=i+vector[1];
                *y=j;
                break;
            case 1:
                *x=i+
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
            case 15:
                break;
        }
    }
}
org::org(int x, int y) {
	i=x;
	j=y;
	red=green=blue=0;
    threat=rand()%100;
    vector[0]=rand()%16;
    vector[1]=rand()%4;
}
org::org(int x, int y,int r,int g,int b){
	i=x;
	j=y;
	if(r!=-1)
		red=r;
	if(g!=-1)
		green=g;
	if(b!=-1)
		blue=b;
    threat=rand()%100;
    vector[0]=rand()%16;
    vector[1]=rand()%4;
}
void org::setrgb(int r,int g,int b){
	if(r!=-1)
		red=r;
	if(g!=-1)
		green=g;
	if(b!=-1)
		blue=b;
}
void org::getrgb(int *r,int *g,int *b) {
   *r=red;
   *g=green;
   *b=blue;
}
SDL_Surface* org::getsurf(int width,int height){
    SDL_Surface * PixelSurface;
    PixelSurface = NULL ;
    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
         rmask = 0xff000000;
         gmask = 0x00ff0000;
         bmask = 0x0000ff00;
         amask = 0x000000ff;
    #else
         rmask = 0x000000ff;
         gmask = 0x0000ff00;
         bmask = 0x00ff0000;
         amask = 0xff000000;
    #endif
    PixelSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, width,height, 32,rmask, gmask, bmask, amask);
    if(PixelSurface == NULL) {
         printf("Creation Failed!\n");
    }
    SDL_FillRect(PixelSurface,NULL,SDL_MapRGB ( PixelSurface->format, red, green, blue )); 
    return PixelSurface; 
}