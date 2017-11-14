
#include"Integrate_Fire.h"

Integrate_Fire::Integrate_Fire(double threshold, double discretization_time)
{
	this->discretization_time= discretization_time;

	v=0.0;
	this->threshold=threshold;
	//restingState();
}

Integrate_Fire::~Integrate_Fire()
{

}

//set the neuron to resting state
void Integrate_Fire::restingState()
{
	v=0.0;

	int i=0;
	for(i=0;i<1000;++i)
	{
		this->iterate(0.0);
	}
}

//I is the input
double Integrate_Fire::iterate(double I)
{
	double dv= (discretization_time)*(-v + I);

	v+=dv;

	if(v > threshold)
	{
		v=0.0;
		return 1.0;
	}
	else
	{
		return 0.0;
	}
}
