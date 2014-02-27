#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <list>
#include <stdio.h>
#include "Util.h"
#include "org.h"
using namespace std;
// runtime structure
struct coord{
    int i,j;
    bool alive;
};
// Globals:
const int sc_bpp    = 32;  // Bits per pixel.

//screen surface
SDL_Surface* screen = NULL;

// Prototypes:
void isalive(int, int , list<coord>*,int, int);//updates all the coords around the given point if they are alive
int loadapplySurface(int, int, SDL_Surface*, SDL_Surface*); // Applies image, but does not refresh screen
void close(vector<SDL_Surface*>);
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
        if((image[i] = IMG_Load(textland[i].c_str())) == NULL) {
            close(image);
            return 1;
        }
    }
    SDL_Surface* Surf_Temp = NULL;
        
    for(int i=0;i<map1.size();i++)
    {
        for(int j=0;j<map1[0].size();j++)
        {
            switch(map1[i][j].gettype())
            {
            case 'W':
                loadapplySurface(2*i,2*j,image[0],screen);
                map1[i][j].setsurf(image[0]);
                break;
            case 'w':
                loadapplySurface(2*i,2*j,image[1],screen);
                map1[i][j].setsurf(image[1]);
                break;
            case 's':
                loadapplySurface(2*i,2*j,image[2],screen);
                map1[i][j].setsurf(image[2]);
                break;
            case 'g':
                loadapplySurface(2*i,2*j,image[3],screen);
                map1[i][j].setsurf(image[3]);
                break;
            case 'h':
                loadapplySurface(2*i,2*j,image[4],screen);
                map1[i][j].setsurf(image[4]);
                break;
            case 'H':
                loadapplySurface(2*i,2*j,image[5],screen);
                map1[i][j].setsurf(image[5]);
                break;
            case 'P':
                loadapplySurface(2*i,2*j,image[6],screen);
                map1[i][j].setsurf(image[6]);
                break;
            case 'D':
                loadapplySurface(2*i,2*j,image[7],screen);
                map1[i][j].setsurf(image[7]);
                break;
            case 'f':
                loadapplySurface(2*i,2*j,image[8],screen);
                map1[i][j].setsurf(image[8]);
                break;
            case 'e':
                loadapplySurface(2*i,2*j,image[9],screen);
                map1[i][j].setsurf(image[9]);
                break;
            }              
        }
    }
    // Update the screen:
    if (SDL_Flip(screen) == -1) {
                close(image);
                return 1; // The screen failed to be updated...
            }
    //generation of team textures
    vector<string> textteam=textureteam();
    vector<SDL_Surface*> image1(textteam.size());
    for(int i=0;i<textteam.size();i++)
    {
        if((image1[i] = IMG_Load(textteam[i].c_str())) == NULL) {
            close(image1);
            return 1;}
    }
    //team placement
    std::list <coord> runtime;
    list<org> L;
    int p=0;   
    while(p<textteam.size())
    {
        int i=rand()%map1.size(),j=rand()%map1[0].size();
    if(map1[i][j].gettype()!='W'){
        loadapplySurface(2*i,2*j,image1[p],screen);        
        org temp(i,j);
        temp.setsurf(image1[p]);
        L.push_back(temp);
        coord temp1;
        temp1.i=i;
        temp1.j=j;
        temp1.alive=true;
        runtime.push_back(temp1);
        for(int x=0;x<10;x++)
        {
            int u=(rand()%5)+1, o=(rand()%5)+1;
            loadapplySurface(2*i+u,2*j+o,image1[p],screen);
            org temp(i+u,j+o);
            temp.setsurf(image1[p]);
            L.push_back(temp);
            coord temp1;
            temp1.i=i+u;
            temp1.j=j+o;
            temp1.alive=true;
            runtime.push_back(temp1);
        }
        p++;
        }
    }
    if (SDL_Flip(screen) == -1) 
    {
        close(image);
        return 1;
    }
    //runtime logic
    SDL_Event Events;
    bool Run=true,state=true;
    while(Run)
    {

        list<org>::iterator i;
        for(i=L.begin(); i != L.end(); ++i)
        {
            //look in each direction and if there is it is empty if it is place in runtime que
            isalive((*i).i,(*i).j,&runtime,(info->current_w)/2,(info->current_h)/2);
        }
        SDL_Delay(10000);
        list<coord>::iterator z;
        for(z=runtime.begin(); z != runtime.end(); ++z)
        {
            loadapplySurface(2*(*z).i,2*(*z).j,image1[0],screen);
        }

        state=!state;
        if (SDL_Flip(screen) == -1) 
        {
            close(image);
            return 1;
        }
        while (SDL_PollEvent(&Events))
        {
            if (Events.type == SDL_QUIT)
                Run = false;
        }
    }
    SDL_SaveBMP( screen,"final.BMP" );
    close(image);
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
void isalive(int i, int j, std::list <coord>* runtime, int width, int height)
{
    vector<bool> alive=vector<bool>(8,true);
    list<coord>::iterator p;
    for(p=(*runtime).begin(); p != (*runtime).end(); ++p)
    {
        //i-1 j
        if(i-1==(*p).i&&j==(*p).j)
            alive[0]=false;
        //i-1 j-1
        if(i-1==(*p).i&&j-1==(*p).j)
            alive[1]=false;
        //i j-1
        if(i==(*p).i&&j-1==(*p).j)
            alive[2]=false;
        //i j+1
        if(i==(*p).i&&j+1==(*p).j)
            alive[3]=false;
        //i+1 j+1
        if(i+1==(*p).i&&j+1==(*p).j)
            alive[4]=false;
        //i+1 j
        if(i+1==(*p).i&&j==(*p).j)
            alive[5]=false;
        //i-1 j+1
        if(i-1==(*p).i&&j+1==(*p).j)
            alive[6]=false;
        //i+1 j-1
        if(i+1==(*p).i&&j-1==(*p).j)
            alive[7]=false;
    }
        //i-1 j
        if(alive[0]&&i-1>=0)
        {
        coord temp1;
        temp1.i=i-1;
        temp1.j=j;
        temp1.alive=false;
        (*runtime).push_back(temp1);    
        }
        //i-1 j-1
        if(alive[1]&&i-1>=0&&j-1>=0)
        {
        coord temp1;
        temp1.i=i-1;
        temp1.j=j-1;
        temp1.alive=false;
        (*runtime).push_back(temp1);    
        }
        //i j-1
        if(alive[2]&&j-1>=0)
        {
        coord temp1;
        temp1.i=i;
        temp1.j=j-1;
        temp1.alive=false;
        (*runtime).push_back(temp1);    
        }
        //i j+1
        if(alive[3]&&j+1<width)
        {
        coord temp1;
        temp1.i=i;
        temp1.j=j+1;
        temp1.alive=false;
        (*runtime).push_back(temp1);   
        }
        //i+1 j+1
        if(alive[4]&&j+1<width&&i+1<height)
        {
        coord temp1;
        temp1.i=i+1;
        temp1.j=j+1;
        temp1.alive=false;
        (*runtime).push_back(temp1); 
        }
        //i+1 j
        if(alive[5]&&i+1<height)
        {
        coord temp1;
        temp1.i=i+1;
        temp1.j=j;
        temp1.alive=false;
        (*runtime).push_back(temp1); 
        }
        //i-1 j+1
        if(alive[6]&&i-1>=0&&j+1<width)
        {
        coord temp1;
        temp1.i=i-1;
        temp1.j=j+1;
        temp1.alive=false;
        (*runtime).push_back(temp1); 
        }
        //i+1 j-1
        if(alive[0]&&j-1>=0&&i+1<height)
        {
        coord temp1;
        temp1.i=i+1;
        temp1.j=j-1;
        temp1.alive=false;
        (*runtime).push_back(temp1); 
        }
}