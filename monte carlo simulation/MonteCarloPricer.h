#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include "MarketParameters.h"
#include "RandomGenerator.h"
#include "PathPriceSimulator.h"

class MonteCarloPricer
{
private:
	MarketParameters parameters;
	int total_simulations;
	int theads_count;

	double global_payoff_sum;
	std::mutex mutex;

	void thread_worker(int simulations_to_run, int thread_id)
	{
		unsigned int seed = std::random_device{}() + thread_id; // !!!!!!
		RandomGenerator()
	}
public:

};