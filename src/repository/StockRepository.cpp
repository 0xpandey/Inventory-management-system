#include "StockRepository.h"
#include <stdexcept>

StockRepository::StockRepository(Database& db)
    : database(db) {}

void StockRepository::createStock(int productId, int initialQuantity, int threshold) {
    const char* sql =
        "INSERT INTO stock (product_id, quantity, threshold) "
        "VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("prepare failed: create stock");
    }

    sqlite3_bind_int(stmt, 1, productId);
    sqlite3_bind_int(stmt, 2, initialQuantity);
    sqlite3_bind_int(stmt, 3, threshold);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("execution failed: create stock");
    }

    sqlite3_finalize(stmt);
}


int StockRepository::getStockQuantity(int productId) {
    const char* sql =
        "SELECT quantity FROM stock WHERE product_id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("prepare failed: get stock quantity");
    }

    sqlite3_bind_int(stmt, 1, productId);

    int quantity = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        quantity = sqlite3_column_int(stmt, 0);
    } else {
        sqlite3_finalize(stmt);
        throw std::runtime_error("stock not found");
    }

    sqlite3_finalize(stmt);
    return quantity;
}

Stock StockRepository::getStock(int productId) {
    const char* sql =
        "SELECT product_id, quantity, threshold, updated_at "
        "FROM stock WHERE product_id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("prepare failed: get stock");
    }

    sqlite3_bind_int(stmt, 1, productId);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("stock not found");
    }

    int pid = sqlite3_column_int(stmt, 0);
    int qty = sqlite3_column_int(stmt, 1);
    int threshold = sqlite3_column_int(stmt, 2);

    const unsigned char* ts = sqlite3_column_text(stmt, 3);
    std::string updatedAt = ts ? reinterpret_cast<const char*>(ts) : "";

    sqlite3_finalize(stmt);

    return Stock(pid, qty, threshold, updatedAt);
}



void StockRepository::updateStock(int productId, int delta) {
    int current = getStockQuantity(productId);
    int updated = current + delta;

    if (updated < 0) {
        throw std::runtime_error("insufficient stock");
    }

    const char* sql =
        "UPDATE stock "
        "SET quantity = ?, updated_at = CURRENT_TIMESTAMP "
        "WHERE product_id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("prepare failed: update stock");
    }

    sqlite3_bind_int(stmt, 1, updated);
    sqlite3_bind_int(stmt, 2, productId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("execution failed: update stock");
    }

    sqlite3_finalize(stmt);
}

