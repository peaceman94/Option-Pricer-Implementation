#pragma once
#include"Asian.h"

//This class just contains the payoff for call and inherits every thing else from parent Asian option class
class AsianPut :public Asian
{
public:
	AsianPut(double interestrate, double strike, double expirytime, double volatility, double sharePrice0, double dividend, int timeStep);
	double AsianPayoff(double sharePrice);
};