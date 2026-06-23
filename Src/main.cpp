#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <thread>
#include <chrono>
#include <cstdio>
#include <algorithm>

std::mt19937 rng(std::random_device{}());

std::normal_distribution<float> news_change(
    0.0f,
    0.0015f
);

class Trader
{
public:
    float money;
    float impulsiveness;
    float bid;

    Trader()
    {
        money =
            std::normal_distribution<float>(
                10000.f,
                2500.f
            )(rng);

        impulsiveness =
            std::uniform_real_distribution<float>(
                -0.10f,
                 0.10f
            )(rng);

        bid = 0.f;
    }

    void UpdateBid(
        float current_price,
        float trend,
        float news
    )
    {
        float mood =
            std::uniform_real_distribution<float>(
                -0.05f,
                 0.05f
            )(rng);

        float momentum = trend * 3.f;

        float panic = 0.f;

        if (trend < -0.03f)
        {
            panic =
                std::uniform_real_distribution<float>(
                    -0.15f,
                    -0.05f
                )(rng);
        }

        bid =
            current_price *
            (
                1.f +
                impulsiveness +
                mood +
                momentum +
                panic +
                news
            );

        if (bid < 1.f)
            bid = 1.f;
    }
};

class Nvidia
{
public:
    float init_price = 100.f;

    std::vector<float> bid_prices;
    std::vector<double> history;

    float GetPrice() const
    {
        if (bid_prices.empty())
            return init_price;

        return
            std::accumulate(
                bid_prices.begin(),
                bid_prices.end(),
                0.f
            )
            /
            bid_prices.size();
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

    FILE* gp =
        popen(
            "gnuplot -persistent",
            "w"
        );

    if (!gp)
    {
        std::cerr
            << "Failed to launch gnuplot\n";
        return 1;
    }

    fprintf(gp, "set title 'NVDA Market Simulation'\n");
    fprintf(gp, "set xlabel 'Time'\n");
    fprintf(gp, "set ylabel 'Price'\n");
    fprintf(gp, "set grid\n");

    float previous_price =
        nvidia.init_price;

    float news = 0.f;

    int frame = 0;

    while (true)
    {
        nvidia.bid_prices.clear();

        float current_price =
            nvidia.GetPrice();

        float trend =
            (current_price - previous_price)
            /
            previous_price;

        previous_price =
            current_price;

        // Continuous sentiment drift
        news += news_change(rng);

        // Rare major events
        if (frame % 500 == 0)
        {
            float shock =
                std::normal_distribution<float>(
                    0.0f,
                    0.03f
                )(rng);

            news += shock;

            std::cout
                << "\nMAJOR NEWS EVENT: "
                << shock * 100.f
                << "% impact\n";
        }

        // Prevent runaway insanity
        news = std::clamp(
            news,
            -0.15f,
             0.15f
        );

        for (Trader& trader : market)
        {
            trader.UpdateBid(
                current_price,
                trend,
                news
            );

            nvidia.bid_prices.push_back(
                trader.bid
            );
        }

        float new_price =
            nvidia.GetPrice();

        nvidia.history.push_back(
            new_price
        );

        if (
            nvidia.history.size()
            > 500
        )
        {
            nvidia.history.erase(
                nvidia.history.begin()
            );
        }

        if (frame % 10 == 0)
        {
            fprintf(
                gp,
                "plot '-' with lines lw 2 title 'NVDA'\n"
            );

            for (
                size_t i = 0;
                i < nvidia.history.size();
                i++
            )
            {
                fprintf(
                    gp,
                    "%zu %f\n",
                    i,
                    nvidia.history[i]
                );
            }

            fprintf(gp, "e\n");
            fflush(gp);

            std::cout
                << "\rPrice: "
                << new_price
                << "  Sentiment: "
                << news
                << "      "
                << std::flush;
        }

        frame++;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(
                50
            )
        );
    }

    pclose(gp);

    return 0;
}