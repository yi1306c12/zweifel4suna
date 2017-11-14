
#ifndef FITZHUGH_NAGUMO_H
#define FITZHUGH_NAGUMO_H

#include"../Dynamics.h"
#include"stdio.h"

class FitzHugh_Nagumo: public Dynamics
{
	public:
		FitzHugh_Nagumo(double a, double b, double tal, double discretization_time);
		~FitzHugh_Nagumo();

		double iterate(double input);

		void restingState();

		double a;
		double b;
		double tal;
		double discretization_time;
		double I;

		double v;
		double w;
};

#endif

