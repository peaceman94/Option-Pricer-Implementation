#include "EuropeanCall.h"

//This file just contains the payoff and BS function implementation. It inherits everything else from Euopean class
EuropeanCall::EuropeanCall(double interestrate, double strike, double expirytime, double volatility, double sharePrice0, double dividend, int timeStep):
European(interestrate, strike,expirytime, volatility, sharePrice0, dividend, timeStep){ }

double EuropeanCall::EuropeanPayoff(double sharePrice)
{
	if (myStrike < sharePrice)
	{
		return (sharePrice - myStrike);
	}
	else
	{
		return 0;
	}
}

double EuropeanCall::Boundary()
{
	return myStrike;
}

double EuropeanCall::PriceOptionAnalytically(void)
{
	// Parameters of Black Scholes formula. Note that this function has no input - all values are taken from member data of the base class. Since we declared all member data protected, we can access this data here
	return (CDF_normal(d1()) * mySharePrice * exp(-myDividendRate * myexpiryTime) - CDF_normal(d2()) * myStrike * exp(-myInterestRate * (myexpiryTime)));
}


