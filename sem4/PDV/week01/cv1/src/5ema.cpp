#include "../pdv_lib/pdv_lib.hpp"
#include <cstdlib>
#include <fstream>
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <thread>
#include <random>

// Vygenerujeme náhodná data ceny akcii v čase.
// Formát je následující: 
// Vector jednolivých akcií obsahující ceny za jednotlivé dny.
std::vector<std::vector<double>> generate_random_stock_data(size_t num_days, size_t num_stocks) {
    std::vector<std::vector<double>> stock_prices(num_days);
    pdv::uniform_random<double> random(0, 10000);

    for (auto& day : stock_prices) {
        day.resize(num_stocks);
        for (auto& price : day) {
            price = random();
        }
    }
    return stock_prices;
}

// Implementace exponenciálního klouzavého průměru.
// Vstupní data jsou ceny akcií v čase.
// Alpha je váha, která určuje, jak moc se má brát v úvahu nová data.
std::vector<double> exponential_moving_average(const std::vector<double>& data, double alpha) {
    std::vector<double> result(data.size());
    result[0] = data[0];
    for (size_t i = 1; i < data.size(); i++) {
        result[i] = alpha * data[i] + (1 - alpha) * result[i - 1];
    }
    return result;
}

int main() {
    // Vygenerujeme nahodna data vyvoje ceny akcii v case.
    auto stock_prices = generate_random_stock_data(100000, 1000);

    // Zajistime, ze vypocet kompilator nezoptimalizuje pres hranici benchmarku.
    stock_prices = pdv::launder_value(stock_prices);
    pdv::benchmark("Exponential Moving Average serial", [&] {

        std::vector<std::vector<double>> ema_prices(stock_prices.size());

        for (size_t i = 0; i < stock_prices.size(); i++) {
            ema_prices[i] = exponential_moving_average(stock_prices[i], 0.1);
        }
        pdv::do_not_optimize_away(ema_prices);
    });


    return 0;
}
