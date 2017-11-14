
#include"Hindmarsh_Rose.h"


Hindmarsh_Rose::Hindmarsh_Rose(double a, double b, double r, double s, double xr, double tal)
{
	this->a=a;
	this->b=b;
	this->r=r;
	this->s=s;
	this->xr=xr;
	this->tal=tal;

	restingState();
}

Hindmarsh_Rose::~Hindmarsh_Rose()
{

}

//set the neuron to resting state
void Hindmarsh_Rose::restingState()
{
	x=xr;
	y=0.0;
	z=0.0;

	int i=0;
	for(i=0;i<1000;++i)
	{
		this->iterate(0.0);
	}
}

double Hindmarsh_Rose::iterate(double input)
{
	I= input;

	if(I>10.0)
	{
		I=10.0;
		printf("ERROR: I>10\n");
	}
	if(I<-10.0)
	{
		I=-10.0;
		printf("ERROR: I<-10\n");
	}

	double dx;
	double dy;
	double dz;

	dx= tal*(+y -x*x*x +b*x*x -z + I);
	dy= tal*(1.0 - a*x*x -y);
	dz= tal*(r*( s*(x - xr) -z));

//	dx= y -x*x*x +b*x*x + I -z;
//	dy= 0.0 + a*x*x -y;
//	dz= r*( s*(x - xr) -z);

	x+=dx;
	y+=dy;
	z+=dz;

	return x;
}
