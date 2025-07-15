#pragma once
#include <deque>
#include <map>
#include <vector>

struct Order {
    enum class Side { Buy, Sell };
    int id;
    Side side;
    double price;
    int quantity;
};

class OrderBook {
public:
    void addOrder(const Order& order);
    /**
     * Attempt to match the incoming order against the book. The order's
     * quantity is reduced by the executed amount so callers can determine
     * any remaining quantity.
     */
    std::vector<Order> match(Order& incoming);
private:
    std::map<double, std::deque<Order>, std::greater<double>> bids_;
    std::map<double, std::deque<Order>> asks_;
};

