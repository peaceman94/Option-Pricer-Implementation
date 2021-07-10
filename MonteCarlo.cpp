#include"MonteCarlo.h"

//Just generates the std n random number to be used in monte carlo pricing 
double MonteCarlo::MC()
{
	random_device rd;
	mt19937 random_generator(rd());
	normal_distribution <double> distribution(0, 1);
	return distribution(random_generator);
}