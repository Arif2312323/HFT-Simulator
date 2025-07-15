# HFT Simulator

This project provides a minimal high-frequency trading simulator. It includes
an order book, matching engine, market data feed, and a simple example
strategy. Orders are matched against resting liquidity until either side is
fully filled so the example better reflects a real exchange.

## Build

```
mkdir build && cd build
cmake .. && make
```

Run with `./simulator`.

