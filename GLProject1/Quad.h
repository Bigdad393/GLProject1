/*
  CS 361 Spring 2013, Professor Morris
  James Smith
  Project 3 (Quad.h)  
*/
#ifndef Quad_H
#define Quad_H
#include "Hull3q.h"
#include "Line3.h"
#include "Point3.h"
#include <random>
#include <cmath>
#include <ctime>
class Quad
{
    public:
             Quad(Point,Point,Point,Point);
             Quad();
             bool operator == (const Quad& rhs)const{return (pntA == rhs.pntA && pntB == rhs.pntB && pntC == rhs.pntC && pntD == rhs.pntD);}
             bool operator< (const Quad& rhs){return (pntA < rhs.pntA);}
             Quad& operator= (const Quad&);
             Point getCenter(int);
			 Point getNormal();
             double shortSide();          
             void printQuad(std::ostream&);
             void displayQuad();
             void setNumber(int);
			 int  getNumber();

			 friend class Point;
             friend class Hull;
             friend class Line;
             friend class iostream;
      private:
             Line lineAB;
             Line lineBC;
             Line lineCD;
             Line lineAD;
             Point pntA;
             Point pntB;
             Point pntC;
             Point pntD;
			 Point pntRight;
			 Point pntLeft;
			 Point pntTop;
			 Point pntBase;
			 int num;
			 int rightn;
			 int leftn;
			 int topn;
			 int basen;
			 
             //string path;
};
#endif 
   
Quad::Quad(Point a,Point b,Point c,Point d)
{ 
    pntA=a;
    pntB=b;
    pntC=c;
    pntD=d;
    lineAB.pnt1=pntA;
	lineAB.pnt2=pntB;
    lineBC.pnt1=pntB;
	lineBC.pnt2=pntC;
    lineCD.pnt1=pntC;
	lineCD.pnt2=pntD;
    lineAD.pnt1=pntA;
	lineAD.pnt2=pntD;
}

Quad::Quad()
{
    pntA;
    pntB;
    pntC;
    pntD;
    num=0;
}

void Quad::setNumber(int number)
{
	num= number;
}
int Quad::getNumber()
{
	return num;
}
void Quad::printQuad(std::ostream& fout)
{
   fout<<pntA.xpos<<"  "<<pntA.ypos<<"  "<<pntA.zpos<<std::endl
        <<pntB.xpos<<"  "<<pntB.ypos<<"  "<<pntB.zpos<<std::endl
        <<pntC.xpos<<"  "<<pntC.ypos<<"  "<<pntC.zpos<<std::endl
        <<pntD.xpos<<"  "<<pntD.ypos<<"  "<<pntD.zpos<<std::endl
        <<pntA.xpos<<"  "<<pntA.ypos<<"  "<<pntA.zpos<<std::endl<<std::endl<<std::endl;
}

Quad& Quad::operator= (const Quad& rhs)
{
	pntA=rhs.pntA;
	pntB=rhs.pntB;
	pntC=rhs.pntC;
	pntD=rhs.pntD;
	lineAB=rhs.lineAB;
	lineBC=rhs.lineBC;
	lineCD=rhs.lineCD;
	lineAD=rhs.lineAD;
	num=rhs.num;
    return *this;
}

Point Quad::getCenter(int cycle)
{
    double h=0.0;
	int c=1.5-(cycle*.1);

    double g=0.0;
   	int p=0;
   	std::mt19937 eng;
	eng.seed((unsigned int)time(NULL));

	double rnd=((this->shortSide())/2);
	double rng= rnd;
    rnd= (rnd)*.1;
	double pii=3.1415927;
  	double r_max=RAND_MAX+1;
  	g= rnd*sqrt(-2*log((rand()+1)/r_max))*sin(2*pii*rand()/r_max)+1; //rnd*rand()/r_max;
	if(cycle>4)
		g=g*(1/cycle);
	
    double x=0.0;
	double y=0.0;
	double z=0.0;
	x= (pntA.xpos+ pntB.xpos+ pntC.xpos+ pntD.xpos)/4;
    y= (pntA.ypos+ pntB.ypos+ pntC.ypos+ pntD.ypos)/4;
    z= (pntA.zpos+ pntB.zpos+ pntC.zpos+ pntD.zpos)/4;
    if(g>rng)
    {
    	g=rng;
    }
 /*   if(cycle==2)
    {
    	//std::cout<<" g = "<<g<<std::endl;
    	if(x>85&&y>75&&y<85)
    	{
    		x+= 1+g;
    		y+=1/4;
    		z+=g;
    	}
    	else if(x<=75&&y>75&&y<85)
    	{
    		x-= 1+g;
    		y+=1/4;
    		z+=g;
    	}
		if(y>85&&x>75&&x<85)
    	{
    		y+= 1+g;
    		x+=1/4;
    		z+=g;
    	}
    	else if(y<=75&&x>75&&x<85)
    	{
    		y-= 1+g;
    		x+=1/4;
    		z+=g;
    	}
		//z+= 1+g;
	}
	
	else if(cycle==2)
    {
    	if(x>50 && z<40)
    		x+= 1+g;
    	else if(x<50 && z<40)
    		x-= 1+g;
		if(y>50 && z<40)	
			y+= 1+g;
		else if(y<50 && z<40)
			y-= 1+g;
		z+= g;//z+= g+1;
	}
	else if(cycle==3)
    {
    	if(x>50 && z<40)
    		x+= .5+g;
    	else if(x<50 && z<40)
    		x-= .5+g;
		if(y>50 && z<40)	
			y+= .5+g;
		else if(y<50 && z<40)
			y-= .5+g;
		z+= g;//z+= g+.5;
	}*/
	
	//else
	//{
		x+= g;
		y+= g;//-rng/2;
		z+= g;//-rng/2;
	//}
	h=0.0;
    Point apnt(x,y,z,p,h);
    return apnt;
}

