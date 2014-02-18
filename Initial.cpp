#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include "PerlinNoise.h"
#include "land.h"
#include <math.h>
using namespace std;
//prototype
void recursiveremoval(std::vector< std::vector< land > >*,int,int);

std::vector< std::vector< land > > initial(int length, int width){
	float seed,density=0.000000045*length*width;
	Perlin p;
	printf("Seed?\n");
	scanf("%f",&seed);
	//seed is determines the value of the z dimension of noise 
	float height,min=9999,max=-111111;
	float height1,min1=9999,max1=-111111;
	vector< vector< land > > map1(length,vector< land > (width));
	vector< vector<float> > map(length,vector<float> (width, 0));
	vector< vector<float> > temp1(length,vector<float> (width, 0));
	//noise generation algorithm |noise(p)|+|noise(2p))/2+...
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			height=0;
			for(float w=1;w<6;w++)
				height+=fabs(p.noise((.4+i*density)*w,(.5+j*density)*w,seed))*(10/w);
			if(height>max)max=height;
			if(height<min)min=height;
			map[i][j]=height;
			height1=(p.noise(i*density,j*density,10*seed)*10);
			if(height1>max1)max1=height1;
			if(height1<min1)min1=height1;
			temp1[i][j]=height1;
		}
	}
	//boundrey water generation and normalization
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			height=(map[i][j]-min)*(100/(max-min));
			temp1[i][j]=(temp1[i][j]-min1)*(100/(max1-min1));
			//just cut off the block edge
			//if((i<length*.02)||(j<width*.02)||(i>length*.98)||j>width*.98){height=height*.2;}
			

			map1[i][j].setheighttype(height);
		}
	}

	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
		char type=map1[i][j].gettype();
		//forest generation
		if((type=='g')&&temp1[i][j]<30)
		{
			map1[i][j].settype('f');
		}
		//eruptive generation
		else if(type=='P'&&temp1[i][j]>90)
		{
			map1[i][j].settype('e');
		}
		//deadland generation
		if(type!='W'&&temp1[i][j]<47&&temp1[i][j]>50)
		{
			map1[i][j].settype('D');
		}
		if((i==0||j==0||j==width||i==length)&& map1[i][j].gettype()!='W'&&map1[i][j].gettype()!='s')
		{
			recursiveremoval(&map1,i,j);
		}
		}
	}
	return map1;
}
//recursive algorithm for watering land near the edge of map
void recursiveremoval(std::vector< std::vector< land > > * map1,int i,int j)
{
	printf("%d,%d\n",i,j);
	char current=(*map1)[i][j].gettype();
	printf("%c",current);
	(*map1)[i][j].settype('W');
	printf("%c", (*map1)[i][j].gettype());
	if(i>0&& (*map1)[i-1][j].gettype()==current)
		recursiveremoval(map1,i-1,j);
	if(i< (*map1).size()-1&& (*map1)[i+1][j].gettype()==current)
		recursiveremoval(map1,i+1,j);
	if(j< (*map1)[0].size()-1&& (*map1)[i][j+1].gettype()==current)
		recursiveremoval(map1,i,j+1);
	if(j>0&& (*map1)[i][j-1].gettype()==current)
		recursiveremoval(map1,i,j-1);
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