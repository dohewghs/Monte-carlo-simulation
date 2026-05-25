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
		RandomGenerator gen(seed);

		PathPriceSimulator* simulator = new PathPriceSimulator(parameters);

		double local_payoff = 0.0;

		for (int i = 0; i < simulations_to_run; ++i)
		{
			double final_price = simulator->simulate_final_price(gen);

			local_payoff += simulator->calculate_payoff(final_price);
		}

		{
			std::lock_guard<std::mutex> lock_guard(mutex);

			this->global_payoff_sum += local_payoff;
		}
	}

public:
	MonteCarloPricer(const MarketParameters& p, int sims, int threads): 
		parameters(p),
		total_simulations(sims), 
		theads_count(threads),
		global_payoff_sum(0.0) 
	{ }

	double calc_option_price()
	{
		global_payoff_sum = 0.0;

		std::vector<std::thread> threads;

		int sims_per_thread = total_simulations / theads_count;

		for (int i = 0; i < theads_count; ++i)
		{
			threads.push_back(
				std::thread(&MonteCarloPricer::thread_worker, this, sims_per_thread, i)
			);
		}

		for (auto& thread : threads)
		{
			if (thread.joinable())
				thread.join();
		}

		double average_payoff = global_payoff_sum / total_simulations;
		double option_price = average_payoff * std::exp(-parameters.risk_rate * parameters.cycles);

		return option_price;
	}
};