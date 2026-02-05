#ifndef TRANSACTION_REPOSITORY_H
#define TRANSACTION_REPOSITORY_H

#include "../database/Database.h"
#include "../models/Transaction.h"
#include "ProductRepository.h"
#include "StockRepository.h"

class TransactionRepository {
private:
    Database& database;
    ProductRepository& productRepo;
    StockRepository& stockRepo;

public:
    TransactionRepository(Database& db,
                          ProductRepository& pr,
                          StockRepository& sr);

    void buy(int productId, int quantity, double unitPrice);
    void sell(int productId, int quantity, double unitPrice);
};

#endif