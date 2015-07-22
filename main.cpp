#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"

using namespace std;

int* masscenter(vector<int*> object){
	int *t=new int[2];
	double x=0;
	double y=0;
	for(int i=0;i<object.size();i++){
		x+=object[i][0];
		y+=object[i][1];

	}
	x=x/object.size();
	y=y/object.size();

	t[0]=(int)x;
	t[1]=(int)y;

	return t;
}



vector<int*> getpoints( char* filename){
	vector<int*> p;
	ifstream f(filename);
	int x,y;
	int *t;
	
	while (!f.eof()){
		f>>x>>y;
		t=new int[2];
		t[0]=x;
		t[1]=y;
		p.push_back(t);
	}
	
	return p;
};





int* getsize(vector <int*> p){
	int *s=new int[2];
	s[0]=0;
	s[1]=0;

	for(int i=0; i<p.size();i++)
	{
		if(s[0]<p[i][0]) s[0]=p[i][0];
		if(s[1]<p[i][1]) s[1]=p[i][1];

	}

	return s;
}

void pointsonlyimage(image* i1){
	
	char fn[]="image.pnm";
	ofstream file(fn);

	file<<"P3"<<endl;
	file<<i1->gety()<<" "<<i1->getx()<<endl;
	file<<255<<endl;

	


	for(int i=i1->getx()-1; i>=0;i--){
			for(int j=0;j<i1->gety();j++){


				if(i1->getp(i,j)!=0)
					file<<"0 0 0"<<endl;
				else
					file<<"255 255 255"<<endl;
		}
			
	}


	file.close();

}


void analyzedimage(image* i1,int r){
	char fn[]="object.pnm";
	ofstream file(fn);
	vector<int*> p;
	int *t;


	t=i1->getobject(r,1)[0];

	i1->drawrad(r,t);

	file<<"P3"<<endl;
	file<<i1->gety()<<" "<<i1->getx()<<endl;
	file<<255<<endl;

	for(int i=i1->getx()-1; i>=0;i--){
			for(int j=0;j<i1->gety();j++){

				switch(i1->getp(i,j)){
					case 0:file<<"255 255 255"<<endl;break;

					case 1: file<<"0 0 0"<<endl;break;

					case 2: file<<"100 200 0"<<endl;break;

					case 3: file<<"100 100 100"<<endl;break;


				}
				
		}
			
	}



	file.close();

}


int main(int argc, char *argv[]){
//радиус
int r=4; 

int *s;

vector<int*> p;

p=getpoints(argv[1]);

s=getsize(p);

image *im=new image(s[0]+1,s[1]+1);

im->setpoints(p);

cout<<"Радиус: "<<endl<<"	"<<r<<endl;



vector<int*> object;

object=im->getobject(r,0);
cout<<"Объект:"<<endl;
for(int i=0;i<object.size();i++)
	cout<<"		x= "<<object[i][0]<<" y= "<<object[i][1]<<endl;

cout<<"Центр масс:"<<endl;

s=masscenter(object);

cout<<"		x= "<<s[0]<<" y= "<<s[1]<<endl;

pointsonlyimage(im);
analyzedimage(im,r);

	return 0;
}

