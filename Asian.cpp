#include"Asian.h"
#include"MonteCarlo.h"
#include<vector>
#include<iostream>


Asian::Asian(double interestrate, double strike, double expirytime, double volatility, double sharePrice0, double dividend, int timeStep) :
	Option(interestrate, strike, expirytime, volatility, sharePrice0, dividend, timeStep), myBinomialTree(volatility, timeStep, sharePrice0, interestrate, expirytime) {}

// Binomial Tree pricing method:
double Asian::PriceAsianOptionWithBinomialTree()
{
	//We process the nodes layer by layer up until mytimesteps (BFS style). This increases memory usage but
	//makes the code very streamlined
	
	//Generate a binary tree
	BinomialTreeNode * TreeRoot = myBinomialTree.MakeTreeNode(mySharePrice, 0);  //set current share price as root for obvious reasons
	vector<BinomialTreeNode *> Nodes = { TreeRoot };  //This is used to store the nodes
	//Nodes vector would be iterated over, this PreviousNode is just the variable we use to keep track of current nodes
	vector<BinomialTreeNode *> PreviousNodes = Nodes;
	
	// i represents the current level of the binary tree exploration we are i - as notes we do breath fiirst search
	for (int i = 0; i < mytimeSteps; i++)    
	{
		//Nodes store the most recent level of nodes we hae explored. It should be reseted every loop
		Nodes.clear();    

		//for each node in the previous node, explore up_shareprice and dowun_shareprice
		vector<BinomialTreeNode *>::iterator it = PreviousNodes.begin();
		for (it; it != PreviousNodes.end(); it++)
		{
			//Get up and down nodes as mentioned in the above comment
			BinomialTreeNode *currentNode = *it;   
			BinomialTreeNode * LeftNode = myBinomialTree.MakeTreeNode(currentNode->data*myBinomialTree.myStepDown, currentNode);
			BinomialTreeNode * RightNode = myBinomialTree.MakeTreeNode(currentNode->data*myBinomialTree.myStepUp, currentNode);
			Nodes.push_back(LeftNode);
			Nodes.push_back(RightNode);
		}
		PreviousNodes = Nodes;
	}

	//For each node, traverse all the way up to parent node and find the average for each path. Sgtore the payoff.

	vector<double> Payoff_of_AsianOption;
	for (int i = 0; i < pow(2, mytimeSteps); i++)    //This "for" loop is traversing every point of "previousnodes"
	{
		double sum = 0;   //Each point of the "previousnodes" must be traced upwards, and the value of all nodes on the path is accumulated, and the sum is stored in the "sum"
		BinomialTreeNode * current = PreviousNodes[i];
		for (int j = mytimeSteps; j >= 0; j--)   //This loop is to use "Parent" pointer to trace back to the upper layer and sum
		{
			sum += current->data;
			current = current->Parent;
		}
		double average = sum / (mytimeSteps + 1);
		Payoff_of_AsianOption.push_back(AsianPayoff(average));
	}

	//recursively find the payoff (discounted) and return.
	std::vector<double> previousOptionValue = Payoff_of_AsianOption;

	//Since the level number of the binary tree is "mytimeSteps + 1", it is necessary to discount "mytimeSteps" forward
	for (int n = mytimeSteps; n > 0; n--)
	{
		Payoff_of_AsianOption.clear();
		for (int i = 0; i < pow(2, n); )   //This "for" loop is to traverse each node of the current layer, the number of nodes in the nth layer is pow (2, n)
		{
			Payoff_of_AsianOption.push_back((myBinomialTree.myProbability * previousOptionValue[i + 1] + (1 - myBinomialTree.myProbability) * previousOptionValue[i]) *exp(-myInterestRate * myBinomialTree.mydelta_t));
			i += 2;
		}
		previousOptionValue = Payoff_of_AsianOption;
	}
	return Payoff_of_AsianOption[0];
}


// Monte Carlo pricing method:
double Asian::PriceAsianOptionWithMonteCarlo(int NumberOfSimulation)
{
	//Sample once per day
	double delta_t = 1.0 / 365;    
	double Sum_Of_Payoff_Of_Simulate = 0;
	
	//Run the simulation for a total of NumberOfSimulation times
	for (int i = 0; i < NumberOfSimulation; i++)   
	{
		double Sum_Of_EachDaySimulate = mySharePrice;
		double SimulateEachDayPrice = mySharePrice;

		//Sample eachsd day and take the average
		for (int n = 1; n < myexpiryTime * 365; n++)   
		{
			SimulateEachDayPrice = SimulateEachDayPrice * exp((myInterestRate - myVolatility * myVolatility / 2)*delta_t + myVolatility * MC.MC()*sqrt(delta_t));
			Sum_Of_EachDaySimulate += SimulateEachDayPrice;
		}
		Sum_Of_Payoff_Of_Simulate += exp(-myInterestRate * myexpiryTime)*AsianPayoff(Sum_Of_EachDaySimulate / (myexpiryTime * 365));
	}
	double Average = Sum_Of_Payoff_Of_Simulate / NumberOfSimulation;
	return Average;
}


