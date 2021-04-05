
#include <iostream>
#include <cmath>
#include "LCG.h"
#include <random>
#include <chrono>
#include <iomanip>
unsigned long long  modulus = pow(2, 31);
int a = 65539;
int seedRandu = 1;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);
std::uniform_real_distribution<double> dist(0.0, 1.0);


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
std::vector<double> monteCarloEstimateF1(long int iterations, LCG& g);
std::vector<double> monteCarloEstimateF2(long int iterations, LCG& g);
std::vector<double> monteCarloEstimateF3(long int iterations, LCG& g);

inline double getValue(LCG& g) {
	return (static_cast<double>(*g++) / modulus);
};

int main()
{

	
	
	LCG g1(a, seedRandu, modulus),g2(a, seedRandu,modulus),g3(a, seedRandu,modulus);
	// Iterations
	const  int n_max = 10e6;

	// Result from MATLAB
	// double res1 = 4.2950e+05, res2 = 3.3282e+04, res3 = 2.8570e+03;

	
	

	std::vector<double> MC1Res = monteCarloEstimateF1(n_max, g1);
	std::vector<double> MC2Res = monteCarloEstimateF2(n_max, g2);
	std::vector<double> MC3Res = monteCarloEstimateF3(n_max, g3);
	std::cout << "Number of interations: " << n_max << std::endl;
	std::cout << "Randu estimate: 1D " << std::setw(10) <<MC1Res.at(0) << "| Mt estimate: " <<std::setw(10) << MC1Res.at(1) << std::setw(10) << " Error : " << std::setw(10) <<  abs(MC1Res.at(0) - MC1Res.at(1))/ MC1Res.at(1)  * 100  << " % " <<  std::endl;
	std::cout << "Randu estimate: 2D " << std::setw(10) <<MC2Res.at(0) << "| Mt estimate: " <<  std::setw(10) << MC2Res.at(1) << std::setw(10) << " Error : " << std::setw(10) << abs(MC2Res.at(0) - MC2Res.at(1))/ MC2Res.at(1)  * 100  << " % " <<  std::endl;
	std::cout << "Randu estimate: 3D " << std::setw(10) << MC3Res.at(0) << "| Mt estimate: " <<  std::setw(10) << MC3Res.at(1) << std::setw(10) << " Error : " << std::setw(10) << abs(MC3Res.at(0) - MC3Res.at(1)) / MC3Res.at(1)  * 100 << " % " << std::endl;
		

}

std::vector<double> monteCarloEstimateF1(long int iterations, LCG& g)

{
	double totalSum1 = 0,totalSum2 = 0;
	double randNum, functionVal1, functionVal2 ,x1,x2;

	
	for (int i = 0; i < iterations; ++i) {
		x1 = getValue(g);
		x2 = dist(generator);
		functionVal1 = F1(x1);
		functionVal2 = F1(x2);
		totalSum1 += functionVal1;
		totalSum2 += functionVal2;
	}
	double estimate1 = totalSum1 / iterations;
	double estimate2 = totalSum2 / iterations;
	std::vector<double> estimate;
	estimate.push_back(estimate1);
	estimate.push_back(estimate2);
	return estimate;
}
std::vector<double> monteCarloEstimateF2(long int iterations, LCG& g)

{
	double totalSum1 = 0, totalSum2 = 0;
	double functionVal1, functionVal2, x1, y1, x2, y2;


	for (int i = 0; i < iterations; ++i) {
		x1 = getValue(g); x2 = dist(generator);
		y1 = getValue(g); y2 = dist(generator);
		functionVal1 = F2(x1, y1);
		functionVal2 = F2(x2, y2);
		totalSum1 += functionVal1;
		totalSum2 += functionVal2;
	}
	double estimate1 = totalSum1 / iterations;
	double estimate2 = totalSum2 / iterations;
	std::vector<double> estimate;
	estimate.push_back(estimate1);
	estimate.push_back(estimate2);
	return estimate;
}
std::vector<double> monteCarloEstimateF3(long int iterations, LCG& g)

{
	double totalSum1 = 0, totalSum2 = 0;
	double functionVal1, functionVal2, x1,y1,z1, x2,y2,z2;

	for (int i = 0; i < iterations; ++i) {
		x1 = getValue(g); x2 = dist(generator);
		y1 = getValue(g); y2 = dist(generator);
		z1 = getValue(g); z2 = dist(generator);
		functionVal1 = F3(x1, y1, z1);
		functionVal2 = F3(x2, y2, z2);
		totalSum1 += functionVal1;
		totalSum2 += functionVal2;
	}
	double estimate1 = totalSum1 / iterations;
	double estimate2 = totalSum2 / iterations;
	std::vector<double> estimate;
	estimate.push_back(estimate1);
	estimate.push_back(estimate2);
	return estimate;
}

