#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "Initial.h"
using namespace std;
// Globals:
const int sc_bpp    = 32;  // Bits per pixel.

// foreground, background, screen
SDL_Surface* fg = NULL, *bg = NULL, *screen = NULL;

// Prototypes:
int loadapplySurface(int, int, SDL_Surface*, SDL_Surface*); // Applies image, but does not refresh screen
void FreeIMG(SDL_Surface*, ...); // Clears an image
void close();
bool init();

int main(int argc, char* argv[]) {
    if(!init())exit(1);
    //reads the info of the window
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
	int sc_width = info->current_w, sc_height = info->current_h;
	vector< vector< land > > map1=initial((info->current_w)/2,(info->current_h)/2);
    //loads the texture images we will be using
    vector<string> textland=textureland();
    vector<SDL_Surface*> image(textland.size());
    for(int i=0;i<textland.size();i++)
    {
        printf("%d %s\n",i,textland[i].c_str());
        if((image[i] = IMG_Load(textland[i].c_str())) == NULL) {
        return 1;
        }
    }
    SDL_Surface* Surf_Temp = NULL;
        

    for(int i=0;i<map1.size();i++)
    {
        for(int j=0;j<map1[0].size();j++)
        {
            if(map1[i][j].gettype()=='W')
               loadapplySurface(2*i,2*j,image[0],screen);
            if(map1[i][j].gettype()=='w')
               loadapplySurface(2*i,2*j,image[1],screen);
            if(map1[i][j].gettype()=='s')
               loadapplySurface(2*i,2*j,image[2],screen);
            if(map1[i][j].gettype()=='g')
               loadapplySurface(2*i,2*j,image[3],screen);
            if(map1[i][j].gettype()=='h')
               loadapplySurface(2*i,2*j,image[4],screen);
            if(map1[i][j].gettype()=='H')
               loadapplySurface(2*i,2*j,image[5],screen);
            if(map1[i][j].gettype()=='P')
               loadapplySurface(2*i,2*j,image[6],screen);
            if(map1[i][j].gettype()=='D')
               loadapplySurface(2*i,2*j,image[7],screen);
            if(map1[i][j].gettype()=='f')
               loadapplySurface(2*i,2*j,image[8],screen);
            if(map1[i][j].gettype()=='e')
               loadapplySurface(2*i,2*j,image[9],screen);

        }
    }
    // Update the screen:
    if (SDL_Flip(screen) == -1) {
                return 1; // The screen failed to be updated...
            }
    SDL_Event Events;
    bool Run=true;
    while(Run)
    {
        while (SDL_PollEvent(&Events))
        {
            if (Events.type == SDL_QUIT)
                Run = false;
        }
    }
    SDL_SaveBMP( screen,"sinfractalsum.BMP" );
    close();
    return 0;

 }

 bool init() { 
	 
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
		screen = SDL_SetVideoMode(1024, 768, sc_bpp, SDL_SWSURFACE);
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
void close() //ends the SDL program
{
	
	screen = NULL;
	//Quit SDL subsystems 
	SDL_Quit();
}