#include "MarketDataFeed.h"
#include <random>

void MarketDataFeed::setCallback(Callback cb) {
    callback_ = std::move(cb);
}

void MarketDataFeed::run(int steps) {
    std::mt19937 gen{42};
    std::normal_distribution<> dist{0, 0.1};
    for (int i = 0; i < steps; ++i) {
        price_ += dist(gen);
        MarketTick tick{price_ - 0.01, price_ + 0.01};
        if (callback_) callback_(tick);
    }
}

