#include "image.h"


using namespace std;

	image::image(int x, int y){
		this->im = new int*[x];
		for(int i=0;i<x;i++){
			this->im[i]=new int[y];
			for (int j=0;j<y;j++)
				this->im[i][j]=0;
		}
		this->x=x;
		this->y=y;




	}

	int image::getx(){
		return this->x;

	}

	int image::gety(){

		return this->y;

	}

	int image::getp(int x,int y){

		return this->im[x][y];
	}

	void image::printimage(){

		for(int i=0; i<this->x;i++){
			for(int j=0;j<this->y;j++)
				cout<<this->im[i][j]<<" ";
			cout<<endl;
		}


	}

	void image::setpoints(vector <int*> points){
		for(int i=0; i<points.size();i++){

			this->im[points[i][0]][points[i][1]]=1;

		}

	}


	void image::drawrad(int r, int *t){
		int xs,xf,ys,yf;

		if(t[0]-r<0)
			xs=0;
		else 
			xs=t[0]-r;

		if(t[1]-r<0)
			ys=0;
		else 
			ys=t[1]-r;

		if(t[0]+r>=this->getx())
			xf=this->getx();
		else 
			xf=t[0]+r;

		if(t[1]+r>=this->gety())
			yf=this->gety();
		else 
			yf=t[1]+r;		



		
		for(int i=xs;i<xf;i++)
			for(int j=ys;j<yf;j++){
				if(this->im[i][j]==0){
				
				if((i==xs)||(i==xf-1))
					this->im[i][j]=3;	

				if((j==ys)||(j==yf-1))
					this->im[i][j]=3;

				}
			}
			

		this->im[t[0]][t[1]]=2;

	}

	int image::radprov(int x1, int y1, int x2, int y2,int r){
		double r1=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
		if(r1>(double)r) return 0;
		return 1;
	}


	int image::prov(vector<int*> p, int*t){

	for(int i=0;i<p.size();i++)
		if((t[0]==p[i][0])&&(t[1]==p[i][1]))
			return 0;

	return 1;
	}

	//IF fl==0 - get obj , else  get center
	vector<int*> image::getobject(int r,int fl){
		vector<int*> p;
		vector<int*> p1;
		int *c=new int[2];
		int *t;
		
		

		for(int i=0;i<this->x;i++){

			for(int j=0;j<this->y;j++){
				
				//cout<<"point "<<j<<" "<<i<<endl;
				p1.clear();
				for(int i1=0;i1<=r;i1++)
					for(int j1=0;j1<=r;j1++){
						if((j-j1>=0)&&(i-i1>=0)){
							
							if((this->radprov(j,i,j-j1,i-i1,r))&&(this->im[i-i1][j-j1]==1)){
								
								//cout<<"		neg: "<<j-j1<<" "<<i-i1<<endl;
								t=new int[2];
								t[1]=j-j1;
								t[0]=i-i1;
								if(prov(p1,t))
									p1.push_back(t);
							}
						}



						if((j+j1<this->y)&&(i+i1<this->x)){
							if((this->radprov(j,i,j+j1,i+i1,r))&&(this->im[i+i1][j+j1]==1)){
								
								//cout<<"		pos: "<<j+j1<<" "<<i+i1<<endl;
								t=new int[2];
								t[1]=j+j1;
								t[0]=i+i1;
								if(prov(p1,t))
									p1.push_back(t);
							}
						}
						
					}

				if(p1.size()>p.size()){
					p=p1;
					c[1]=j;
					c[0]=i;
				}


			}
		}


			


		
		if(fl!=0){
			p.clear();
			p.push_back(c);


		}
		else cout<<"Центр области: "<<endl<<"	x = "<<c[0]<<" y="<<c[1]<<endl;
		return p;
	}

