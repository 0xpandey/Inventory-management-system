#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    int id;
    std::string name;
    std::string category;
    double price;
    bool isActive;
    std::string createdAt;

    // For creating a new product (before saving to DB)
    Product(const std::string& name,
            const std::string& category,
            double price)
        : id(-1),
          name(name),
          category(category),
          price(price),
          isActive(true) {}

    // For loading an existing product from DB
    Product(int id,
            const std::string& name,
            const std::string& category,
            double price,
            bool isActive,
            const std::string& createdAt)
        : id(id),
          name(name),
          category(category),
          price(price),
          isActive(isActive),
          createdAt(createdAt) {}
};

#endif