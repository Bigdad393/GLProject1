/*
  CS 361 
  James Smith
  Project3 (Point3.h)  
*/
#ifndef POINT3_H
#define POINT3_H
#include <iostream>
class Point
{
      public:
             Point(float, float, float,int, float);
             Point();
             Point(const Point& rhs);//:position(rhs.position){xpos=rhs.xpos;ypos=rhs.ypos;zpos=rhs.zpos;}                                                           
             bool operator == (const Point& rhs)const{return ((xpos == rhs.xpos)&&(ypos == rhs.ypos)&&(zpos == rhs.zpos));}
             bool operator != (const Point& rhs)const{return ((xpos != rhs.xpos)||(ypos != rhs.ypos)||(zpos != rhs.zpos));}
             bool operator< (const Point& rhs){return (xpos < rhs.xpos);}
             Point& operator= (const Point&);
             Point& operator+= (const Point&);
             Point& operator-= (const Point&);
             double midPnt(Point, Point);
             bool operator>(const Point& rhs){return (h > rhs.h);}
			 float distance(const Point&);
			 float getXpos();
			 float getYpos();
			 float getZpos();
			 void setXpos(float);
			 void setYpos(float);
			 void setZpos(float);
			 float distanceL(const Point&,const Point&);
			 float distanceTo(Point,Point,Point);
             void setActive();
             //Point setPoint(double,double,double);
             void displayP();
             void printP(std::ostream&)const;          
             float bad;
			 friend class Quad;
			 friend class Triangle;
             friend class iostream;
             friend class Line;
             friend class Hull;
      private:
		  float xpos;
		  float ypos;
		  float zpos;
		  float h;
              const int position;
			  float active;
			  
              
};             
 
#endif              
