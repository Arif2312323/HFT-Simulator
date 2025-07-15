#pragma once
#include <functional>

struct MarketTick {
    double bid;
    double ask;
};

class MarketDataFeed {
public:
    using Callback = std::function<void(const MarketTick&)>;
    void setCallback(Callback cb);
    void run(int steps = 1000);
private:
    Callback callback_;
    double price_{100.0};
};

