#include "ProductRepository.h"
#include <stdexcept>
#include <vector>

ProductRepository::ProductRepository(Database& db)
    : database(db) {}

int ProductRepository::addProduct(const Product& product) {
    const char* sql =
        "INSERT INTO products (name, category, price, is_active) "
        "VALUES (?, ?, ?, 1);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("prepare failed: insert product");
    }

    sqlite3_bind_text(stmt, 1, product.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, product.category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, product.price);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("execution failed: insert product");
    }

    sqlite3_finalize(stmt);
    return static_cast<int>(sqlite3_last_insert_rowid(database.getDB()));
}

std::vector<Product> ProductRepository::getAllProducts() {
    const char* sql =
        "SELECT id, name, category, price, is_active, created_at FROM products;";

    sqlite3_stmt* stmt = nullptr;
    std::vector<Product> products;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("prepare failed: select products");
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char* ts = sqlite3_column_text(stmt, 5);
        std::string createdAt = ts ? reinterpret_cast<const char*>(ts) : "";    //Checking if column is null

        products.emplace_back(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            sqlite3_column_double(stmt, 3),
            sqlite3_column_int(stmt, 4) == 1,
            createdAt
        );

    }

    sqlite3_finalize(stmt);
    return products;
}
