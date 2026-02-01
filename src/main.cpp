#include <iostream>
#include "database/Database.h"
using namespace std;

int main() {
    Database db("data/inventory.db");

    if (!db.open()) {
        return 1;
    }

    db.initialize();

    cout << "Database initialized successfully.\n";

    return 0;
}