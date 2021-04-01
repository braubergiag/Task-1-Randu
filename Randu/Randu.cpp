
#include <iostream>
#include <cmath>
#include "LCG.h"

unsigned long long  modulus = pow(2, 31);
int a = 65539;
int seed = 1;
inline double F1(double x)
{
	return 5 * exp(x * 14);
}
inline double F2(double x, double y)
{
	return 5 * exp(x * y * 14);
}
inline double F3(double x, double y, double z)
{
	return 5 * exp(x * y * z * 14);
}
double monteCarloEstimateF1(long int iterations, LCG& g);
double monteCarloEstimateF2(long int iterations, LCG& g);
double monteCarloEstimateF3(long int iterations, LCG& g);

inline double getValue(LCG& g) {
	return (static_cast<double>(*g++) / modulus);
};
int main()
{

	
	
	LCG g1(a, seed, modulus),g2(a,seed,modulus),g3(a,seed,modulus);
	// Iterations
	const  int n_max = 10e6;
	// Result from MATLAB
	double res1 = 4.2950e+05, res2 = 3.3282e+04, res3 = 2.8570e+03;
	//Estimations
	double MC1Res = monteCarloEstimateF1(n_max, g1);
	double MC2Res = monteCarloEstimateF2(n_max, g2);
	double MC3Res = monteCarloEstimateF3(n_max, g3);
	std::cout << "Number of interations: " << n_max << std::endl;
	std::cout << "Estimate: 1D " << MC1Res << " True value: " << res1 << " Error rate: " << (1 - res1/ MC1Res) * 100 << " % " << std::endl;
	std::cout << "Estimate: 2D " << MC2Res << " True value: " << res2 << " Error rate: " << (1 - res2 / MC2Res) * 100 << " % " << std::endl;
	std::cout << "Estimate: 3D " << MC3Res << " True value: " << res3 << " Error rate: " << (1 - res3 / MC3Res) * 100 << " % " << std::endl;
		

}

double monteCarloEstimateF1(long int iterations, LCG& g)

{
	double totalSum = 0;
	double randNum, functionVal, x;

	int iter = 0;
	for (int i = 0; i < iterations; ++i) {
		x = getValue(g);
		functionVal = F1(x);
		totalSum += functionVal;
	}
	double estimate = totalSum / iterations;
	return estimate;
}
double monteCarloEstimateF2(long int iterations, LCG& g)

{
	double totalSum = 0;
	double randNum, functionVal, x, y;

	int iter = 0;
	for (int i = 0; i < iterations; ++i) {
		x = getValue(g);
		y = getValue(g);
		functionVal = F2(x, y);
		totalSum += functionVal;
	}
	double estimate = totalSum / iterations;
	return estimate;
}
double monteCarloEstimateF3(long int iterations, LCG& g)

{
	double totalSum = 0;
	double randNum, functionVal, x, y, z;

	int iter = 0;
	for (int i = 0; i < iterations; ++i) {
		x = getValue(g);
		y = getValue(g);
		z = getValue(g);
		functionVal = F3(x, y, z);
		totalSum += functionVal;
	}
	double estimate = totalSum / iterations;
	return estimate;
}

