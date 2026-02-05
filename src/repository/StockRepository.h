#ifndef STOCK_REPOSITORY_H
#define STOCK_REPOSITORY_H

#include "../database/Database.h"
#include "../models/Stock.h"

class StockRepository {
private:
    Database& database;

public:
    explicit StockRepository(Database& db);

    void createStock(int productId, int initialQuantity, int threshold = 5);

    int getStockQuantity(int productId);     // internal / validation
    Stock getStock(int productId);           // full stock view

    void updateStock(int productId, int delta);
};

#endif
