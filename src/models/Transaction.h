//Transaction.h will bridge between my db and code for transaction table

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
using namespace std;

enum class TransactionType {
    BUY,
    SELL
};

class Transaction {
public:
    int id;                  //Primary key
    int productId;           //FK → products.id
    TransactionType type;    //BUY or SELL
    int quantity;            //Units moved
    double unitPrice;        //Price per unit
    string timestamp;   //When transaction occurred

    //Constructor for new transaction
    Transaction(int productId,
                TransactionType type,
                int quantity,
                double unitPrice)
        : id(-1),
          productId(productId),
          type(type),
          quantity(quantity),
          unitPrice(unitPrice) {}

    //Constructor for DB-loaded transaction
    Transaction(int id,
                int productId,
                TransactionType type,
                int quantity,
                double unitPrice,
                const string& timestamp)
        : id(id),
          productId(productId),
          type(type),
          quantity(quantity),
          unitPrice(unitPrice),
          timestamp(timestamp) {}
};

#endif