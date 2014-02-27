#include "org.h"
org::org(int x, int y) {
	i=x;
	j=y;
}
void org::setsurf(SDL_Surface* in){
surf=in;
}
SDL_Surface* org::getsurf(){
return surf;
}