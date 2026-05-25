#pragma once
#include <random>

class RandomGenerator
{
private:
	std::mt19937 generator;
	std::normal_distribution<double> norm_distribution;

public:
	RandomGenerator(unsigned int seed) :
		generator(seed), norm_distribution(0.0, 1.0) 
	{ }

	double get_random()
	{
		return this->norm_distribution(generator);
	}
};