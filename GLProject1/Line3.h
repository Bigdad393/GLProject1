/*
  CS 361
  James Smith
  Project 3 (Line3.h)
*/
#ifndef LINE3_H
#define LINE3_H
#include <random>
#include <iostream>
#include <ctime>
//#include <iostream>
#include "Point3.h"
class Line
{
      public:
             Line(Point,Point);
             Line();
             bool operator == (const Line& rhs)const{return ((pnt1==rhs.pnt1&&pnt2==rhs.pnt2)||(pnt1==rhs.pnt2&&pnt2==rhs.pnt1));}
             bool operator< (const Line& rhs){return (xpos2 < rhs.xpos2 && ypos2<rhs.ypos2 && zpos2<rhs.zpos2);}
             Line& operator= (const Line&);
			 Point getMidpoint(int);
			
             void printL(std::ostream&);


			 friend class Point;
             friend class Hull;
             friend class Triangle;
             friend class Quad;
             friend class iostream;
      private:
             Point pnt1;
             Point pnt2;
             Point midpoint;
			 float xpos1;
			 float ypos1;
			 float zpos1;
			 float xpos2;
			 float ypos2;
			 float zpos2;
};

#endif

