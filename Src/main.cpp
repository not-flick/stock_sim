#include <iostream>
#include <matplot/matplot.h>
#include <random>
#include <vector>
#include <numeric>
#include <thread>
#include <chrono>


//debug


using namespace matplot;

std::mt19937 rng(std::random_device{}());

std::normal_distribution<float> money_dist(
    10000.f,
    2500.f
);

class Trader {
public:
    float money;
    float impulsiveness;
    float bid;

    Trader()
    {
        money = money_dist(rng);

        impulsiveness =
            std::uniform_real_distribution<float>(
                -0.1f,
                 0.1f
            )(rng);

        bid = 0.f;
    }

    void UpdateBid(float current_price)
    {
        float mood =
            std::uniform_real_distribution<float>(
                -0.05f,
                 0.05f
            )(rng);

        bid = current_price *
              (1.f + impulsiveness + mood);
    }
};

class Nvidia {
public:
    float init_price = 100.f;

    std::vector<float> bid_prices;
    std::vector<double> history;

    float GetPrice() const
    {
        if (bid_prices.empty())
            return init_price;

        return std::accumulate(
            bid_prices.begin(),
            bid_prices.end(),
            0.f
        ) / bid_prices.size();
    }
};

int main()
{
    std::vector<Trader> market;

    for (int i = 0; i < 100; i++)
    {
        market.emplace_back();
    }

    Nvidia nvidia;

    auto fig = figure(true);

    while (true)
    {
        nvidia.bid_prices.clear();

        float current_price = nvidia.GetPrice();

        for (Trader& trader : market)
        {
            trader.UpdateBid(current_price);
            nvidia.bid_prices.push_back(trader.bid);
        }

        nvidia.history.push_back(nvidia.GetPrice());

        if (nvidia.history.size() > 500)
        {
            nvidia.history.erase(nvidia.history.begin());
        }

        clf();

        plot(nvidia.history);

        title("Nvidia");
        xlabel("Tick");
        ylabel("Price");

        draw();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(50)
        );
    }

    return 0;
}