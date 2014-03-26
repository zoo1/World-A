#include <vector>
#include <stdio.h>
#include "PerlinNoise.h"
#include "land.h"
#include <math.h>

using namespace std;
//current magic numbers:
static const float DMULT=9000;
static const float XNOISE=.4, YNOISE=.5;

std::vector< std::vector< land > > initial(int length, int width,float seed){
	//9000 magic number
	float density=DMULT*(1/float(length))*(1/float(width)),cutoff=sqrtf(powf(length,2)+powf(width,2))*.2;
	Perlin p;
	//seed is determines the value of the z dimension of noise 
	float height,min=9999,max=-111111;
	float height1,min1=9999,max1=-111111;
	vector< vector< land > > map1(length,vector< land > (width));
	vector< vector<float> > temp(length,vector<float> (width, 0));
	vector< vector<float> > temp1(length,vector<float> (width, 0));
	//noise generation algorithm |noise(p)|+|noise(2p))/2+...
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			height=0;
			for(float w=1;w<9;w++)
				//also has a magic number:.4 and .5
				height+=fabs(p.noise((XNOISE+i*density)*w,(YNOISE+j*density)*w,seed))*(10/w);
			if(height>max)max=height;
			if(height<min)min=height;
			temp[i][j]=height;
			height1=(p.noise(i*density,j*density,10*seed)*10);
			if(height1>max1)max1=height1;
			if(height1<min1)min1=height1;
			temp1[i][j]=height1;
		}
	}
	//boundry water generation and normalization
	float multiplier,current;
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<width;j++)
		{
			current=sqrtf(powf(fabs((length/2)-(float)i),2)+powf(fabs((width/2)-(float)j),2));
			multiplier=1;
			if(cutoff<current)
			{
				multiplier=1-(current-cutoff)*.025;
				if(multiplier<0)
					multiplier=0;
			}
			height=multiplier*(temp[i][j]-min)*(100/(max-min));
			temp1[i][j]=(temp1[i][j]-min1)*(100/(max1-min1));
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
		}
	}
	return map1;
}