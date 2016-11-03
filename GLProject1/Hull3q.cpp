/*
  James Smith
  Project 3 (Hull3q.cpp)
*/
#include <cstdlib>
#include "Quad.h"
#include "qTriangle.h"
#include "Hull3q.h"
#include "normal.h"
#include <list>
#include <vector>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Point3.h"
using namespace std;
Hull::Hull()
{
}
Hull::Hull(int cycle)
{
	Point p;
	int c = 0;
	int v = 0;
	int v0 = 12;
	int v1 = 72;
	int v2 = 288;
	int v3 = 1152;
	int v4 = 4608;
	int v5 = 18432;
	int v6 = 73728;
	int u = 0;
	int u0 = 24;
	int u1 = 144;
	int u2 = 576;
	int u3 = 2304;
	int u4 = 9216;
	int u5 = 36864;
	int u6 = 147456;
	if (cycle != 0)
	{
		c = (24 * 9 * pow(4, (cycle - 1)));
		u= (24 * 6 * pow(4, (cycle - 1)));
		v= (24 *3*  pow(4, (cycle - 1)));
	}
	else
	{
		c = 36;
		v = 12;
		u = 24;
	}
	cout << "the size of c in hull is " << c << endl << endl;
	for (int g = 0; g < c; g++)
	{
		mnt.push_back(0.0);
	}
	

}
void Hull::resetVertices(int vert)
{
	/**/
	if (vert < 7)
	{
		switch (vert)
		{
		case 0:
			vertices = vertices0;
			UVs = UVs0;
			break;
		case 1:
			vertices = vertices1;
			UVs = UVs1;
			break;
		case 2:
			vertices = vertices2;
			UVs = UVs2;
			break;
		case 3:
			vertices = vertices3;
			UVs = UVs3;
			break;
		case 4:
			vertices = vertices4;
			UVs = UVs4;
			break;
		case 5:
			vertices = vertices5;
			UVs = UVs5;
			break;
		case 6:
			vertices = vertices6;
			UVs = UVs6;
			break;
		}
	}
	else
		vertices = vertices;
}
float* Hull::getmnt()
{
	static const int size = mnt.size();
	float* amnt=NULL;
	amnt = new float[size];

	for (int i = 0; i < size; i++)
	{
		amnt[i] = mnt[i];
	}
	return amnt;
}
void Hull::makeHull(int mountaintop,int cycles)
{
	float x=0.0;
	float y=0.0;
	float z=0.0;
	float maxX = 0.1;
	float maxY = 0.1;
    Point pnt1,pnt2,pnt3,pnt4,pntA,pntB,pntC,pntD,cpnt,ctr;
    Point rightpnt,leftpnt,basepnt,toppnt,endleftpnt;
    Line baseline;
    Line topline;
    Line rightline;
    Line leftline;
    Quad* pQd;
    Triangle* tri1;
    
    srand(time(0));
	float rnd=50.0;
	float pii=3.1415927;
	float r_max=RAND_MAX+1;
	vector<int> vect(4);
	vector<int>::iterator vecitr;
	//list<int*>::iterator vitr;
    list<Point> vectorlist;
    list<Triangle> trianglelist;
    list<Quad> quadlist;
	vector<vector<int>>::iterator vitr;
	list<Point>::iterator pitr;
    list<Triangle>::iterator titr;
    list<Quad>::iterator qitr;
	list<Quad>::iterator qditr;


    x= .2*sqrt(-2*log((rand()+1)/r_max))*sin(2*pii*rand()/r_max)+rnd;
	y= .2*sqrt(-2*log((rand()+1)/r_max))*sin(2*pii*rand()/r_max)+rnd;
	z= mountaintop;
    cpnt.xpos=x;
	cpnt.ypos=y;
	cpnt.zpos=z;

    fstream fout,fout1;
	fout << fixed << setprecision(2);
	fout.open("Triangle.txt", ios::out);
	fout1 << fixed << setprecision(2);
	fout1.open("UVcoord.txt", ios::out);
	//Base corner points
    vectorlist.push_back(cpnt);
    pnt1.xpos=0;pnt1.ypos=0;pnt1.zpos=0;
    vectorlist.push_back(pnt1);
    pnt2.xpos=100;pnt2.ypos=0;pnt2.zpos=0;
    vectorlist.push_back(pnt2);
    pnt3.xpos=100;pnt3.ypos=100;pnt3.zpos=0;
    vectorlist.push_back(pnt3);
    pnt4.xpos=0;pnt4.ypos=100;pnt4.zpos=0;
	vectorlist.push_back(pnt4);
	/***base triangle build****************************************************/
    pntA=cpnt;
    pntB=pnt1;
    pntC=pnt2;
    tri1=new Triangle(pntA,pntB,pntC);
    trianglelist.push_back(*tri1);
    pntA=cpnt;
    pntB=pnt2;
    pntC=pnt3;
    tri1=new Triangle(pntA,pntB,pntC);
    trianglelist.push_back(*tri1);
    pntA=cpnt;
    pntB=pnt3;
    pntC=pnt4;
    tri1=new Triangle(pntA,pntB,pntC);
    trianglelist.push_back(*tri1);
    pntA=cpnt;
    pntB=pnt4;
    pntC=pnt1;
    tri1=new Triangle(pntA,pntB,pntC);
    trianglelist.push_back(*tri1);

	pitr = vectorlist.begin();
	while (pitr != vectorlist.end())
	{
		Point P = *pitr;
		float xp = P.getXpos();
		float yp = P.getYpos();
		if (xp > maxX)
			maxX = xp;
		if (yp > maxY)
			maxY = yp;
		pitr++;
	}
	titr = trianglelist.begin();
	while (titr != trianglelist.end())
	{
		//cout<<"quadlist output"<<endl;
		tri1 = &(*titr);
		pntA = tri1->pntA;
		vertices0.push_back(pntA);
		UVs0.push_back(pntA.xpos / maxX);
		UVs0.push_back(pntA.ypos / maxY);
		pntB = tri1->pntB;
		vertices0.push_back(pntB);
		UVs0.push_back(pntB.xpos / maxX);
		UVs0.push_back(pntB.ypos / maxY);
		
		pntC = tri1->pntC;
		vertices0.push_back(pntC);
		UVs0.push_back(pntC.xpos / maxX);
		UVs0.push_back(pntC.ypos / maxY);
		titr++;
	}

    int vl[4]={0,0,0,0};
    int count= 1;
	//First quad build
    if(cycles>0)
    {
    	titr=trianglelist.begin();
		leftline=titr->AB;
		endleftpnt=leftline.getMidpoint(1);

	    for(int i=0;i<4;i++)
		{
			ctr= titr->getCenter();
	        vectorlist.push_back(ctr);
			if(i==0)
			{
		        leftpnt=endleftpnt;
				vectorlist.push_back(leftpnt);
				rightline=titr->AC;
				rightpnt=rightline.getMidpoint(1);
				vectorlist.push_back(rightpnt);
	 		}
	 		else if(i==3)
	 		{
	 			leftpnt=rightpnt;
				rightpnt=endleftpnt;
			}
			else
	 		{
	 			leftpnt=rightpnt;
				rightline=titr->AC;
				rightpnt=rightline.getMidpoint(1);
				vectorlist.push_back(rightpnt);
	 		}
	 		
	 		//quad 1
			pntA=titr->pntB;
	        pntB=leftpnt;
	        pntC=ctr;
	        baseline=titr->BC;
	        pntD=baseline.getMidpoint(1);
	        vectorlist.push_back(pntD);
			pQd=new Quad(pntA,pntB,pntC,pntD);
			pQd->setNumber(count);

	        quadlist.push_back(*pQd);
	        count++;
			//quad 2
	        pntA=pntD;
	        pntB=pntC;
	        pntC=rightpnt;
	        pntD=titr->pntC;
	        pQd=new Quad(pntA,pntB,pntC,pntD);
			pQd->setNumber(count);

	        quadlist.push_back(*pQd);
			count++;
			//quad 3
			pntA=leftpnt;
	        pntD=pntB;
	        pntB=titr->pntA;
			pntC=rightpnt;
	        pQd=new Quad(pntA,pntB,pntC,pntD);
			pQd->setNumber(count);

	        quadlist.push_back(*pQd);
			count++;

			titr++;
		}
		// set x,y max values to normalize UV coords.
		pitr = vectorlist.begin();
		while (pitr != vectorlist.end())
		{
			Point P = *pitr;
			float xp = P.getXpos();
			float yp = P.getYpos();
			if (xp > maxX)
				maxX = xp;
			if (yp > maxY)
				maxY = yp;
			pitr++;
		}

		qitr = quadlist.begin();
		while (qitr != quadlist.end())
		{
			pntA = qitr->pntA;
			pntA.bad = false;
			vertices1.push_back(pntA);
			UVs1.push_back(pntA.xpos / maxX);
			UVs1.push_back(pntA.ypos / maxY);
			pntB = qitr->pntB;
			pntB.bad = false;
			vertices1.push_back(pntB);
			UVs1.push_back( pntB.xpos / maxX);
			UVs1.push_back(pntB.ypos / maxY);
			pntC = qitr->pntC;
			pntC.bad = false;
			vertices1.push_back(pntC);
			UVs1.push_back(pntC.xpos / maxX);
			UVs1.push_back(pntC.ypos / maxY);
			pntA = qitr->pntA;
			pntA.bad = false;
			vertices1.push_back(pntA);
			UVs1.push_back(pntA.xpos / maxX);
			UVs1.push_back(pntA.ypos / maxY);
			pntB = qitr->pntC;
			pntB.bad = false;
			vertices1.push_back(pntB);
			UVs1.push_back(pntB.xpos / maxX);
			UVs1.push_back(pntB.ypos / maxY);
			pntC = qitr->pntD;
			pntC.bad = false;
			vertices1.push_back(pntC);
			UVs1.push_back(pntC.xpos / maxX);
			UVs1.push_back(pntC.ypos / maxY);
			qitr++;
		}

	}
	int vc = vectorlist.size();
	vector<vector<int>> vlist(vc, vector<int>(4));
	for (int t = 0; t < vc; t++)
	{
		vlist[t] = { 0,0,0,0 };
	}
	qitr = quadlist.begin();
	while (qitr != quadlist.end())
	{
		pitr = vectorlist.begin();
		for (int i = 0; i<vc; i++)
		{
			int nbr = qitr->getNumber();
			if ((qitr->pntA == *pitr) || (qitr->pntB == *pitr) || (qitr->pntC == *pitr) || (qitr->pntD == *pitr))
			{
				int ct = 0;
				if (vlist[i][0] != 0)
				{
					ct++;
				}
				if ((vlist[i][1]) != 0)
				{
					ct++;
				}
				if ((vlist[i][2]) != 0)
				{
					ct++;
				}
				(vlist[i][ct]) = nbr;
			}
			pitr++;
		}
		qitr++;
	}
	// build new quads from the current list of quads for each cycle 
	for(int v=1;v<cycles;v++)
	{
		int vec = vectorlist.size();
		int q= quadlist.size();
		int vls = vlist.size();
		//vlist.clear();
		vect.clear();
		vector<int>fvec = { 0,0,0,0 };
		for (int t = 0; t < vec; t++)
		{
			vlist.push_back(fvec);
		}
		qitr = quadlist.begin();
		while(qitr!=quadlist.end())
		{
			pitr=vectorlist.begin();
			for(int i=0;i<vec;i++)
			{
				int nbr=qitr->getNumber();
				if((qitr->pntA==*pitr)||(qitr->pntB==*pitr)||(qitr->pntC==*pitr)||(qitr->pntD==*pitr))
				{
					int ct=0;
					if (vlist[i][0]!=0)
					{
						ct++;
					}					
					if ((vlist[i][1])!=0)
					{
						ct++;
					}
					if((vlist[i][2])!=0)
					{
						ct++;
					}
					(vlist[i][ct])=nbr;
				}
    			pitr++;
			}
			qitr++;
		}
		qitr=quadlist.begin();
		while(qitr!=quadlist.end())
		{
			int vsize = vlist.size();
			vitr = vlist.begin();
			for(int i=0;i<vsize;i++)
			{
				vect = *vitr;
				
				//check each quad for shared verticies 
				if (vect[0]==qitr->getNumber())
				{
					
					if(vect[1]!=0)
					{
						//qditr=qitr;
						qditr= quadlist.begin();
						while(qditr!=quadlist.end())
						{
							//if found, check for a shared line and set as nieghbor
							if(qditr->getNumber()== vect[1] || qditr->getNumber()== vect[2] || qditr->getNumber()== vect[3])
							{
								if(qitr->lineAB==qditr->lineCD || qitr->lineAB==qditr->lineBC || qitr->lineAB==qditr->lineAD)
								{
									qitr->leftn=qditr->getNumber();
									qitr->pntLeft.setActive();									
								}
								if(qitr->lineBC==qditr->lineCD || qitr->lineBC==qditr->lineAB || qitr->lineBC==qditr->lineAD)
								{
									qitr->topn=qditr->getNumber();									
									qitr->pntTop.setActive();
								}
								if(qitr->lineCD==qditr->lineAB || qitr->lineCD==qditr->lineBC || qitr->lineCD==qditr->lineAD)
								{
									qitr->rightn=qditr->getNumber();									
									qitr->pntRight.setActive();
								}
								if(qitr->lineAD==qditr->lineCD || qitr->lineAD==qditr->lineBC || qitr->lineAD==qditr->lineAB)
								{
									qitr->basen=qditr->getNumber();									
									qitr->pntBase.setActive();
								}
							}
							qditr++;
						}
					}
				}
				if (vect[1]==qitr->getNumber())
				{
					if(vect[2]!=0)
					{
						qditr= quadlist.begin();
						while(qditr!=quadlist.end())
						{
							if(qditr->getNumber()== vect[2] || qditr->getNumber()== vect[3])
							{
								if(qitr->lineAB==qditr->lineCD || qitr->lineAB==qditr->lineBC || qitr->lineAB==qditr->lineAD)
								{
									qitr->leftn=qditr->getNumber();									
									qitr->pntLeft.setActive();
								}
								if(qitr->lineBC==qditr->lineCD || qitr->lineBC==qditr->lineAB || qitr->lineBC==qditr->lineAD)
								{
									qitr->topn=qditr->getNumber();									
									qitr->pntTop.setActive();
								}
								if(qitr->lineCD==qditr->lineAB || qitr->lineCD==qditr->lineBC || qitr->lineCD==qditr->lineAD)
								{
									qitr->rightn=qditr->getNumber();									
									qitr->pntRight.setActive();
								}
								if(qitr->lineAD==qditr->lineCD || qitr->lineAD==qditr->lineBC || qitr->lineAD==qditr->lineAB)
								{
									qitr->basen=qditr->getNumber();									
									qitr->pntBase.setActive();
								}
							}
							qditr++;
						}
					}
				}
				if (vect[2]==qitr->getNumber())
				{
					if(vect[3]!=0)
					{
						qditr= quadlist.begin();
						while(qditr!=quadlist.end())
						{
							if(qditr->getNumber()== vect[3])
							{
								if(qitr->lineAB==qditr->lineCD || qitr->lineAB==qditr->lineBC || qitr->lineAB==qditr->lineAD)
								{
									qitr->leftn=qditr->getNumber();
									qitr->pntLeft.setActive();
								}
								if(qitr->lineBC==qditr->lineCD || qitr->lineBC==qditr->lineAB || qitr->lineBC==qditr->lineAD)
								{
									qitr->topn=qditr->getNumber();									
									qitr->pntTop.setActive();
								}
								if(qitr->lineCD==qditr->lineAB || qitr->lineCD==qditr->lineBC || qitr->lineCD==qditr->lineAD)
								{
									qitr->rightn=qditr->getNumber();									
									qitr->pntRight.setActive();
								}
								if(qitr->lineAD==qditr->lineCD || qitr->lineAD==qditr->lineBC || qitr->lineAD==qditr->lineAB)
								{
									qitr->basen=qditr->getNumber();									
									qitr->pntBase.setActive();
								}
							}
							qditr++;
						}
					}
				}
				vitr++;
			}
			qitr++;
		}

		Point zeropnt;
		zeropnt.setActive();
		int sendcycles= v+1;
		int howmany= quadlist.size();
		count= 1;
		for(int k=0;k<howmany;k++)
		{
			qitr=quadlist.begin();
			ctr= qitr->getCenter(sendcycles);
			vectorlist.push_back(ctr);
			if(qitr->pntLeft.active && qitr->pntLeft!=zeropnt)
			{
				leftpnt= qitr->pntLeft;
			}
			else
			{
		        leftline=qitr->lineAB;
				leftpnt=leftline.getMidpoint(sendcycles);
				vectorlist.push_back(leftpnt);
				if(qitr->pntLeft.active)
				{
					qditr=quadlist.begin();
					 while( qditr!=quadlist.end())
					 {
						 if(qitr->leftn==qditr->getNumber())
							break;
						 qditr++;
					 }
					 Line lq = qitr->lineAB;
					 Line lqr = qditr->lineCD;
					 if(lq==lqr)
					 {
						qditr->pntRight=leftpnt;
					 	qditr->pntRight.setActive();
					 }
					 else
					 {
					 	qditr->pntTop=leftpnt;
					 	qditr->pntTop.setActive();
					 }
				}
			}
			if(qitr->pntRight.active && qitr->pntRight!=zeropnt)
			{
				rightpnt= qitr->pntRight;
			}
			else
			{
				rightline=qitr->lineCD;
	   			rightpnt=rightline.getMidpoint(sendcycles);
				vectorlist.push_back(rightpnt);
				if(qitr->pntRight.active)
				{
					 qditr=quadlist.begin();
					 while( qditr!=quadlist.end())
					 {
						 if(qitr->rightn==qditr->getNumber())
							break;
						 qditr++;
					 }
					 Line lq = qitr->lineCD;
					 Line lqr = qditr->lineAB;
					 if(lqr==lq)
					 {
					 	qditr->pntLeft=rightpnt;
					 	qditr->pntLeft.setActive();
					 }
					 else
					 {
					 	qditr->pntTop=rightpnt;
					 	qditr->pntTop.setActive();
					 }
				}
			}

			if(qitr->pntTop.active && qitr->pntTop!=zeropnt)
			{
				toppnt= qitr->pntTop;
			}
			else
			{
				topline=qitr->lineBC;
				toppnt=topline.getMidpoint(sendcycles);
				vectorlist.push_back(toppnt);
				if(qitr->pntTop.active)
				{
					 qditr=quadlist.begin();
					 while( qditr!=quadlist.end())
					 {
						 if(qitr->topn==qditr->getNumber())
							break;
						 qditr++;
					 }
					 Line lq = qitr->lineBC;
					 Line lqr = qditr->lineAD;
					 Line lqr2 = qditr->lineAB;
					 if(lqr==lq)
					 {
					 	qditr->pntBase=toppnt;
					 	qditr->pntBase.setActive();
					 }
					 else if(lqr2==lq)
					 {
					 	qditr->pntLeft=toppnt;
					 	qditr->pntLeft.setActive();
					 }
					 else
					 {
					 	qditr->pntRight=toppnt;
					 	qditr->pntRight.setActive();
					 }
				}
			}
			bool bss = qitr->pntBase.active;
			if((bss) && qitr->pntBase!=zeropnt)
			{
				basepnt= qitr->pntBase;
			}
			else
			{
				baseline=qitr->lineAD;
				basepnt=baseline.getMidpoint(sendcycles);
				vectorlist.push_back(basepnt);
				qditr=quadlist.begin();
				 while( qditr!=quadlist.end())
				 {
					 if(qitr->basen==qditr->getNumber())
						break;
					 qditr++;
				 }
				 bool bs = qitr->pntBase.active;
				 if(bs)
				 {
					 qditr->pntTop= basepnt;
					 qditr->pntTop.setActive();
				}
			}
			//quad 1
			pntA=qitr->pntA;
			pntB=leftpnt;
	        pntC=ctr;
	        pntD=basepnt;         
	        pQd=new Quad(pntA,pntB,pntC,pntD);
			pQd->setNumber(count);
	        quadlist.push_back(*pQd);

			count++;
			//quad 2
			pntA=pntD;
			pntB=ctr;
	        pntC=rightpnt;
	        pntD=qitr->pntD;         
	        pQd=new Quad(pntA,pntB,pntC,pntD);
	        pQd->setNumber(count);
	        quadlist.push_back(*pQd);

			count++;
			//quad 3
	        pntA=ctr;
			pntB=toppnt;
	        pntC=qitr->pntC;
	        pntD=rightpnt;         
	        pQd=new Quad(pntA,pntB,pntC,pntD);
	        pQd->setNumber(count);
	        quadlist.push_back(*pQd);

	        count++;
			//quad 4
	        pntA=leftpnt;
			pntB=qitr->pntB;
	        pntC=toppnt;
	        pntD=ctr;         
	        pQd=new Quad(pntA,pntB,pntC,pntD);
	        pQd->setNumber(count);
	        quadlist.push_back(*pQd);
	        quadlist.pop_front();
	        count++;
  		}	
		pitr = vectorlist.begin();
		while (pitr != vectorlist.end())
		{
			Point P = *pitr;
			float xp = P.getXpos();
			float yp = P.getYpos();
			if (xp > maxX)
				maxX = xp;
			if (yp > maxY)
				maxY = yp;
			pitr++;
		}
		// switch statemant for recording each cycle of a mountain build 
		int index = v + 1;
		switch (index)
		{
			case 2:
				
				qitr = quadlist.begin();
				while (qitr != quadlist.end())
				{
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices2.push_back(pntA);
					UVs2.push_back(pntA.xpos / maxX);
					UVs2.push_back(pntA.ypos / maxY);
					pntB = qitr->pntB;
					pntB.bad = false;
					vertices2.push_back(pntB);
					UVs2.push_back(pntB.xpos / maxX);
					UVs2.push_back(pntB.ypos / maxY);
					pntC = qitr->pntC;
					pntC.bad = false;
					vertices2.push_back(pntC);
					UVs2.push_back(pntC.xpos / maxX);
					UVs2.push_back(pntC.ypos / maxY);
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices2.push_back(pntA);
					UVs2.push_back(pntA.xpos / maxX);
					UVs2.push_back(pntA.ypos / maxY);
					pntB = qitr->pntC;
					pntB.bad = false;
					vertices2.push_back(pntB);
					UVs2.push_back(pntB.xpos / maxX);
					UVs2.push_back( pntB.ypos / maxY);
					pntC = qitr->pntD;
					pntC.bad = false;
					vertices2.push_back(pntC);
					UVs2.push_back(pntC.xpos / maxX);
					UVs2.push_back(pntC.ypos / maxY);
					qitr++;
				}
				break;
			case 3:
				
				qitr = quadlist.begin();
				while (qitr != quadlist.end())
				{
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices3.push_back(pntA);
					UVs3.push_back(pntA.xpos / maxX);
					UVs3.push_back(pntA.ypos / maxY);
					pntB = qitr->pntB;
					pntB.bad = false;
					vertices3.push_back(pntB);
					UVs3.push_back(pntB.xpos / maxX);
					UVs3.push_back(pntB.ypos / maxY);
					pntC = qitr->pntC;
					pntC.bad = false;
					vertices3.push_back(pntC);
					UVs3.push_back(pntC.xpos / maxX);
					UVs3.push_back(pntC.ypos / maxY);
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices3.push_back(pntA);
					UVs3.push_back(pntA.xpos / maxX);
					UVs3.push_back(pntA.ypos / maxY);
					pntB = qitr->pntC;
					pntB.bad = false;
					vertices3.push_back(pntB);
					UVs3.push_back(pntB.xpos / maxX);
					UVs3.push_back(pntB.ypos / maxY);
					pntC = qitr->pntD;
					pntC.bad = false;
					vertices3.push_back(pntC);
					UVs3.push_back(pntC.xpos / maxX);
					UVs3.push_back(pntC.ypos / maxY);
					qitr++;
				}
				break;
			case 4:
				
				qitr = quadlist.begin();
				while (qitr != quadlist.end())
				{
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices4.push_back(pntA);
					UVs4.push_back(pntA.xpos / maxX);
					UVs4.push_back(pntA.ypos / maxY);
					pntB = qitr->pntB;
					pntB.bad = false;
					vertices4.push_back(pntB);
					UVs4.push_back(pntB.xpos / maxX);
					UVs4.push_back(pntB.ypos / maxY);
					pntC = qitr->pntC;
					pntC.bad = false;
					vertices4.push_back(pntC);
					UVs4.push_back(pntC.xpos / maxX);
					UVs4.push_back(pntC.ypos / maxY);
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices4.push_back(pntA);
					UVs4.push_back(pntA.xpos / maxX);
					UVs4.push_back(pntA.ypos / maxY);
					pntB = qitr->pntC;
					pntB.bad = false;
					vertices4.push_back(pntB);
					UVs4.push_back(pntB.xpos / maxX);
					UVs4.push_back(pntB.ypos / maxY);
					pntC = qitr->pntD;
					pntC.bad = false;
					vertices4.push_back(pntC);
					UVs4.push_back(pntC.xpos / maxX);
					UVs4.push_back(pntC.ypos / maxY);
					qitr++;
				}
				break;
			case 5:
				
				qitr = quadlist.begin();
				while (qitr != quadlist.end())
				{
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices5.push_back(pntA);
					UVs5.push_back(pntA.xpos / maxX);
					UVs5.push_back(pntA.ypos / maxY);
					pntB = qitr->pntB;
					pntB.bad = false;
					vertices5.push_back(pntB);
					UVs5.push_back(pntB.xpos / maxX);
					UVs5.push_back(pntB.ypos / maxY);
					pntC = qitr->pntC;
					pntC.bad = false;
					vertices5.push_back(pntC);
					UVs5.push_back(pntC.xpos / maxX);
					UVs5.push_back(pntC.ypos / maxY);
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices5.push_back(pntA);
					UVs5.push_back(pntA.xpos / maxX);
					UVs5.push_back(pntA.ypos / maxY);
					pntB = qitr->pntC;
					pntB.bad = false;
					vertices5.push_back(pntB);
					UVs5.push_back(pntB.xpos / maxX);
					UVs5.push_back(pntB.ypos / maxY);
					pntC = qitr->pntD;
					pntC.bad = false;
					vertices5.push_back(pntC);
					UVs5.push_back(pntC.xpos / maxX);
					UVs5.push_back(pntC.ypos / maxY);
					qitr++;
				}
				break;
			case 6:
				
				qitr = quadlist.begin();
				while (qitr != quadlist.end())
				{
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices6.push_back(pntA);
					UVs6.push_back(pntA.xpos / maxX);
					UVs6.push_back(pntA.ypos / maxY);
					pntB = qitr->pntB;
					pntB.bad = false;
					vertices6.push_back(pntB);
					UVs6.push_back(pntB.xpos / maxX);
					UVs6.push_back(pntB.ypos / maxY);
					pntC = qitr->pntC;
					pntC.bad = false;
					vertices6.push_back(pntC);
					UVs6.push_back(pntC.xpos / maxX);
					UVs6.push_back(pntC.ypos / maxY);
					pntA = qitr->pntA;
					pntA.bad = false;
					vertices6.push_back(pntA);
					UVs6.push_back(pntA.xpos / maxX);
					UVs6.push_back(pntA.ypos / maxY);
					pntB = qitr->pntC;
					pntB.bad = false;
					vertices6.push_back(pntB);
					UVs6.push_back(pntB.xpos / maxX);
					UVs6.push_back(pntB.ypos / maxY);
					pntC = qitr->pntD;
					pntC.bad = false;
					vertices6.push_back(pntC);
					UVs6.push_back(pntC.xpos / maxX);
					UVs6.push_back(pntC.ypos / maxY);
					qitr++;
				}
				break;
		}
  	}

/**************** output and cleanup*******************************************/
	//set the max x and max y for making the uv list
	pitr = vectorlist.begin();
	while (pitr != vectorlist.end())
	{
		Point P = *pitr;
		float xp = P.getXpos();
		float yp = P.getYpos();
		if (xp > maxX)
			maxX = xp;
		if (yp > maxY)
			maxY = yp;
		pitr++;
	}
	
    if(cycles==0)
    {		
		titr=trianglelist.begin();
	    while(titr!=trianglelist.end())
	    {
	    	//cout<<"quadlist output"<<endl;
			tri1 = &(*titr);
			pntA = tri1->pntA;
			vertices.push_back(pntA);
			UVs.push_back(pntA.xpos / maxX);
			UVs.push_back(pntA.ypos / maxY);
			float xp = (pntA.xpos / maxX);
			float yp= (pntA.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			pntB = tri1->pntB;
			vertices.push_back(pntB);
			UVs.push_back(pntB.xpos / maxX);
			UVs.push_back(pntB.ypos / maxY);
			xp = (pntB.xpos / maxX);
			yp = (pntB.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			pntC = tri1->pntC;
			vertices.push_back(pntC);
			UVs.push_back(pntC.xpos / maxX);
			UVs.push_back(pntC.ypos / maxY);
			xp = (pntC.xpos / maxX);
			yp = (pntC.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			tri1->printT(fout);
			titr++;
	    }
    }
	else
	{
		//making triangles for opengl
		titr = trianglelist.begin();
		while (titr != trianglelist.end())
		{
			trianglelist.erase(titr++);
		}
		int vtp = 0;
		int uvp = 0;
		qitr = quadlist.begin();
		while (qitr != quadlist.end())
		{
			pntA = qitr->pntA;
			pntA.bad = false;
			vertices.push_back(pntA);
			UVs.push_back(pntA.xpos / maxX);
			UVs.push_back(pntA.ypos / maxY);
			float xp = (pntA.xpos / maxX);
			float yp = (pntA.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			pntB = qitr->pntB;
			pntB.bad = false;
			vertices.push_back(pntB);
			UVs.push_back(pntB.xpos / maxX);
			UVs.push_back(pntB.ypos / maxY);
			xp = (pntB.xpos / maxX);
			yp = (pntB.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			pntC = qitr->pntC;
			pntC.bad = false;
			vertices.push_back(pntC);
			UVs.push_back(pntC.xpos / maxX);
			UVs.push_back(pntC.ypos / maxY);
			xp = (pntC.xpos / maxX);
			yp = (pntC.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			tri1 = new Triangle(pntA, pntB, pntC);
			trianglelist.push_back(*tri1);
			tri1->printT(fout);
			pntA = qitr->pntA;
			pntA.bad = false;
			vertices.push_back(pntA);
			UVs.push_back(pntA.xpos / maxX);
			UVs.push_back(pntA.ypos / maxY);
			xp = (pntA.xpos / maxX);
			yp = (pntA.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			pntB = qitr->pntC;
			pntB.bad = false;
			vertices.push_back(pntB);
			UVs.push_back(pntB.xpos / maxX);
			UVs.push_back(pntB.ypos / maxY);
			xp = (pntB.xpos / maxX);
			yp = (pntB.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			pntC = qitr->pntD;
			pntC.bad = false;
			vertices.push_back(pntC);
			UVs.push_back(pntC.xpos / maxX);
			UVs.push_back(pntC.ypos / maxY);
			xp = (pntC.xpos / maxX);
			yp = (pntC.ypos / maxY);
			fout1 << xp << " " << yp << endl;
			tri1 = new Triangle(pntA, pntB, pntC);
			trianglelist.push_back(*tri1);
			tri1->printT(fout);
			qitr++;
		}
	}
	fout.close();
	fout1.close();

	qitr=quadlist.begin();
    while(qitr != quadlist.end())
    {
        quadlist.erase(qitr++);
    }
    titr=trianglelist.begin();
    while(titr != trianglelist.end())
    {
    	trianglelist.erase(titr++);
    }
}

