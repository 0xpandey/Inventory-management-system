#include "Database.h"
#include <iostream>
using namespace std;

Database::Database(const string& path) : db(nullptr), dbPath(path) {}

Database::~Database() {
    close();
}

bool Database::open() {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Failed to open database: "
                  << sqlite3_errmsg(db) << endl;
        return false;
    }
    return true;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

void Database::execute(const std::string& sql) {
    char* errorMsg = nullptr;

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMsg) != SQLITE_OK) {
        cerr << "SQL error: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
}

void Database::initialize() {
    execute("PRAGMA foreign_keys = ON;");

    execute(
        "CREATE TABLE IF NOT EXISTS products ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "category TEXT,"
        "price REAL NOT NULL,"
        "created_at TEXT DEFAULT CURRENT_TIMESTAMP,"
        "is_active INTEGER DEFAULT 1"
        ");"
    );

    execute(
        "CREATE TABLE IF NOT EXISTS stock ("
        "product_id INTEGER PRIMARY KEY,"
        "quantity INTEGER NOT NULL CHECK (quantity >= 0),"
        "threshold INTEGER DEFAULT 5,"
        "updated_at TEXT DEFAULT CURRENT_TIMESTAMP,"
        "FOREIGN KEY (product_id) REFERENCES products(id)"
        ");"
    );

    execute(
        "CREATE TABLE IF NOT EXISTS inventory_transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "product_id INTEGER NOT NULL,"
        "type TEXT CHECK (type IN ('BUY','SELL')),"
        "quantity INTEGER NOT NULL,"
        "unit_price REAL NOT NULL,"
        "timestamp TEXT DEFAULT CURRENT_TIMESTAMP,"
        "FOREIGN KEY (product_id) REFERENCES products(id)"
        ");"
    );
}