/*
  CS 361 
  James Smith
  Project 3 (Hull3q.h)  
*/
#ifndef HULL3Q_H
#define HULL3Q_H
#include <vector>
#include "Point3.h"
class Hull
{
    public:
		Hull();
		Hull(int);
		void resetVertices(int);
		//void put(int );
		float* getmnt();
        void makeHull(int,int);
		std::vector<Point> vertices;
		std::vector<Point> vertices0;
		std::vector<Point> vertices1;
		std::vector<Point> vertices2;
		std::vector<Point> vertices3;
		std::vector<Point> vertices4;
		std::vector<Point> vertices5;
		std::vector<Point> vertices6;
		std::vector<float> UVs;
		std::vector<float> UVs0;
		std::vector<float> UVs1;
		std::vector<float> UVs2;
		std::vector<float> UVs3;
		std::vector<float> UVs4;
		std::vector<float> UVs5;
		std::vector<float> UVs6;
		std::vector<float> mnt;
		friend class Source;
    private:
        int Hullnbr;
		
		
};
#endif   

