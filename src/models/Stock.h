#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock {
public:
    int productId;
    int quantity;
    int threshold;
    std::string updatedAt;

    Stock(int productId,
          int quantity,
          int threshold,
          const std::string& updatedAt)
        : productId(productId),
          quantity(quantity),
          threshold(threshold),
          updatedAt(updatedAt) {}
};

#endif