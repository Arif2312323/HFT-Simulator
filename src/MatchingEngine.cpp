#include "MatchingEngine.h"

std::vector<Trade> MatchingEngine::processOrder(const Order& order) {
    std::vector<Trade> trades;
    Order working = order;
    auto matched = book_.match(working);
    for (const auto& m : matched) {
        Trade t{order.side == Order::Side::Buy ? order.id : m.id,
                order.side == Order::Side::Sell ? order.id : m.id,
                m.price,
                m.quantity};
        trades.push_back(t);
    }
    if (working.quantity > 0) {
        book_.addOrder(working);
    }
    return trades;
}

