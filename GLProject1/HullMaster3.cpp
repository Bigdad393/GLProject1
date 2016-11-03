/*
  CS 361 
  James Smith
  Project 3 (HullMaster3.cpp) 
*/
//#include "Point3.h"
//#include "Triangle.h"
#include "Hull3q.h"
//#include "Point3.cpp"
//#include "Hull3.cpp"
#include <iostream>

using namespace std;

int main()
{
    int mountianheight=0;
	int cycles=0;
	char question;
    bool range=false;
	bool repeat=true;
	while(repeat)
	{
	  repeat=false;
	  while(!range)
	  {
		while (!range)
		{ 
			mountianheight=69;
		  //cout<<"Enter mountian height 20-100:  ";
		  //cin.clear();
		  //cin >>mountianheight;
		  if (mountianheight <20 || mountianheight > 100)
					{cout<<"Please enter a number between 20 and 100."<<endl;}
		  else
			range=true;
		}
		range=false;
		while (!range)
		{ 
		  cout<<"Enter the number of iterations (ie mountain making loops) (0-10):  ";                                 
		  cin.clear();
		  cin >>cycles;
		  if (cycles <0 || cycles > 10)
					{cout<<"Please enter a number between 0 and 10."<<endl;}
		  else
			range=true;
		}
	  } 
		Hull hl;
		hl.makeHull(mountianheight,cycles);
		cout<<"Build another mountian? (enter y for yes)"<<endl;                                 
		cin.clear();
		cin >>question;
		if (question =='y' || question == 'Y')
		{
			repeat=true;
			range=false;
		}			
		else
			repeat=false;
		
	}
    return 1;
}
