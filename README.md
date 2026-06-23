# Stock Market Simulator

A simple stock market simulation written in C++.

This project started as an experiment to answer a simple question:

> What happens if a group of traders repeatedly react to price changes and news events?

The result is a surprisingly interesting market where trends, crashes, rallies, and bubbles emerge from a few simple rules.

## Features

* 100 simulated traders
* Individual trader personalities
* Market sentiment system
* Gaussian news drift
* Random major news events
* Momentum-based trading behavior
* Panic selling during sharp declines
* Real-time price chart using Gnuplot
* Emergent bull and bear markets

## How It Works

Each trader generates a bid based on:

* Personal impulsiveness
* Current market sentiment
* Recent price trends
* Random mood fluctuations
* Panic reactions during crashes

The market price is calculated from the average bid of all traders.

Although no actual shares are traded, the interactions between traders create realistic-looking price movements and market behavior.

## Example Behaviors

The simulator can produce:

* Sudden crashes
* Long bull runs
* Sideways consolidation
* Volatility spikes
* News-driven rallies
* Panic selloffs

Every run produces a different market history.

## Dependencies

* C++17 or newer
* Gnuplot

### Install Gnuplot (MSYS2)

```bash
pacman -S mingw-w64-ucrt-x86_64-gnuplot
```

## Build

```bash
g++ main.cpp -O2 -std=c++17 -o stock_sim.exe
```

## Run

```bash
./stock_sim.exe
```

A Gnuplot window will open and display the market price in real time.

## Project Status

Version 1.0 Complete

This project intentionally stops at sentiment-driven market simulation.

Features such as:

* Order books
* Share ownership
* Market makers
* Bid/ask spreads
* Liquidity simulation

were considered but intentionally left out to keep the project focused and lightweight.

## What I Learned

This project taught me:

* Emergent systems can arise from simple rules.
* Small changes in trader behavior dramatically affect market structure.
* Markets are often driven by feedback loops rather than fundamentals.
* Plotting libraries are somehow harder to set up than writing a stock market.

## Future Ideas

* Trader archetypes (momentum, contrarian, investor)
* Multiple competing stocks
* Economic cycles
* Earnings reports
* Portfolio simulation

## License

MIT License

---
