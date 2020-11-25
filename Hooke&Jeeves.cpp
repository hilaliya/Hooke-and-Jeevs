#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cmath>
#include<string.h>
using namespace std;

//Function
double func(int par, int var, double pcoef[], double pdeg[], double x[], double coef[][10], double deg[][10])
{
	double z=0;
	double w[par];
	for(int i=0; i<par; i++)
	{	w[i]=0;
		for(int k=0; k<var; k++)
		{
			w[i]=w[i]+coef[i][k]*pow(x[k], deg[i][k]);
		}		
		z=z+pcoef[i]*pow(w[i],pdeg[i]);
	}		
	return z;
}



int main(){

cout<<"\nEnter the number of variables in your function: ";
int var;  //number of variables
cin>>var; 

cout<<"\nEnter the number of  paranthesis in your function: ";
int par;  //number of paranthesis
cin>>par; cout<<endl;

double pcoef[par];  //the coefficient of the paranthesis 
double pdeg[par];  //the degree of the paranthesis 

double coef[var][10];   // the coefficient of the variable in a paranthesis
double deg[var][10];   // the degree of the variable in a paranthesis

for(int k=0; k<par; k++)
{
	cout<<endl;				
	cout<<"Enter the coefficient of the "<<k+1<<".  paranthesis in your function x*(...): ";	
	cin>>pcoef[k]; 
	cout<<"Enter the degree of the "<<k+1<<".  paranthesis in your function (...)^x: ";	
	cin>>pdeg[k]; 	
}
for(int k=0; k<par; k++)
{
	cout<<endl;	
	for(int j=0; j<var; j++)
	{			
		cout<<"Enter the coefficient of the "<<j+1<<". variable in the "<<k+1<<". paranthesis (x*var+...): ";
		cin>>coef[k][j];

			
		cout<<"Enter the degree of the "<<j+1<<". variable in the "<<k+1<<". paranthesis(var^x+..): ";
		cin>>deg[k][j];
	}
}


cout<<"\nYour function is: ";
for(int k=0; k<par;k++)
{
	cout<<" + "<<pcoef[k]<<"(";
	for(int j=0; j<var; j++)
	{
		cout<<" "<<coef[k][j]<<"*X"<<j+1<<"^"<<deg[k][j];
	}
	cout<<")^"<<pdeg[k];	
}


int ii=1;
while( ii==1)
{
	cout<<"\n\nTry out your function!\n\n";
	double ex[var];
	
	for(int i=0; i<var; i++)
	{
		cout<<"Enter the "<<i+1<<". variable: ";	
		cin>>ex[i];
	}
	
	cout<<"\nf(X)="<<func(par,var,pcoef,pdeg,ex,coef,deg);
	cout<<"\n\npress 1 to continue, press any other key to exit: ";
	cin>>ii;	
}


cout<<"a- Hooke & Jeeves With Discrete Steps\n\n";
double X[var];
cout<<"\nEnter the start point x: \n";
for(int i=0; i<var; i++)
{
	cout<<"x"<<i+1<<"= ";
	cin>>X[i];	
}

double d[var][var];
for(int i=0; i<var; i++)
{
	for(int j=0; j<var; j++)
	{
		if(i==j) d[i][j]=1;
		else d[i][j]=0;
	}
}

double eps;  //epsilon
double del;  //delta
double alp;  //alpha

cout<<"\nEnter epsilon: ";
cin>>eps;
int k=0;

cout<<"\nEnter delta: ";
cin>>del;
	while (del<eps)
	{
		cout<<"\nPlease make sure 'delta >= epsilon' holds"<<endl;
		cout<<"\nEnter epsilon: ";
		cin>>eps;
		cout<<"\nEnter delta: ";
		cin>>del;	
	}	
	cout<<"\nEnter alpha: ";
	cin>>alp;
		
	int j=0;
		
	double y[var][var+1];
	double Y[var];
	double y1[var];
		
	for(int i=0; i<var; i++)
	{	
		y[i][0]=X[i];
		Y[i]=y[i][0];
		X[i]=Y[i];	
	}
		
	while(del>eps)  
	{
			
		while(j<var)
		{ cout<<"\n\n****  Iteration "<<k+1<<",  Dimension (j)= "<<j+1<<"  ****\n\n"; 	
			for(int i=0; i<var; i++)
			{
				y1[i]=y[i][j]+del*d[i][j];
				Y[i]=y[i][j];	
			}
			cout<<"X=(";
			for(int i=0; i<var; i++)
			{
				cout<<" "<<X[i]<<" ";	
			}
			cout<<")     f(X)= "<<func(par,var,pcoef, pdeg,X,coef,deg)<<endl<<endl;
				
			cout<<"y=(";
			for(int i=0; i<var; i++)
			{
				cout<<" "<<y[i][j]<<" ";	
			}
			cout<<")     f(y)= "<<func(par,var,pcoef, pdeg,Y,coef,deg)<<endl<<endl;
				
			cout<<"y+lambda*d=(";
			for(int i=0; i<var; i++)
			{
				cout<<" "<<y1[i]<<" ";	
			}
		
			cout<<")  f(y+lambda*d)= "<<func(par,var,pcoef, pdeg,y1,coef,deg)<<endl;
		
				
			if(func(par,var,pcoef, pdeg,Y,coef,deg)-func(par,var,pcoef, pdeg,y1,coef,deg)<eps/1000 )  //step 1
			{	
				cout<<"\nf(y)= "<<func(par,var,pcoef, pdeg,Y,coef,deg)<<" <= f(y+lambda*d)= "<<func(par,var,pcoef, pdeg,y1,coef,deg);
				cout<<" ---> Termination failure!\n";
				for(int i=0; i<var; i++)
				{
					y1[i]=y[i][j]-del*d[i][j];
				}
				
				cout<<"\ny-lambda*d=(";
				for(int i=0; i<var; i++)
				{
					cout<<" "<<y1[i]<<" ";
				}
				cout<<")   f(y-lambda*d)= "<<func(par,var,pcoef, pdeg,y1,coef,deg)<<endl;
				if(func(par,var,pcoef, pdeg,y1,coef,deg)<func(par,var,pcoef, pdeg,Y,coef,deg))
				{
					for(int i=0; i<var; i++)
					{
						y[i][j+1]=y1[i];
					}	
				}
				else
				{	
					for(int i=0; i<var; i++)
					{
						y[i][j+1]=y[i][j];
					}
				}
			}
			else //if(f(y1)<f(Y))  //step 1
			{
				cout<<"\nf(y)= "<<func(par,var,pcoef, pdeg,Y,coef,deg)<<" > f(y+lambda*d)= "<<func(par,var,pcoef, pdeg,y1,coef,deg);
				cout<<" ---> Termination success :D\n";
				for(int i=0; i<var; i++)
				{
					y[i][j+1]=y1[i];
					Y[i]=y1[i];
			}					
			}
			if(j<var-1)   //step 2
			{
				j=j+1;  
			}
			else  //step 2 
			{	
				for(int i=0; i<var; i++)
				{
					Y[i]=y[i][var];
				}
				
				if(func(par,var,pcoef, pdeg,Y,coef,deg)<func(par,var,pcoef, pdeg,X,coef,deg))  //step 3
				{
					for(int i=0; i<var; i++)
					{
						y[i][0]=y[i][var]+alp*(y[i][var]-X[i]);
						X[i]=y[i][var];
					}			
					k=k+1;
					j=0;
					}
				else  //step 4
				{
					if(del>eps)  
					{
						del=del/2;
						cout<<"\nThe new Delta is "<<del<<endl;
						for(int i=0; i<var; i++)
						{
							y[i][0]=X[i];
						}
						k=k+1;
						j=0;						
					}
					else
					{
						cout<<endl<<"****************************************\n";
						cout<<"\nThe solution is: X=(";
						for(int i=0; i<var; i++)
						{
							cout<<" "<<X[i]<<" ";
						}
						cout<<")"<<endl;
						cout<<"\nf(X)= "<<func(par,var,pcoef, pdeg,X,coef,deg)<<endl<<endl;
						j=var+1;
					}
				}
			}
			cout<<"\ndelta= "<<del;
		}
	}
}


