#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;
//double c1,c2,w;
double c1=1.4962;
double c2=1.4962;
double w=0.7298;
double gain = 100;
double ic =0.001;
double b=100;
double rin=668.229777;
double old_rr=912;
double vce = 2;							//vcc = 5V
const int n=500;
const int p=25;						//n is number of iterations and p is number of particles
bool isInRange(double x[p][4],double v[p][4],int i,double lim[4][2])
{
	bool t=true;
	double aa,ss,dd,ff;
	aa=x[i][0]+v[i][0];ss=x[i][1]+v[i][1];dd=x[i][2]+v[i][2];ff=x[i][3]+v[i][3];
	if(aa>lim[0][1]||aa<lim[0][0]){t=false;}
	if(ss>lim[1][1]||ss<lim[1][0]){t=false;}
	if(dd>lim[2][1]||dd<lim[2][0]){t=false;}
	if(ff>lim[3][1]||ff<lim[3][0]){t=false;}
	return t;
}
double rand_num()
{
	double r=(double)abs(rand())/(double)RAND_MAX;
	return r;
}
double fit(double x[p][4],int m)
{
	double r1,r2,re,rc,new_ic,new_gain,new_vce,new_rin,fitness;
	r1=x[m][0];r2=x[m][1];rc=x[m][2];re=x[m][3];
	double vb=(5*r2)/(r1+r2);
	new_ic=(vb-0.7)/re;
	new_vce=5-new_ic*(re+rc);
	new_gain=(new_ic*rc)/0.025;
	double rr=(r1*r2)/(r1+r2);
	double rpi=(b*0.025)/new_ic;
	new_rin=(rr*rpi)/(rr+rpi);
	if(new_vce>0.2)
	{
 	fitness = pow((new_ic-ic)/ic,2)+pow((new_gain-gain)/gain,2)+pow((new_vce-vce)/vce,2)+pow((new_rin-rin)/rin,2);
 	}
 	else{fitness=100;}
 	return fitness;
}

void calc_lmin(double x[p][4],double lmin[p][4],int m)
{
	if(fit(x,m)<fit(lmin,m))
	{	
		for(int i=0;i<4;i++)
			{
				lmin[m][i]=x[m][i];
		}
	}
}

void calc_gmin(double lmin[p][4],double gmin[p][4])
{
	for (int j=0;j<p;j++)
	{
		if(fit(gmin,0)>fit(lmin,j))
	{	
		for(int i=0;i<4;i++)
			{
				gmin[0][i]=lmin[j][i];
		}
	}
}}	
int main()
{	ofstream f,f1,f2,f3,f4,f5;
	f.open ("average.txt");
	f1.open("0.txt");
	f2.open("10.txt");
	f3.open("50.txt");
	f4.open("100.txt");
	f5.open("500.txt");
	double lim[4][2];
	double r1_avg[n],r2_avg[n],rc_avg[n],re_avg[n];
	double fit_gbest[n];
	for(int i=0;i<n;i++)
	{
		r1_avg[i]=0;fit_gbest[i]=0;r2_avg[i]=0;rc_avg[i]=0;re_avg[i]=0;
	}
	lim[0][0]=2500;lim[0][1]=5000;lim[1][0]=500;lim[1][1]=2000;lim[2][0]=500;lim[2][1]=5000;lim[3][0]=100;lim[3][1]=1000; 
	double x[p][4];
	double v[p][4];
	double lbest[p][4];
	double gbest[p][4];
	for(int i=0;i<p;i++)		//initialize all particles and their velocities to zero and lbest as initial position
	{
		for(int j=0;j<4;j++)
		{
			x[i][j]=lim[j][0]+(rand_num()*(lim[j][1]-lim[j][0]));
			lbest[i][j]=x[i][j];
			v[i][j]=0;
		}
		f1<<x[i][0]<<"\t"<<x[i][1]<<"\n";
	}
	
	calc_gmin(lbest,gbest);//done
	for(int i=0;i<n;i++)

		{
			for (int j=0;j<p;j++)
			{	double rnd1=rand_num();double rnd2=rand_num();
				for(int k=0;k<4;k++)
				{
					v[j][k]=(c1*rnd1*(gbest[0][k]-x[j][k]))+(c2*rnd2*(lbest[j][k]-x[j][k]))+w*v[j][k];
				}
				if(isInRange(x,v,j,lim)==true)
				{
					for(int k=0;k<4;k++)
					{
						x[j][k]=x[j][k]+v[j][k];
					}
				}
				else
				{
					for(int k=0;k<4;k++)
					{
						v[j][k]=v[j][k]/2;
					}
				}	
				calc_lmin(x,lbest,j);
			}
			calc_gmin(lbest,gbest);
			fit_gbest[i]=fit(gbest,0);
			double r1a=0, r2a =0, rea=0, rca=0;
			for(int y=0;y<p;y++){r1a=r1a+(x[y][0]/p);r2a=r2a+(x[y][1]/p);rca=rca+(x[y][2]/p);rea=rea+(x[y][3]/p);}
			f<<r1a<<"\t"<<r2a<<"\t"<<rca<<"\t"<<rea<<"\t"<<fit_gbest[i]<<"\n";	
			cout<<gbest[0][0]<<" "<<gbest[0][1]<<" "<<gbest[0][2]<<" "<<gbest[0][3]<<"\n";
			if(i==9){for(int z=0;z<p;z++){f2<<x[z][0]<<"\t"<<x[z][1]<<"\n";}}
			if(i==49){for(int z=0;z<p;z++){f3<<x[z][0]<<"\t"<<x[z][1]<<"\n";}}
			if(i==99){for(int z=0;z<p;z++){f4<<x[z][0]<<"\t"<<x[z][1]<<"\n";}}
			if(i==499){for(int z=0;z<p;z++){f5<<x[z][0]<<"\t"<<x[z][1]<<"\n";}}
		}
f.close();
return 0;
}

	
