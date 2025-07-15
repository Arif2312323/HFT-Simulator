#pragma once
#include "MarketDataFeed.h"
#include "MatchingEngine.h"
#include <vector>

class IStrategy {
public:
    virtual ~IStrategy() = default;
    virtual void onMarketData(const MarketTick&) = 0;
    virtual std::vector<Order> getOrders() = 0;
};

