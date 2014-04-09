#include <iostream>
#include <string>
#include <vector>
#include "land.h"
#include "Util.h"
#include <SDL_ttf.h>


using namespace std;
//From main:
extern SDL_Surface* screen;
// Globals:
static TTF_Font *font;
static SDL_Color textColor = { 111, 255, 255 };
static int z=1; //current zoom level
static int screeny=1300,screenx=714;//screen position related to zoom
static const int sc_bpp = 32;  // Bits per pixel.

//seed screen that asks for the users seed

int seed()
{
    //Initial method
    SDL_Surface *message = TTF_RenderText_Blended( font, "From ZOO, Welcome to this little game I am developing. There is currently a lot that need to be worked on.", textColor );
    loadapplySurface( 0, 100, message, screen ); 
    message = TTF_RenderText_Blended( font, "Please enter the seed you want to use to generate the game(between 1 and 11 digits please).", textColor );
    loadapplySurface( 0, 150, message, screen );
    message = TTF_RenderText_Blended( font, "Seed:", textColor );
    loadapplySurface( 0, 200, message, screen );
    //allow the user to exit or to place the seed in starting the game
    char seedarray[11]="0";
    int seed=0;
    int currentplace=0;
    SDL_Event Events;
    message = TTF_RenderText_Blended( font, seedarray, textColor );
    loadapplySurface( 70, 200, message, screen );
    if(SDL_Flip( screen )==-1)
    {
    TTF_Quit();
    SDL_Quit();
    return -1;
    }
    SDL_Surface* blackscreen = SDL_CreateRGBSurface(0,200,100,32,0,0,0,0);
    while(true)
    {
        while (SDL_PollEvent(&Events))
        {
            switch(Events.type) {
                case SDL_QUIT:
                    TTF_Quit();
                    SDL_Quit();
                    return -1;
                case SDL_KEYDOWN:
                    switch( Events.key.keysym.sym ) { 
                        case SDLK_1:
                            if(currentplace<11)
                                seedarray[currentplace++]='1';
                            break;
                        case SDLK_2:
                            if(currentplace<11)
                                seedarray[currentplace++]='2';
                            break;
                        case SDLK_3:
                            if(currentplace<11)
                                seedarray[currentplace++]='3';
                            break;
                        case SDLK_4:
                            if(currentplace<11)
                                seedarray[currentplace++]='4';
                            break;
                        case SDLK_5:
                            if(currentplace<11)
                                seedarray[currentplace++]='5';
                            break;
                        case SDLK_6:
                            if(currentplace<11)
                                seedarray[currentplace++]='6';
                            break;
                        case SDLK_7:
                            if(currentplace<11)
                                seedarray[currentplace++]='7';
                            break;
                        case SDLK_8:
                            if(currentplace<11)
                                seedarray[currentplace++]='8';
                            break;
                        case SDLK_9:
                            if(currentplace<11)
                                seedarray[currentplace++]='9';
                            break;
                        case SDLK_0:
                            if(currentplace<11)
                                seedarray[currentplace++]='0';
                            break;
                        case SDLK_BACKSPACE:
                            //remove a char value
                            if(currentplace)
                                seedarray[--currentplace]=' ';
                            break;
                        case SDLK_RETURN:
                            //convert char array into return value
                            int i=0,holder,expe;
                            currentplace--;
                            for(;currentplace>-1;currentplace--)
                            {
                                
                                switch(seedarray[currentplace]){
                                    case '1':
                                        holder=1;
                                        break;
                                    case '2':
                                        holder=2;
                                        break;
                                    case '3':
                                        holder=3;
                                        break;
                                    case '4':
                                        holder=4;
                                        break;
                                    case '5':
                                        holder=5;
                                        break;
                                    case '6':
                                        holder=6;
                                        break;
                                    case '7':
                                        holder=7;
                                        break;
                                    case '8':
                                        holder=8;
                                        break;
                                    case '9':
                                        holder=9;
                                        break;
                                    case '0':
                                        holder=0;
                                        break;
                                }
                                expe=1;
                                int ti=i;
                                for(;i!=0;i--)
                                    expe*=10;
                                seed=seed+(holder*expe);
                                i=ti+1;
                            }
                            printf("%d\n",seed);
                            return seed;
                    }
                    SDL_Surface* blackscreen = SDL_CreateRGBSurface(0,200,100,32,0,0,0,0);
                    message = TTF_RenderText_Blended( font, seedarray, textColor );
                    loadapplySurface( 70, 200, blackscreen,screen);
                    loadapplySurface( 70, 200, message, screen );
                    if(SDL_Flip( screen )==-1)
                    {
                        TTF_Quit();
                        SDL_Quit();
                        return -1;
                    }
                }
        }
    }
}
bool init() //creates the sdl Video screen and inits everything
{  

	//Initialize SDL 
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		return false;

	} 
    //set the videomode to screen or a SDL Surface
	screen = SDL_SetVideoMode(1300, 714, sc_bpp, SDL_SWSURFACE);
	if( screen == NULL ) 
    { 
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
        SDL_Quit();
		return false; 
	} 
    //initialize the text creater
    if( TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    //create font
    font = TTF_OpenFont("textures/Quicksand_Bold.ttf", 24);
    if (font == NULL)
    {
        printf("TTF_OpenFont() Failed: %s\n",TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }
	//set the caption of the the window will also set icon image later
	SDL_WM_SetCaption("World-A", "World-A");	 
	return true; 
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

void close(SDL_Surface* freeme[],int i) //ends the SDL program and frees the images
{
    for(int j=0;j<i;j++)
        SDL_FreeSurface(freeme[j]);
	SDL_FreeSurface(screen);
	screen = NULL;
    //Quit TTF subsystems
    TTF_Quit();
	//Quit SDL subsystems 
	SDL_Quit();
}

int zoom(bool inout, vector< vector< land > > *map1)
{
    int originx,originy;
    if(inout)   //zoom in
    {
        switch(z){
            case 1: 
                //if it has not been zoomed in yet set the coords at the center of screen
                if(screeny==-1&&screenx==-1)
                {
                    screeny=(*map1).size()/2;
                    screenx=(*map1)[0].size()/2;
                }
                originx=screenx-(*map1)[0].size()/4;
                originy=screeny-(*map1).size()/4;
                for(int i=0;i<(*map1).size()/2;i++)
                {
                    for(int j=0;j<(*map1)[0].size()/2;j++)
                    {
                      loadapplySurface(i,j,(*map1)[originy+i][originx+j].getsurf(),screen);  
                    }
                }
                z++;
                return 0;
            case 2:
                originx=screenx-(*map1)[0].size()/8;
                originy=screeny-(*map1).size()/8;
                for(int i=0;i<(*map1).size()/2;i++)
                {
                    for(int j=0;j<(*map1)[0].size()/2;j++)
                    {
                      loadapplySurface(2*i,2*j,(*map1)[originy+i][originx+j].getsurf(),screen);  
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
                for(int i=0;i<(*map1).size();i++)
                {
                    for(int j=0;j<(*map1)[0].size();j++)
                    {
                        loadapplySurface(i/2,j/2,(*map1)[i][j].getsurf(),screen);
                    }
                }
                z--;
                return 0;
            case 3:
                //TODO make sure that screeenx and screeny do not lead to accessing arrays out of bounds
                originx=screenx-(*map1)[0].size()/4;
                originy=screeny-(*map1).size()/4;
                for(int i=0;i<(*map1).size()/2;i++)
                {
                    for(int j=0;j<(*map1)[0].size()/2;j++)
                    {
                      loadapplySurface(i,j,(*map1)[originy+i][originx+j].getsurf(),screen);  
                    }
                }   
                z--;
                return 0;
        }
    }
}


int slide(char dir, vector< vector< land > > *map1) //TODO FINISH THIS FUNCTION!!!!
{

    int line;
    switch(dir){
        case 'u'://up
            loadapplySurface(0,1,screen,screen);
            switch(z){
                case 1:
                    cout<<"up\n";
                    int i;
                    line=screeny-(*map1).size()/2;
                    cout<<line<<"\n";
                    if(line<0)
                        line=0;
                    for(i=0;i<(*map1)[0].size();i=i+4)
                    {
                        cout<<"["<<line<<"]["<<i<<(*map1)[line][i].gettype()<<"]\n";
                        loadapplySurface(0,i,(*map1)[line][i].getsurf(),screen);
                    }
                    if(screeny>4)
                        screeny=screeny-4;
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
                    cout<<"down\n";
                    int i;
                    line=screeny+(*map1).size()/2;
                    
                    if(line>=(*map1).size())
                        line=(*map1).size()-1;
                    cout<<line<<"\n";
                    for(i=0;i<(*map1)[0].size();i=i+2)
                        loadapplySurface(0,i,(*map1)[line][i].getsurf(),screen);
                    if((screeny+4)<(*map1).size())
                        screeny=screeny+4;

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