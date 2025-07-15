#pragma once
#include "OrderBook.h"
#include <vector>

struct Trade {
    int buyOrderId;
    int sellOrderId;
    double price;
    int quantity;
};

class MatchingEngine {
public:
    std::vector<Trade> processOrder(const Order& order);
private:
    OrderBook book_;
};

