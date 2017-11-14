#include"Ripple.h"

Ripple::Ripple(int problem_size)
{
	this->problem_size= problem_size;
}

Ripple::~Ripple()
{

}


double Ripple::objectiveFunction(double* chromossome)
{
	int i;
	double sum= 0.0;
	
	for(i=0; i< problem_size ;++i)
	{
		sum+= chromossome[i]*chromossome[i];
	}
	sum= sin(sum);

	return sqrt(sum);
}
		
double Ripple::printDetails(double* variables)
{
	return 0;
}
