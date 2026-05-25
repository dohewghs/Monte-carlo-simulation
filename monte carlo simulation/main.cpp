#include "MonteCarloPricer.h"
#include <chrono>

int main()
{
    MarketParameters params{
        100.0,  // Початкова ціна S0
        110.0,  // Страйк K
        0.20,   // Волатильність 20%
        0.05,   // Ставка 5%
        1.0,    // 1 рік
        365     // Кроків моделювання
    };

    int total_simulations = 10000000;
    int threads_count = std::thread::hardware_concurrency(); 

    if (threads_count == 0) 
        threads_count = 4;

    std::cout << "Starting Monte Carlo simulation with " << threads_count << " threads...\n";
    
    MonteCarloPricer pricer(params, total_simulations, threads_count);
	
    auto start_time = std::chrono::high_resolution_clock::now();

    double price = pricer.calc_option_price();

    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "---------------------------------------\n";
    std::cout << "Estimated Option Price: " << price << "\n";
    std::cout << "Execution Time: " << duration << " ms\n";
    std::cout << "---------------------------------------\n";
    return 0;
}