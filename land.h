#ifndef LAND_H
#define LAND_H
 
class land
{
protected:
    float height;
	//for the character association with type:W=deep water w=shallow water s=sand
	//g=grassland h=low hills H=highhills P=peak f=forrest e=eruptive D=deadlands 
	char type,status;
 
public:
    char setheighttype(float);
	char settype(char);
	char gettype();
	char getstatus();
	void setstatus(char);
};
 
#endif