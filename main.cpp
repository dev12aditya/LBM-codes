#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ofstream results;
	int m=100,mstep=100000;
	float f1[m],f2[m],T[m],feq[m],x[m];
	float dx=1.0, dt=1.0;
	x[0]=0.0;
	for(int i=1;i<m;i++)
	{
		x[i]=x[i-1]+dx;
	}
	float csq= (dx*dx)/(dt*dt);
	float alpha=0.25;
    float omega=1.0/(alpha/(dt*csq)+0.5);
    float twall=100;
	// Initial Conditions

	for(int i=0;i<m;i++)
	{
		T[i]=0.0;
		f1[i]=0.5*T[i];
		f2[i]=0.5*T[i];
	}

	// Main Loop

	for(int ts=1;ts<mstep;ts++)
	{
		// Collision Process
		for(int i=0;i<m;i++)
		{
			T[i]=f1[i]+f2[i];
			feq[i]=0.5*T[i];						// for D1Q2 feq1=feq2=feq
			f1[i]=(1-omega)*f1[i]+omega*feq[i];
			f2[i]=(1-omega)*f2[i]+omega*feq[i];
		}

		//Streaming
		for(int i=1;i<=m-1;i++)
		{
			f1[m-i]=f1[m-i-1];
			f2[i-1]=f2[i];
		}

		//Boundary Conditions
		f1[0]=twall-f2[0];							// Constant temperature boundary condition at x=0
		f1[m]=f1[m-1];								// Adiabatic boundary condition at x=L
		f2[m]=f2[m-1];								// Adiabatic Boundary Condition at x=L
	}
	results.open("C:\\Users\\Devaditya Mohanty\\Desktop\\results.csv");
	results<<"x[i],T[i]"<<endl;
	for(int i=0;i<m;i++)
    {
        results<<x[i]<<","<<T[i]<<endl;
    }
    return 0;
}
