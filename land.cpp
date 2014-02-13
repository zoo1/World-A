#include "land.h"
char land::setheighttype(float in){
	height=in;
	if(height<20){return(type='W');}
	else if(28>height&&height>20){return(type='w');}
	else if(28<height&&height<36){return(type='s');}
	else if(36<height&&height<51){return(type='g');}
	else if(51<height&&height<71){return(type='h');}
	else if(71<height&&height<91){return(type='H');}
	else if(91<height){return(type='P');}
}
char land::settype(char in){
	return(type=in);
}
char land::gettype(){return(type);}
char land::getstatus(){return(status);}
void land::setstatus(char in){
	status=in;
}