void Quad::displayQuad()
{
	std::cout<<"pntA is "<<pntA.xpos<<", "<<pntA.ypos<<", "<<pntA.zpos<<std::endl
        <<"pntB is "<<pntB.xpos<<", "<<pntB.ypos<<", "<<pntB.zpos<<std::endl
		<<"pntC is "<<pntC.xpos<<", "<<pntC.ypos<<", "<<pntC.zpos<<std::endl
        <<"pntD is "<<pntD.xpos<<", "<<pntD.ypos<<", "<<pntD.zpos<<std::endl;
}
//return the length of the shortest side
double Quad::shortSide()
{
    double alth=0.0;
	double blth=0.0;
	double clth=0.0;
	double dlth=0.0;
	double x=0.0;
	double y=0.0;
	double z=0.0;

	x=pntA.xpos-pntB.xpos;
    y=pntA.ypos-pntB.ypos;
    z=pntA.zpos-pntB.zpos;
    alth= sqrt((x*x)+(y*y)+(z*z));
    x=pntB.xpos-pntC.xpos;
    y=pntB.ypos-pntC.ypos;
    z=pntB.zpos-pntC.zpos;
    blth= sqrt((x*x)+(y*y)+(z*z));
    x=pntC.xpos-pntD.xpos;
    y=pntC.ypos-pntD.ypos;
    z=pntC.zpos-pntD.zpos;
    clth= sqrt((x*x)+(y*y)+(z*z));
    x=pntA.xpos-pntD.xpos;
    y=pntA.ypos-pntD.ypos;
    z=pntA.zpos-pntD.zpos;
    dlth= sqrt((x*x)+(y*y)+(z*z));
    if(alth<blth && alth<clth && alth<dlth)
        return (alth);
    else if(blth<alth &&  blth<clth && blth<dlth)
        return (blth);
    else if(clth<alth &&  blth>clth && clth<dlth)
        return (clth);
    else
        return (dlth);
}    
Point Quad::getNormal()
{
	double ax, bx, cx, ay, by, cy, az, bz, cz, nx, ny, nz, N, h;
	int p = this->getNumber();
	h = 0.0;
	bx = (pntB.xpos - pntA.xpos);
	by = (pntB.ypos - pntA.ypos);
	bz = (pntB.zpos - pntA.zpos);
	cx = (pntC.xpos - pntA.xpos);
	cy = (pntC.ypos - pntA.ypos);
	cz = (pntC.zpos - pntA.zpos);
	ax = pntA.xpos;
	ay = pntA.ypos;
	az = pntA.zpos;
	nx = ((by*cz) - (bz*cy));
	ny = ((bz*cx) - (bx*cz));
	nz = ((bx*cy) - (by*cx));
	N = sqrt((nx)*(nx)+(ny)*(ny)+(nz)*(nz));
	//xang = (acos(nx / N) * 180 / 3.1416);
	//yang = (acos(ny / N) * 180 / 3.1416);
	//zang = (acos(nz / N) * 180 / 3.1416);
	Point normpt(nx / N, ny / N, nz / N, p, h);
	//orthonorm = (normpt);
	//if (nz / N <.3)                                                                //projection on z axis
	//	dead = true;
	//else
	//	dead = false;
	return (normpt);
}