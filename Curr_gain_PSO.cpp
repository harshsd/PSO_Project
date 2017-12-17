#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
double c1=1.4962;
double c2=1.4962;
double w=0.7298;
const int n=15;//No of parameters
const int i=100;// No. of iterations
const int p=25;// No. of particles

double fit(double x[p][n], int par_num)
{
	//Enter code to calculate fitness here
}

double rand_num()				// Returns random number between 0 and 1
{
	double r=(double)abs(rand())/(double)RAND_MAX;
	return r;
}

void init_limits(double a[2][n])		//a[0][m] is min of mth parameter and a[1][m] is max of mth parameter
{
	//Enter limits here;

}

void init_particles(double x[p][n], double lbest[p][n], double lim[2][n])  //Initializes particles between their max and min values
{
	for(int j=0;j<p;j++)
	{
		for(int k=0;k<n;k++)
		{
				x[j][k]= lim[0][k] + (rand_num()*(lim[1][k]-lim[0][k]));
				lbest[j][k] = x[j][k];
		}
	}
}

bool isInRange(double x[p][n], double v[p][n], int par_num,double lim[2][n])  //To check if particle is in range
{
	bool t=true;
	for(int k=0;k<n;k++)
	{
		double new_x = x[par_num,k] + v[par_num,k];
		if(new_x<lim[0][k]||new_x>lim[1][k])
		{
			t=false;
		}
	}
	return t;
}

void calc_lbest(double x[p][n],double lbest[p][n], int par_num) 			//updates lbest of one particle
{
	if(fit(x,par_num)<fit(lbest,par_num))
	{
		for(int j=0;j<n;j++)
		{
			lbest[par_num][j]=x[par_num][j];
		}
	}
}

void calc_gbest(double lbest[p][n], double gbest[p][n])		//updates gbest array
{
	for(int par_num=0;par_num<p;j++)
	{
		if(fit(lbest,par_num)<fit(gbest,0))
		{
			for(int k=0;k<n;k++){gbest[0][k]=lbest[par_num][k];}
		}
	}
}

void writeFile(double x[p][n], int par_num)
{
	ofstream s;
	s.open("Model.txt");
	s << "*Website PHILIPS\n";
	s << ".MODEL QBC547A NPN(\n";
	s << "+IS="+str(1.533E-14)+" \n";		//Replicate this line as many times as parameters are there
}

void readFile()
{
	//Write code to read output file here
}
int main()
{
	double par_limits[2][n];
	init_limits(par_limits);
	double x[p][n];
	double v[p][n];
	double lbest[p][n];
	double gbest[p][n];// We use only gbest[0] array to store best particle. Ignore others
	init_particles(x,lbest,par_limits);		//particles initialized and lbest initialized
	for(int j=0;j<p;j++){for(int k=0;k<n;k++){v[j][k]=0;gbest[0][k]=0;}}
	calc_gbest(lbest,gbest); //Initialize gbest
	
	//Enter iterations
	for(int iteration=0;iteration<i;iteration++)	//performs i iterations //completed
	{
			for(int j=0;j<p;j++)		//for each particle update x and v
			{
				double rnd1=rand_num();double rand_num();
				for(int k=0;k<n;k++)
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
				calc_lbest(x,lbest,j);
			}
			calc_gbest(lbest,gbest);		//update gbest
	}
	return 0;	
}