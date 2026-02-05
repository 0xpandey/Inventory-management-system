#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

enum class TransactionType {
    BUY,
    SELL
};

class Transaction {
public:
    int id;
    int productId;
    TransactionType type;
    int quantity;
    double unitPrice;
    std::string timestamp;

    // New transaction (before saving to DB)
    Transaction(int productId,
                TransactionType type,
                int quantity,
                double unitPrice)
        : id(-1),
          productId(productId),
          type(type),
          quantity(quantity),
          unitPrice(unitPrice) {}

    // Loaded from DB
    Transaction(int id,
                int productId,
                TransactionType type,
                int quantity,
                double unitPrice,
                const std::string& timestamp)
        : id(id),
          productId(productId),
          type(type),
          quantity(quantity),
          unitPrice(unitPrice),
          timestamp(timestamp) {}
};

#endif