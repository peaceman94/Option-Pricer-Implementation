#include"European.h"
#include<vector>
#include<iostream>

European::European(double interestrate, double strike, double expirytime, double volatility, double sharePrice0, double dividend, int timeStep) :
	Option(interestrate, strike, expirytime, volatility, sharePrice0, dividend, timeStep) , myBinomialTree(volatility, timeStep, sharePrice0, interestrate,expirytime){}

double European::CDF_normal(double x)
{
	return 0.5 * erfc(-x / sqrt(2));
}

// Binomial Tree pricing method
double European::PriceEuropeanOptionWithBinomialTree(void)
{
	std::vector<double> currentPrice(myBinomialTree.mytimestep + 1, 0);
	for (int i = 0; i < myBinomialTree.mytimestep + 1; ++i)
	{
		currentPrice[i] = EuropeanPayoff(myBinomialTree.GetSharePrice(myBinomialTree.mytimestep, i));
	}

	std::vector<double> previousPrices = currentPrice;
	for (int n = myBinomialTree.mytimestep - 1; n >= 0; n--)
	{
		for (int i = 0; i < n + 1; i++)
		{
			currentPrice[i] = (myBinomialTree.myProbability * previousPrices[i + 1] + (1 - myBinomialTree.myProbability) * previousPrices[i]) *exp(-myInterestRate * myBinomialTree.mydelta_t);
		}
		
		previousPrices = currentPrice;
	}
	return currentPrice[0];
}

// Monte Carlo pricing method
double European::PriceEuropeanOptionWithMonteCarlo(int NumberOfSimulation)
{
	double SimulateSharePrice;
	double Sum_Of_Payoff_Of_Simulate = 0;
	for (int i = 0; i < NumberOfSimulation; i++)
	{
		SimulateSharePrice = mySharePrice * exp((myInterestRate - myVolatility * myVolatility / 2)*myexpiryTime + myVolatility * MC.MC()*sqrt(myexpiryTime));
		Sum_Of_Payoff_Of_Simulate += exp(-myInterestRate * myexpiryTime)*EuropeanPayoff(SimulateSharePrice);
	}
	double Average = Sum_Of_Payoff_Of_Simulate / NumberOfSimulation;
	return Average;
}


