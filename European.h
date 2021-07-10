#pragma once
#include"Option.h"
#include"BinomialTree.h"
#include"MonteCarlo.h"

class European:public Option
{   
public:
	European(double interestrate, double strike, double expirytime, double volatility, double sharePrice0, double dividend, int timeStep);
	~European() {};

	//payoff for call = max(sharePrice - strike, 0)
	virtual double EuropeanPayoff(double sharePrice) =0;

	// Binomial Tree pricing method
	virtual double PriceEuropeanOptionWithBinomialTree(void);

	// Monte Carlo pricing method
	double PriceEuropeanOptionWithMonteCarlo(int NumberOfSimulation);

protected:
	BinomialTree myBinomialTree;
	MonteCarlo MC;

	// BS analytical formulation parameters
	double CDF_normal(double x);
	double d1(void) { return 1.0 / myVolatility / sqrt(myexpiryTime) * (log(mySharePrice / myStrike) + (myInterestRate - myDividendRate + myVolatility * myVolatility / 2.0) * (myexpiryTime)); }
	double d2(void) { return d1() - myVolatility * sqrt(myexpiryTime); };
};
