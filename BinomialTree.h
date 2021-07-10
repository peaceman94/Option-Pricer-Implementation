#pragma once
#include"BinomialTreeNode.h"

class BinomialTree
{
public:
	BinomialTree(double volatility, double timestep, double SharePrice0, double rate,double expiryTime);
	double mytimestep;
	double myProbability;
	double mydelta_t;
	double myStepUp;
	double myStepDown;

	double GetSharePrice(unsigned int time, unsigned int latticeIndex) const;

	//Just used for Asian option calculation (see more comment on cpp file)
	BinomialTreeNode * MakeTreeNode(const double& element, BinomialTreeNode * parent);

private:
	double myvolatility;
	double mySharePrice0;
	double myrate;
};
