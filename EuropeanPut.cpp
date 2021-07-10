#include "EuropeanPut.h"

//This file just contains the payoff and BS function implementation. It inherits everything else from Euopean class
EuropeanPut::EuropeanPut(double interestrate, double strike, double expirytime, double volatility, double sharePrice0, double dividend, int timeStep) :
	European(interestrate, strike, expirytime, volatility, sharePrice0, dividend, timeStep) { }

double EuropeanPut::EuropeanPayoff(double sharePrice)
{
	if (myStrike > sharePrice)
	{
		return ( myStrike- sharePrice);
	}
	else
	{
		return 0;
	}
}

double EuropeanPut::Boundary()
{
	return 0;
}

double EuropeanPut::PriceOptionAnalytically(void)
{
	//This just calulates the option price based off the closed formulation for Black Scholes Model
	return (CDF_normal(-d2()) * myStrike * exp(-myInterestRate * (myexpiryTime))- CDF_normal(-d1()) * mySharePrice * exp(-myDividendRate * myexpiryTime));
}