#include "BinomialTree.h"
#include <cmath>
#include <iostream>

//This class initializes the paramenters for binomial tree based off the input parameters. It uses Cox Ross Rubinstiens formulation
//of the trees and risk nuetral probabilities.

BinomialTree::BinomialTree(double volatility, double timestep, double SharePrice0, double rate, double expiryTime) :
	myvolatility(volatility), mytimestep(timestep), mySharePrice0(SharePrice0), myrate(rate)
{
	mydelta_t = expiryTime / timestep;
	myStepUp = exp(myvolatility*sqrt(mydelta_t));
	myStepDown = exp(-myvolatility * sqrt(mydelta_t));
	myProbability = (exp(myrate*mydelta_t) - myStepDown) / (myStepUp - myStepDown);
}

double BinomialTree::GetSharePrice(unsigned int time, unsigned int latticeIndex) const
{
	return mySharePrice0 * pow(myStepUp, latticeIndex) * pow(myStepDown, time - latticeIndex);
}

//This is just used in Asian option calculation as we need to take average for each path and for keeping track of each path
//we need to keep track of parent node
BinomialTreeNode * BinomialTree::MakeTreeNode(const double& element, BinomialTreeNode * parent)
{
	BinomialTreeNode * Node = new BinomialTreeNode(element, parent);
	return Node;
}

