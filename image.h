#ifndef IMAGE_H
#define IMAGE_H
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;
class image{
private:
	int **im;
	int x,y;


public:
	image(int x, int y);

	int getx();

	int gety();
	int getp(int x,int y);

	void printimage();

	void setpoints(vector <int*> points);


	void drawrad(int r, int *t);

	int radprov(int x1, int y1, int x2, int y2,int r);


	int prov(vector<int*> p, int*t);

	
	vector<int*> getobject(int r,int fl);

};





#endif
