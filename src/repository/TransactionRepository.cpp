#include "TransactionRepository.h"
#include <stdexcept>

TransactionRepository::TransactionRepository(
    Database& db,
    ProductRepository& pr,
    StockRepository& sr)
    : database(db), productRepo(pr), stockRepo(sr) {}

static void execSimple(sqlite3* db, const char* sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string err = errMsg ? errMsg : "unknown error";
        sqlite3_free(errMsg);
        throw std::runtime_error(err);
    }
}

void TransactionRepository::buy(int productId, int quantity, double price) {
    const char* sql =
        "INSERT INTO transactions (product_id, type, quantity, price) "
        "VALUES (?, 'BUY', ?, ?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("prepare failed: buy transaction");

    sqlite3_bind_int(stmt, 1, productId);
    sqlite3_bind_int(stmt, 2, quantity);
    sqlite3_bind_double(stmt, 3, price);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("execution failed: buy transaction");
    }

    sqlite3_finalize(stmt);

    stockRepo.updateStock(productId, quantity);
}


void TransactionRepository::sell(int productId, int quantity, double price) {
    int currentQty = stockRepo.getStockQuantity(productId);

    if (currentQty < quantity) {
        throw std::runtime_error("Not enough stock");
    }

    const char* sql =
        "INSERT INTO transactions (product_id, type, quantity, price) "
        "VALUES (?, 'SELL', ?, ?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("prepare failed: sell transaction");

    sqlite3_bind_int(stmt, 1, productId);
    sqlite3_bind_int(stmt, 2, quantity);
    sqlite3_bind_double(stmt, 3, price);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("execution failed: sell transaction");
    }

    sqlite3_finalize(stmt);

    stockRepo.updateStock(productId, -quantity);
}



