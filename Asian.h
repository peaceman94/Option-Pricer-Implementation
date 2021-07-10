#pragma once
#include"Option.h"
#include"BinomialTree.h"
#include"MonteCarlo.h"

//Header file for Asian option pricing method implementations.
//Implements 2 methods, Monte Carlo and Binomial Option Pricing Method
class Asian :public Option
{
public:
	Asian(double interestrate, double strike, double expirytime, double volatility, double sharePrice0, double dividend, int timeStep);
	~Asian() {};

	//Call Payoff is max(AverageSharePrice - strike, 0)
	virtual double AsianPayoff(double sharePrice) = 0;
	virtual double PriceAsianOptionWithBinomialTree();

	virtual double PriceAsianOptionWithMonteCarlo(int NumberOfSimulation);


protected:
	BinomialTree myBinomialTree;
	MonteCarlo MC;
};
