/*
  CS 361
  James Smith
  Project 3 (Line3.cpp)
*/
#include "Line3.h"
#include <random>
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
Line::Line(Point a,Point b)
{
    //xpos1=a.xpos;ypos1=a.ypos;xpos2=b.xpos;ypos2=b.ypos;
    pnt1=a;
    pnt2=b;
    //this->setMidpoint();
}
Line::Line()
{
    pnt1;
    pnt2;
}
void Line::printL(std::ostream& fout)
{
    fout<<pnt1.xpos<<"  "<<pnt1.ypos<<"  "<<pnt1.zpos<<std::endl;
    fout<<pnt2.xpos<<"  "<<pnt2.ypos<<"  "<<pnt2.zpos<<std::endl;
}
Line& Line::operator= (const Line& rhs)
{
    pnt1=rhs.pnt1;
    pnt2=rhs.pnt2;
	return *this;
}


Point Line::getMidpoint(int cycle)
{
	float rnd=(pnt1.distance(pnt2))/4;
	float rng= rnd*2;
	int c=4;//6-(cycle);
	rnd= (rnd/c)*.3;
	float g= 0.0;
	//std::mt19937 eng;
	//eng.seed((unsigned int)time(NULL));
	//std::uniform_real_distribution<double> dis(0, rng);
	float pii=3.1415927;
	float r_max=RAND_MAX+1;
	g= rnd*sqrt(-2*log((rand()+1)/r_max))*sin(2*pii*rand()/r_max)+1;
	if(cycle>4)
		g=g/cycle;
	if(g>rng)
	{
		g=rng;
	}
	if(g<-rng)
	{
		g= -rng;
	}

	float x=0.0;
	float y=0.0;
	float z=0.0;

	x=(pnt1.xpos+pnt2.xpos)/2;
	y=(pnt1.ypos+pnt2.ypos)/2;
	z=(pnt1.zpos+pnt2.zpos)/2;
	//if (x < 80 && x>40 && y < 80 && y>40)
		//cout << "x is " << x << ", y is " << y << ",  g is " << g << endl;
	if(!((pnt1.zpos==0)&&(pnt2.zpos==0)))
	{
		if(cycle>0)
		{
			if(x>80&&y<80)
			{
				x+= g*(8 / (cycle + 2));
				y-= g*(7 / (cycle + 2));
				z+=g;
			}
			else if(x>80&&y>80)
			{
				x+= g*(8 / (cycle + 2));
				y+= g*(7 / (cycle + 2));
				z+=g;
			}
			if(x<80&&y>80)
			{
				y+= g*(8 / (cycle + 2));
				x-= g*(7 / (cycle + 2));
				z+=g;
			}
				else if(x<80&&y<80)
				{
					y-= g*(8 / (cycle + 2));
					x-= g*(7 / (cycle + 2));
					z+=g;
				}
		}
		else
		{
			x+=g;//-(rng/2);
			y+=g;//-(rng/2);
			z+=g;//-(rng/2);
		}
	}
	else
	{
		if(x>80)
			x+=fabs(g)*(8/cycle);//-(rng/2);
		else if(x<=80)
			x-=fabs(g)*(8/cycle);//-(rng/2);
		else
			x+=g;
		if (y>80)
			y+=fabs(g)*(8/cycle);//-(rng/2);
		else if(y<=80)
			y-=fabs(g)*(8/cycle);//-(rng/2);
		else
			y+=g;
	}
	midpoint.xpos=x;
	midpoint.ypos=y;
	midpoint.zpos=z;
	return midpoint;
}

