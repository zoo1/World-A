#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include "land.h"

using namespace std;
//From main:
extern SDL_Surface* screen;
// Globals:
static int z=1; //current zoom level
static int screeny;
static int screenx=screeny=-1; //screen position related to zoom
static const int sc_bpp = 32;  // Bits per pixel.
bool init() //creates the sdl Video screen and inits everything
{ 
	 
	bool success = true; 

	//Initialize SDL 
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		success = false; 
	} 
	else 
	{ 
		//Create window 
		screen = SDL_SetVideoMode(1300, 714, sc_bpp, SDL_SWSURFACE);
		if( screen == NULL ) { 
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
			success = false; 
		} 
		else 
		{ 	
			//set the caption of the the window will also set icon image later
			SDL_WM_SetCaption("World-A", NULL);
		} 
	}	 
	return success; 
}

int loadapplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination) // Creates image, applies it to a surface,but does not refresh the screen
{
    //Make a temporary rectange to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    SDL_Surface* Surf_Temp = SDL_DisplayFormatAlpha(source);
    SDL_BlitSurface( Surf_Temp, NULL, screen, &offset );
    SDL_FreeSurface(Surf_Temp);
    return 0;
}

void close(vector<SDL_Surface*> freeme) //ends the SDL program and frees the images
{
    for(int i=0;i<freeme.size();i++)
        SDL_FreeSurface(freeme[i]);
	SDL_FreeSurface(screen);
	screen = NULL;
	//Quit SDL subsystems 
	SDL_Quit();
}

int zoom(bool inout, vector< vector< land > > map1)
{
    int originx,originy;
    if(inout)   //zoom in
    {
        switch(z){
            case 1: 
                //if it has not been zoomed in yet set the coords at the center of screen
                if(screeny==-1&&screenx==-1)
                {
                    screeny=map1.size()/2;
                    screenx=map1[0].size()/2;
                }
                originx=screenx-map1[0].size()/4;
                originy=screeny-map1.size()/4;
                for(int i=0;i<map1.size()/2;i++)
                {
                    for(int j=0;j<map1[0].size()/2;j++)
                    {
                      loadapplySurface(i,j,map1[originy+i][originx+j].getsurf(),screen);  
                    }
                }
                z++;
                return 0;
            case 2:
                originx=screenx-map1[0].size()/8;
                originy=screeny-map1.size()/8;
                for(int i=0;i<map1.size()/2;i++)
                {
                    for(int j=0;j<map1[0].size()/2;j++)
                    {
                      loadapplySurface(2*i,2*j,map1[originy+i][originx+j].getsurf(),screen);  
                    }
                }
                z++;
                return 0;
            case 3:
                return 1;
        }
    }
    else        //zoom out
    {
        switch(z){
            case 1:
                return 1;
            case 2: //return to full map size
                for(int i=0;i<map1.size();i++)
                {
                    for(int j=0;j<map1[0].size();j++)
                    {
                        loadapplySurface(i/2,j/2,map1[i][j].getsurf(),screen);
                    }
                }
                z--;
                return 0;
            case 3:
                //TODO make sure that screeenx and screeny do not lead to accessing arrays out of bounds
                originx=screenx-map1[0].size()/4;
                originy=screeny-map1.size()/4;
                for(int i=0;i<map1.size()/2;i++)
                {
                    for(int j=0;j<map1[0].size()/2;j++)
                    {
                      loadapplySurface(i,j,map1[originy+i][originx+j].getsurf(),screen);  
                    }
                }   
                z--;
                return 0;
        }
    }
}


int slide(char dir, vector< vector< land > > map1)
{
    int line;
    switch(dir){
        case 'u'://up
            loadapplySurface(0,1,screen,screen);
            switch(z){
                case 1:
                    int i;
                    line=screeny-map1.size()/4;
                    if(line<0)
                        line=0;
                    for(i=0;i<map1[0].size()/4;i++)
                        loadapplySurface(0,i*2,map1[line][i].getsurf(),screen);
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
            break;
        case 'd'://down
            loadapplySurface(0,-1,screen,screen);
            switch(z){
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
            break;
        case 'l'://left
            loadapplySurface(1,0,screen,screen);
            switch(z){
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
            break;
        case 'r'://right
            loadapplySurface(-1,0,screen,screen);
            switch(z){
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }
            break;
    }
}

//vector holds all different land texture strings
vector<string> textureland(){
vector <string> rtd;

rtd.push_back("textures/darkblue.bmp");
rtd.push_back("textures/lightblue.bmp");
rtd.push_back("textures/sand.bmp");
rtd.push_back("textures/green.bmp");
rtd.push_back("textures/lightbrown.bmp");
rtd.push_back("textures/brown.bmp");
rtd.push_back("textures/grey.bmp");
rtd.push_back("textures/black.bmp");
rtd.push_back("textures/darkgreen.bmp");
rtd.push_back("textures/orange.bmp");
return rtd;
}

//vector holds all different team texture strings
vector<string> textureteam(){
	vector <string> rtd;

	rtd.push_back("textures/red.bmp");
	rtd.push_back("textures/purple.bmp");
	rtd.push_back("textures/neonblue.bmp");
	rtd.push_back("textures/maroon.bmp");
	rtd.push_back("textures/yellow.bmp");
	return rtd;
}