#include<iostream>
#include"BinomialTree.h"
#include"Option.h"
#include"European.h"
#include"EuropeanCall.h"
#include"EuropeanPut.h"
#include"Asian.h"
#include"AsianCall.h"
#include"AsianPut.h"

using namespace std;

int main(void)
{
	double InterestRate = 0.05;
	double strike = 100;
	double volatility = 0.3;
	double expirytime = 1.0;
	int timestep = 18;
	double dividend = 0.01;
	double sharePrice = 100;
	
	cout << "European Call Option Price:" << endl;
	EuropeanCall A1(InterestRate, strike, expirytime, volatility, sharePrice, dividend, timestep);
	//Compare the 3 prices
	cout << "    Black Scholes Analytical:   " << A1.PriceOptionAnalytically() << endl;
	cout << "    Binomial Tree Pricer:  " << A1.PriceEuropeanOptionWithBinomialTree() << endl;
	cout << "    Monte Carlo Pricer:  " << A1.PriceEuropeanOptionWithMonteCarlo(10000) << endl;


	cout << endl;
	cout << "European Put Option Price:" << endl;
	EuropeanPut A2(InterestRate, strike, expirytime, volatility, sharePrice, dividend, timestep);
	cout << "    Black Scholes Analytical:   " << A2.PriceOptionAnalytically() << endl;
	cout << "    Binomial Tree Pricer:  " << A2.PriceEuropeanOptionWithBinomialTree() << endl;
	cout << "    Monte Carlo Pricer:  " << A2.PriceEuropeanOptionWithMonteCarlo(10000) << endl;

	cout << endl;
	cout << "Asian Call Option Price:" << endl;
	AsianCall AS1(InterestRate, strike, expirytime, volatility, sharePrice, dividend, timestep);
	cout << "    Binomial Tree Pricer:   " << AS1.PriceAsianOptionWithBinomialTree() << endl;
	cout << "    Monte Carlo Pricer:  " << AS1.PriceAsianOptionWithMonteCarlo(10000) << endl;

	cout << endl;
	cout << "Asian Put Option Price:" << endl;
	AsianPut AS2(InterestRate, strike, expirytime, volatility, sharePrice, dividend, timestep);
	cout << "    Binomial Tree Pricer:   " << AS2.PriceAsianOptionWithBinomialTree() << endl;
	cout << "    Monte Carlo Pricer:  " << AS2.PriceAsianOptionWithMonteCarlo(10000) << endl;

	return 0;
}


