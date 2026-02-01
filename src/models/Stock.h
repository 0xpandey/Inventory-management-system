//Stock.h will bridge between my db and code for stocks table

#ifndef STOCK_H
#define STOCK_H
using namespace std;

class Stock {
public:
    int productId;     //ForeignKey → products.id
    int quantity;      //Current available quantity
    int threshold;     //Low stock alert level

    Stock(int productId, int quantity, int threshold = 5)
        : productId(productId),
          quantity(quantity),
          threshold(threshold) {}
};

#endif