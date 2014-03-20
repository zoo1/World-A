#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <list>
#include <stdio.h>
#include "Util.h"
#include "Init.h"
#include "org.h"
using namespace std;

// Globals:
SDL_Surface* screen = NULL; //screen surface

int main(int argc, char* argv[]) {
    if(!init())exit(1);
    //reads the info of the window
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
	int sc_width = info->current_w, sc_height = info->current_h;
	vector< vector< land > > map1=initial((info->current_w)*2,(info->current_h)*2);
    //loads the texture images we will be using
    vector<string> textland=textureland();
    vector<SDL_Surface*> image(textland.size());
    for(int i=0;i<textland.size();i++)
    {
        if((image[i] = SDL_LoadBMP(textland[i].c_str())) == NULL) {
            close(image);
            return 1;
        }
    }
        
    for(int i=0;i<map1.size();i++)
    {
        for(int j=0;j<map1[0].size();j++)
        {
            switch(map1[i][j].gettype())
            {
            case 'W':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[0],screen);
                map1[i][j].setsurf(image[0]);
                break;
            case 'w':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[1],screen);
                map1[i][j].setsurf(image[1]);
                break;
            case 's':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[2],screen);
                map1[i][j].setsurf(image[2]);
                break;
            case 'g':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[3],screen);
                map1[i][j].setsurf(image[3]);
                break;
            case 'h':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[4],screen);
                map1[i][j].setsurf(image[4]);
                break;
            case 'H':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[5],screen);
                map1[i][j].setsurf(image[5]);
                break;
            case 'P':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[6],screen);
                map1[i][j].setsurf(image[6]);
                break;
            case 'D':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[7],screen);
                map1[i][j].setsurf(image[7]);
                break;
            case 'f':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[8],screen);
                map1[i][j].setsurf(image[8]);
                break;
            case 'e':
                if(i%4==0&&j%4==0)
                    loadapplySurface(i/2,j/2,image[9],screen);
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
    list<org> L;
    int p=0,count=0;   
    while(p<textteam.size())
    {
        int i=rand()%map1.size(),j=rand()%map1[0].size();
    if(map1[i][j].gettype()!='W'){
        loadapplySurface(i/2,j/2,image1[p],screen);        
        org temp(i,j);
        temp.setsurf(image1[p]);
        L.push_back(temp);
        if(count==5)
            {
                count=0;
                p++;
            }
        count++;
        }
    }
    if (SDL_Flip(screen) == -1) 
    {
        close(image);
        return 1;
    }
    //runtime logic
    SDL_Event Events;
    bool Run=true;
    while(Run)
    {

        list<org>::iterator i;
        for(i=L.begin(); i != L.end(); ++i)
        {
            
        }
        //run game of life logic
        SDL_Delay(1000);
        list<org> tempL;
        
        L=tempL;
        if (SDL_Flip(screen) == -1) 
        {
            close(image);
            return 1;
        }
        while (SDL_PollEvent(&Events))
        {
            switch(Events.type) {
                case SDL_QUIT:
                    Run = false;
                    break;
                case SDL_KEYDOWN:
                    switch( Events.key.keysym.sym ) { 
                        case SDLK_1:
                            zoom(true,map1);
                            break;
                        case SDLK_2:
                            zoom(false,map1);
                            break;
                        case SDLK_UP: 
                            slide('u',map1);
                            break; 
                        case SDLK_DOWN: 
                            slide('d',map1); 
                            break; 
                        case SDLK_LEFT:
                            slide('l',map1);
                            break; 
                        case SDLK_RIGHT: 
                            slide('r',map1);
                            break; 
                        default:;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch( Events.button.button){
                        case SDL_BUTTON_WHEELUP:
                            printf("scrollin\n");
                            zoom(true,map1);
                            break;
                        case SDL_BUTTON_WHEELDOWN:
                            printf("scrollout\n");
                            zoom(false,map1);
                            break; 
                    }
                    break;
                default:;
            }
        }
    }
    SDL_SaveBMP( screen,"final.BMP" );
    close(image);
    return 0;
 }
