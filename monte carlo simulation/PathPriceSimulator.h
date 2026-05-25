#pragma once
#include "MarketParameters.h"
#include "RandomGenerator.h"
#include <cmath>

class PathPriceSimulator
{
private:
	MarketParameters parameters;

public:
	PathPriceSimulator(const MarketParameters& p) : 
		parameters(p) 
	{ }

	double simulate_final_price(RandomGenerator& generator) const
	{
		double price = this->parameters.initial_price;
		double deltaTime = this->parameters.cycles / this->parameters.iter_per_cycle;

		double drift = (parameters.risk_rate - (parameters.volatility * parameters.volatility) / 2.0) * deltaTime;
		double diffusion = parameters.volatility * std::sqrt(deltaTime);

		for (int i = 0; i < parameters.iter_per_cycle; ++i)
		{
			double z = generator.get_random();
			
			price = price * std::exp(drift + diffusion * z);
		}

		return price;
	}

	double calculate_payoff(double final_price) const 
	{
		return std::max(final_price - parameters.strike_price, 0.0);
	}
};