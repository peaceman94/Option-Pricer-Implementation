#include<iostream>
#include"BinomialTree.h"
#include"Option.h"
#include"European.h"
#include"EuropeanCall.h"
#include"EuropeanPut.h"
#include"Asian.h"
#include"AsianCall.h"
#include"AsianPut.h"

#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

int plot_func( vector<double> xs, vector<double> xs2, vector<double> ys, vector<double> ys2, string fileName,
	vector<wchar_t>* title, vector<wchar_t>* xLable, vector<wchar_t>* yLable, bool plotSecond = true){

	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &xs;
	series->ys = &ys;
	series->linearInterpolation = true;
	series->lineType = toVector(L"dashed");
	series->lineThickness = 2;
	series->pointType = toVector(L"dots");
	series->color = CreateRGBColor(1, 0, 0);

	ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &xs;
	series2->ys = &ys2;
	series2->linearInterpolation = true;
	series2->lineType = toVector(L"dashed");
	series2->lineThickness = 2;
	series2->pointType = toVector(L"dots");
	series2->color = CreateRGBColor(0, 0, 1);
	
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = title;
	settings->xLabel = xLable;
	settings->yLabel = yLable;
	settings->scatterPlotSeries->push_back(series);

	if(plotSecond)
		settings->scatterPlotSeries->push_back(series2);

	DrawScatterPlotFromSettings(imageReference, settings);

	vector<double> *pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, fileName);
	DeleteImage(imageReference->image);

	return 0;
}

int main(void)
{
	double InterestRate = 0.05;
	double strike = 100;
	double volatility = 0.3;
	double expirytime = 1.0;
	int timestep = 20;
	double dividend = 0.01;
	double sharePrice = 100;
	
	//levers to pull to decide what to run
	bool run_all_pricers = false;
	bool plot_exp = true;
	bool plot_tsteps = true;
	bool plot_strike = true;
	bool plot_mc_sims = true;
	if(run_all_pricers)
	{
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
	}
	

	//various graphs for Asian Options
	if(plot_exp)
	{
		//1. Sensitivity To Expiry
		vector<double> expiries = {(double)1/2, (double)3/4, (double)1, (double)2, 3};
		vector<double> option_prices_binomial_tree = {};
		vector<double> option_prices_monte_carlo = {};

		for(auto analysis_exp: expiries)
		{
			AsianCall AS_Analysis(InterestRate, strike, analysis_exp, volatility, sharePrice, dividend, timestep);
			double curr_price_binomial_tree = AS_Analysis.PriceAsianOptionWithBinomialTree();
			double curr_price_monte_carlo = AS_Analysis.PriceAsianOptionWithMonteCarlo(10000);
			option_prices_binomial_tree.push_back(curr_price_binomial_tree);
			option_prices_monte_carlo.push_back(curr_price_monte_carlo);

			cout << "Expiry (in yrs): " << analysis_exp << "\t" << "binomial price: " <<  curr_price_binomial_tree << "\t";
			cout << "monte carlo price: " << curr_price_monte_carlo << endl;
		}

		auto title = toVector(L"Asian Call Option Price Vs Expiry");
		auto xLable = toVector(L"Expiry (yrs)");
		auto yLable = toVector(L"Price ($)");
		string fileName = "Asian_Price_Vs_Expiry.png";
		plot_func(expiries, expiries, option_prices_binomial_tree, option_prices_monte_carlo, fileName, title, xLable, yLable);
	}
	

	if(plot_tsteps)
	{
		//2. Sensitivity To Timesteps
		vector<double> timesteps = {2,3,4,5,7, 10, 12, 15, 17, 20, 23, 25};
		vector<double> option_prices_binomial_tree_tsteps = {};
		for(auto analysis_tsteps: timesteps)
		{
			AsianCall AS_Analysis(InterestRate, strike, expirytime, volatility, sharePrice, dividend, analysis_tsteps);
			double curr_price_binomial_tree = AS_Analysis.PriceAsianOptionWithBinomialTree();
			option_prices_binomial_tree_tsteps.push_back(curr_price_binomial_tree);
			cout << "timesteps: " << analysis_tsteps << "\t" << "binomial price: " <<  curr_price_binomial_tree << endl;
		}
		auto title = toVector(L"Asian Call Option Price Vs Timesteps");
		auto xLable = toVector(L"Timesteps");
		auto yLable = toVector(L"Price ($)");
		string fileName = "Asian_Price_Vs_Timesteps.png";
		plot_func(timesteps, {}, option_prices_binomial_tree_tsteps, {}, fileName, title, xLable, yLable, false);
	}
	
	if(plot_strike)
	{
		vector<double> strikes = {50, 60, 75, 90, 100, 110, 125, 140, 150};
		vector<double> option_prices_binomial_tree_strikes = {};
		vector<double> option_prices_monte_carlo_strikes = {};
		for(auto analysis_strike: strikes)
		{
			AsianCall AS_Analysis(InterestRate, analysis_strike, expirytime, volatility, sharePrice, dividend, timestep);
			double curr_price_binomial_tree = AS_Analysis.PriceAsianOptionWithBinomialTree();
			double curr_price_monte_carlo = AS_Analysis.PriceAsianOptionWithMonteCarlo(10000);
			option_prices_binomial_tree_strikes.push_back(curr_price_binomial_tree);
			option_prices_monte_carlo_strikes.push_back(curr_price_monte_carlo);
			cout << "Strike: " << analysis_strike << "\t" << "binomial price: " <<  curr_price_binomial_tree << "\t";
			cout << "monte carlo price: " << curr_price_monte_carlo << endl;
		}

		auto title = toVector(L"Asian  Call Option Price Vs Strike");
		auto xLable = toVector(L"Strike");
		auto yLable = toVector(L"Price");
		string fileName = "Asian_Price_Vs_Strike.png";
		plot_func(strikes, strikes, option_prices_binomial_tree_strikes, option_prices_monte_carlo_strikes, fileName, title, xLable, yLable);
	}

	if(plot_mc_sims)
	{
		vector<double> num_of_sims = {100, 500, 1000, 2000, 5000, 7000, 10000, 12000, 15000, 17000, 20000};
		vector<double> option_prices_monte_carlo_sims = {};
		AsianCall AS_Analysis(InterestRate, strike, expirytime, volatility, sharePrice, dividend, timestep);
		for(auto num_of_sim: num_of_sims)
		{
			double curr_price_monte_carlo = AS_Analysis.PriceAsianOptionWithMonteCarlo(num_of_sim);
			option_prices_monte_carlo_sims.push_back(curr_price_monte_carlo);
			cout << "# of simulations: " << num_of_sim << "\t" << "Monte Carlo price: " <<  curr_price_monte_carlo << endl;
		}

		auto title = toVector(L"Asian Call Option Price Vs Monte Carlo Simulations");
		auto xLable = toVector(L"# of smulations");
		auto yLable = toVector(L"Price");
		string fileName = "Asian_Price_Vs_MCSims.png";
		plot_func({}, num_of_sims, {}, option_prices_monte_carlo_sims, fileName, title, xLable, yLable, true);
	}

	return 0;
}
