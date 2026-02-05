#include "ReportService.h"
#include <iostream>
#include <iomanip>

ReportService::ReportService(Database& db) : database(db) {}

void ReportService::inventoryReport() {
    const char* sql =
        "SELECT p.name, p.category, s.quantity, s.threshold "
        "FROM products p "
        "JOIN stock s ON p.id = s.product_id "
        "WHERE p.is_active = 1;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Inventory report failed");

    std::cout << "\n INVENTORY REPORT\n";
    std::cout << "--------------------------------------------------\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout
            << std::left << std::setw(15) << sqlite3_column_text(stmt, 0)
            << std::setw(15) << sqlite3_column_text(stmt, 1)
            << std::setw(10) << sqlite3_column_int(stmt, 2)
            << "Threshold: " << sqlite3_column_int(stmt, 3)
            << "\n";
    }

    sqlite3_finalize(stmt);
}

void ReportService::lowStockReport() {
    const char* sql =
        "SELECT p.name, s.quantity, s.threshold "
        "FROM products p "
        "JOIN stock s ON p.id = s.product_id "
        "WHERE s.quantity < s.threshold;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Low stock report failed");

    std::cout << "\n[alert] LOW STOCK ALERT\n";
    std::cout << "--------------------------------------------------\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout
            << sqlite3_column_text(stmt, 0)
            << " | Qty: " << sqlite3_column_int(stmt, 1)
            << " | Threshold: " << sqlite3_column_int(stmt, 2)
            << "\n";
    }

    sqlite3_finalize(stmt);
}

void ReportService::salesReport() {
    const char* sql =
        "SELECT SUM(quantity * price) "
        "FROM transactions "
        "WHERE type = 'SELL';";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Sales report failed");

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double total = sqlite3_column_double(stmt, 0);
        std::cout << "\n[$$] TOTAL SALES: $$" << total << "\n";
    }

    sqlite3_finalize(stmt);
}

void ReportService::transactionHistory() {
    const char* sql =
        "SELECT product_id, type, quantity, price, timestamp "
        "FROM transactions ORDER BY timestamp DESC;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database.getDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
        throw std::runtime_error("Transaction history failed");

    std::cout << "\n[History] TRANSACTION HISTORY\n";
    std::cout << "--------------------------------\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout
            << "Product ID: " << sqlite3_column_int(stmt, 0)
            << " | " << sqlite3_column_text(stmt, 1)
            << " | Qty: " << sqlite3_column_int(stmt, 2)
            << " | Price: " << sqlite3_column_double(stmt, 3)
            << " | " << sqlite3_column_text(stmt, 4)
            << "\n";
    }

    sqlite3_finalize(stmt);
}

