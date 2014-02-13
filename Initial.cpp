#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include "PerlinNoise.h"
#include "land.h"
using namespace std;

std::vector< std::vector< land > > initial(int length, int width){
	float seed,density=0.0000001*length*width;
	Perlin p;
	printf("Seed?\n");
	scanf("%f",&seed);
	//seed is determines the value of the z dimension of noise 
	//need to determine a value in which length and width map to -1 to 1
	float height,min=9999,max=-111111;
	float height1,min1=9999,max1=-111111;
	vector< vector< land > > map1(length,vector< land > (width));
	vector< vector<float> > map(length,vector<float> (width, 0));
	vector< vector<float> > temp1(length,vector<float> (width, 0));
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			height=p.noise((.4+i*density),(.5+j*density),seed)*10+p.noise(2*(.4+i*density),2*(.5+j*density),seed)*5+p.noise(4*(.4+i*density),4*(.5+j*density),seed)*2.5;
			if(height>max)max=height;
			if(height<min)min=height;
			map[i][j]=height;
			height1=(p.noise(i*density,j*density,10*seed)*10);
			if(height1>max1)max1=height1;
			if(height1<min1)min1=height1;
			temp1[i][j]=height1;
		}
	}
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			height=(map[i][j]-min)*(100/(max-min));
			temp1[i][j]=(temp1[i][j]-min1)*(100/(max1-min1));
			if((i<length*.02)||(j<width*.02)||(i>length*.98)||j>width*.98){height=height*.2;}
			map1[i][j].setheighttype(height);
		}
	}

	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
		char type=map1[i][j].gettype();
		//forest generation
		if((type=='g'||type=='h')&&temp1[i][j]<30)
		{
			map1[i][j].settype('f');
		}
		//eruptive generation
		if(type=='P'&&temp1[i][j]>90)
		{
			map1[i][j].settype('e');
		}
		//deadland generation
		if(type!='W'&&temp1[i][j]<47&&temp1[i][j]>50)
		{
			map1[i][j].settype('D');
		}
		}
	}
	return map1;
}

//vector holds all different land texture strings
std::vector<string> textureland(){
vector <string> rtd;

rtd.push_back("textures/darkblue.jpg");
rtd.push_back("textures/lightblue.jpg");
rtd.push_back("textures/sand.jpg");
rtd.push_back("textures/green.jpg");
rtd.push_back("textures/lightbrown.jpg");
rtd.push_back("textures/brown.jpg");
rtd.push_back("textures/grey.jpg");
rtd.push_back("textures/black.jpg");
rtd.push_back("textures/darkgreen.jpg");
rtd.push_back("textures/orange.jpg");
return rtd;
}

//vector holds all different team texture strings
std::vector<string> textureteam(){
	vector <string> rtd;

	rtd.push_back("textures/red.jpg");
	return rtd;
	}