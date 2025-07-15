#include "OrderBook.h"
#include <algorithm>

void OrderBook::addOrder(const Order& order) {
    if (order.side == Order::Side::Buy) {
        bids_[order.price].push_back(order);
    } else {
        asks_[order.price].push_back(order);
    }
}

std::vector<Order> OrderBook::match(Order& incoming) {
    std::vector<Order> trades;
    if (incoming.side == Order::Side::Buy) {
        while (incoming.quantity > 0 && !asks_.empty()) {
            auto it = asks_.begin();
            if (incoming.price < it->first) break;

            Order& resting = it->second.front();
            int execQty = std::min(incoming.quantity, resting.quantity);
            Order trade = resting;
            trade.quantity = execQty;
            trades.push_back(trade);

            resting.quantity -= execQty;
            incoming.quantity -= execQty;

            if (resting.quantity == 0) {
                it->second.pop_front();
            }
            if (it->second.empty()) {
                asks_.erase(it);
            }
        }
    } else {
        while (incoming.quantity > 0 && !bids_.empty()) {
            auto it = bids_.begin();
            if (incoming.price > it->first) break;

            Order& resting = it->second.front();
            int execQty = std::min(incoming.quantity, resting.quantity);
            Order trade = resting;
            trade.quantity = execQty;
            trades.push_back(trade);

            resting.quantity -= execQty;
            incoming.quantity -= execQty;

            if (resting.quantity == 0) {
                it->second.pop_front();
            }
            if (it->second.empty()) {
                bids_.erase(it);
            }
        }
    }
    return trades;
}

