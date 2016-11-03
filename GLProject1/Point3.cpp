/*
  CS 361
  James Smith
  Project 3 (Point3.cpp)  
*/
#include "Point3.h"
#include "cmath"
Point::Point(float x, float y, float z,int p, float nh):position(p)
{     
     xpos=x;
     ypos=y;
     zpos=z;
     //position=p;
     h=nh;
     active= false;
     bad=false;
}
Point::Point():xpos(0.0),ypos(0.0),zpos(0.0),position(0)                                              
{h=0.0;active= false;bad=true;}

Point::Point(const Point& rhs):position(rhs.position)
{
    xpos=rhs.xpos;
    ypos=rhs.ypos;
    zpos=rhs.zpos;
	active = rhs.active;
	bad = rhs.bad;
    h=rhs.h;
}                                                           
double Point::midPnt(Point pa, Point pb)
{
	float ax,ay,az,bx,by,bz,nx,ny,nz,md;
    ax=pa.xpos;ay=pa.ypos;az=pa.zpos;
    bx=pb.xpos;by=pb.ypos;bz=pb.zpos;
    nx=(ax+bx)/2;
    ny=(ay+by)/2;
    nz=(az+bz)/2;
    Point mid= Point(nx,ny,nz,1,-1);
    md=distance(mid);
    return md;
}
float Point::getXpos()
{
	return xpos;
}
float Point::getYpos()
{
	return ypos;
}
float Point::getZpos()
{
	return zpos;
}
void Point::setXpos(float x)
{
	xpos=x;
}
void Point::setYpos(float y)
{
	ypos=y;
}
void Point::setZpos(float z)
{
	zpos=z;
}

                 
float Point::distanceTo(Point pntA,Point pntB,Point pntC)//h is the distance from this point to plane A,B,C
{
    float ht,ax,ay,az,bx,by,bz,cx,cy,cz,nx,ny,nz,N;
    bx=(pntB.xpos-pntA.xpos);
    by=(pntB.ypos-pntA.ypos);
    bz=(pntB.zpos-pntA.zpos);
    cx=(pntC.xpos-pntA.xpos);
    cy=(pntC.ypos-pntA.ypos);
    cz=(pntC.zpos-pntA.zpos);    
    ax=pntA.xpos;
    ay=pntA.ypos;
    az=pntA.zpos;
    nx=((by*cz)-(bz*cy));
    ny=((bz*cx)-(bx*cz));
    nz=((bx*cy)-(by*cx));    
    //N=sqrt((nx)*(nx)+(ny)*(ny)+(nz)*(nz));
    //nx=nx/N;ny=ny/N;nz=nz/N;
    ht=((((nx*xpos+ny*ypos+nz*zpos)-nx*ax-ny*ay-nz*az))/sqrt(nx*nx+ny*ny+nz*nz));    
    return ht;   
}
float Point::distance(const Point& pnt)//point to point distance
{
	float x,y,z;
    x=xpos-pnt.xpos;
    y=ypos-pnt.ypos;
    z=zpos-pnt.zpos;
    return (sqrt(x*x+y*y+z*z));
}
float Point::distanceL(const Point& rhs,const Point& lhs)//point to line segment distance
{
	float x,y,z,x1,y1,z1,i,j,k,d;
    x1=lhs.xpos-rhs.xpos;
    y1=lhs.ypos-rhs.ypos;
    z1=lhs.zpos-rhs.zpos;
    x=xpos-rhs.xpos;
    y=ypos-rhs.ypos;
    z=zpos-rhs.zpos;
    i=y1*z-y*z1;
    j=x1*z-x*z1;
    k=x1*y-x*y1;
    d=(sqrt(i*i+j*j+k*k))/(sqrt(x1*x1+y1*y1+z1*z1));
    
    return d;
}                         
void Point::printP(std::ostream& fout) const
{
     fout<<xpos<<"   "<<ypos<<"   "<<zpos<<std::endl;
}
void Point::displayP()
{
    std::cout<<xpos<<"	 "<<ypos<<"	  "<<zpos<<std::endl;//<<"poisition is "<<position
            //<<std::endl;
}
Point& Point::operator= (const Point& rhs)
{
     xpos=rhs.xpos;
     ypos=rhs.ypos;
     zpos=rhs.zpos;
     h=rhs.h;
     active=rhs.active;
     bad=rhs.bad;
    
	 return *this;
}
Point& Point::operator+= (const Point& rhs)
{
    xpos+=rhs.xpos;
     ypos+=rhs.ypos;
     zpos+=rhs.zpos;
    
     return *this;
}
Point& Point::operator-= (const Point& rhs)
{
     xpos-=rhs.xpos;
     ypos-=rhs.ypos;
     zpos-=rhs.zpos;
    
     return *this;
}
void Point::setActive()
{
    active=true;
}             
