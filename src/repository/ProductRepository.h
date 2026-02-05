#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

#include "../database/Database.h"
#include "../models/Product.h"
#include <vector>


class ProductRepository {
private:
    Database& database;     //Not using pointer because pointer can be null

public:
    explicit ProductRepository(Database& db);

    int addProduct(const Product& product);
    Product getProductById(int id);
    std::vector<Product> getAllProducts();
};

#endif
