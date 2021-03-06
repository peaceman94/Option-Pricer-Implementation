#include "AsianCall.h"

//This class just contains the payoff function. It inherits everything from parent class
AsianCall::AsianCall(double interestrate, double strike, double expirytime, double volatility, double sharePrice0, double dividend, int timeStep) :
	Asian(interestrate, strike, expirytime, volatility, sharePrice0, dividend, timeStep) { }

double AsianCall::AsianPayoff(double sharePrice)
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