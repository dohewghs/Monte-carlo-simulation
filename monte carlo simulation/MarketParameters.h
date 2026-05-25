#pragma once

struct MarketParameters
{
	double initial_price;
	double strike_price;
	double volatility;
	double risk_rate;
	double cycles;
	int iter_per_cycle;

	MarketParameters():
		initial_price(100),
		strike_price(110),
		volatility(0.2),
		risk_rate(0.05),
		cycles(1),
		iter_per_cycle(365)
	{ }

	MarketParameters(double _initial_price, double _strike_price, double _volatility, double _risk_rate, double _cycles, int _iter_per_cycle):
		initial_price(_initial_price),
		strike_price(_strike_price),
		volatility(_volatility),
		risk_rate(_risk_rate),
		cycles(_cycles),
		iter_per_cycle(_iter_per_cycle)
	{ }
};