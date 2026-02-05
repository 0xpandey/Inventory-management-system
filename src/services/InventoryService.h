#pragma once
#include "../repository/ProductRepository.h"
#include "../repository/StockRepository.h"
#include "../repository/TransactionRepository.h"

class InventoryService {
private:
    ProductRepository& productRepo;
    StockRepository& stockRepo;
    TransactionRepository& transactionRepo;

public:
    InventoryService(
        ProductRepository& p,
        StockRepository& s,
        TransactionRepository& t
    );

    void addProduct();
    void buyStock();
    void sellStock();
};
