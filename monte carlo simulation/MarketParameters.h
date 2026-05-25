#pragma once

struct MarketParameters
{
	double initial_price;
	double strike_price;
	double volatility;
	double risk_rate;
	double cycles;
	int iter_per_cycle;
	double simulations_count;

	MarketParameters():
		initial_price(100),
		strike_price(110),
		volatility(0.2),
		risk_rate(0.05),
		cycles(1),
		iter_per_cycle(365),
		simulations_count(1e6)
	{ }
};