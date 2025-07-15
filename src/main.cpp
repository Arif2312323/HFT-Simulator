#include "MarketDataFeed.h"
#include "MatchingEngine.h"
#include "StrategyInterface.h"
#include <iostream>
#include <memory>

class NaiveStrategy : public IStrategy {
public:
    void onMarketData(const MarketTick& tick) override {
        lastBid_ = tick.bid;
        lastAsk_ = tick.ask;
    }
    std::vector<Order> getOrders() override {
        std::vector<Order> orders;
        Order buy{nextId_++, Order::Side::Buy, lastBid_, 1};
        Order sell{nextId_++, Order::Side::Sell, lastAsk_, 1};
        orders.push_back(buy);
        orders.push_back(sell);
        return orders;
    }
private:
    double lastBid_{0};
    double lastAsk_{0};
    int nextId_{1};
};

int main() {
    MatchingEngine engine;
    MarketDataFeed feed;
    NaiveStrategy strat;
    feed.setCallback([&](const MarketTick& tick){
        strat.onMarketData(tick);
        for (const auto& order : strat.getOrders()) {
            auto trades = engine.processOrder(order);
            for (const auto& t : trades) {
                std::cout << "trade price=" << t.price << " qty=" << t.quantity << "\n";
            }
        }
    });
    feed.run(100);
    return 0;
}

