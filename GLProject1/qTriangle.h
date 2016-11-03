/*
  CS 361 
  James Smith
  Project 3 (qTriangle.h)  
*/
#ifndef qTRIANGLE_H
#define qTRIANGLE_H
#include "line3.h"
#include <random>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
class Triangle
{
    public:
             Triangle(Point,Point,Point);
             Triangle();
             bool operator == (const Triangle& rhs)const{return (pntA == rhs.pntA && pntB == rhs.pntB && pntC == rhs.pntC);}
             bool operator< (const Triangle& rhs){return (area<rhs.area);}
             Triangle& operator= (const Triangle&);
             Point getCenter();           
			 void printT(std::ostream&);
			 void printTgl(std::ostream&);
			 void displayL();
			 Point Triangle::getNormal();
			 friend class Point;
             friend class Hull;
             friend class Line;
             friend class iostream;
      private:
             Line AB;
             Line BC;
             Line AC;
             Point pntA;
             Point pntB;
             Point pntC;
             Point ctr;
			 float area;
};
#endif 
   
Triangle::Triangle(Point a,Point b,Point c)
{ 
    pntA=a;
    pntB=b;
    pntC=c;
    AB.pnt1=pntA;AB.pnt2=pntB;
    BC.pnt1=pntB;BC.pnt2=pntC;
    AC.pnt1=pntA;AC.pnt2=pntC;
    ctr=getCenter();
	area = 0.0;
}
Triangle::Triangle()
{
    pntA;
    pntB;
    pntC;
	area = 0.0;
}  
void Triangle::printT(std::ostream& fout2)
{
	fout2 << (pntA.xpos / 20) - 2 << "  " << (pntA.zpos / 20) - 1 << "  " << (pntA.ypos / 20) + 0 << std::endl
		  << (pntB.xpos / 20) - 2 << "  " << (pntB.zpos / 20) - 1 << "  " << (pntB.ypos / 20) + 0 << std::endl
		  << (pntC.xpos / 20) - 2 << "  " << (pntC.zpos / 20) - 1 << "  " << (pntC.ypos / 20) + 0 << std::endl;
        //<<pntA.xpos<<"  "<<pntA.ypos<<"  "<<pntA.zpos<<std::endl;
}
void Triangle::printTgl(std::ostream& fout2)
{
	fout2 << pntA.xpos << "f, " << pntA.ypos << "f, " << pntA.zpos << "f, "
		  << pntB.xpos << "f, " << pntB.ypos << "f, " << pntB.zpos << "f, "
		  << pntC.xpos << "f, " << pntC.ypos << "f, " << pntC.zpos << "f, "
		  << pntA.xpos << "f, " << pntA.ypos << "f, " << pntA.zpos << "f, ";
}
Triangle& Triangle::operator= (const Triangle& rhs)
{
	pntA=rhs.pntA;
	pntB=rhs.pntB;
	pntC=rhs.pntC;
	AB=rhs.AB;
	BC=rhs.BC;
	AC=rhs.AC;
    return *this;
}
Point Triangle::getCenter()
{
	float g=0.0;
   	std::mt19937 eng;
	eng.seed((unsigned int)time(NULL));

	float rnd=10;
    rnd= rnd/1.5;
	std::normal_distribution<float> dis(0, .2);
	g=  dis(eng)*rnd;

	float x=0.0;
	float y=0.0;
	float z=0.0;
	float h=0.0;
    int p=0;
    x= (pntA.xpos+pntB.xpos+pntC.xpos)/3;
    y= (pntA.ypos+pntB.ypos+pntC.ypos)/3;
    z= (pntA.zpos+pntB.zpos+pntC.zpos)/3;
    if(x>80&&y>70&&y<90)
	{
		x+= 8+fabs(g);
		y+=g/2;
		z+=g;
	}
	else if(x<80&&y>70&&y<90)
	{
		x-= 8+fabs(g);
		y+=g/2;
		z+=g;
	}
	if(y>80&&x>70&&x<90)
	{
		y+= 4+(g);
		x+=g/2;
		z+=g;
	}
	else if(y<80&&x>70&&x<90)
	{
		y-= 8+fabs(g);
		x+=g/2;
		z+=g;
	}
    Point apnt(x,y,z,p,h);
    return apnt;
}
void Triangle::displayL()
{
	std::cout<<"pntA is "<<pntA.xpos<<", "<<pntA.ypos<<", "<<pntA.zpos<<std::endl
			 <<"pntB is "<<pntB.xpos<<", "<<pntB.ypos<<", "<<pntB.zpos<<std::endl
			 <<"pntC is "<<pntC.xpos<<", "<<pntC.ypos<<", "<<pntC.zpos<<std::endl;
}
Point Triangle::getNormal()//the normal projection 
{
	double ax, bx, cx, ay, by, cy, az, bz, cz, nx, ny, nz, N, h;
	int p = 0;
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
