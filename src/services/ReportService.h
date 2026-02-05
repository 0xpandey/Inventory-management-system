#pragma once
#include "../database/Database.h"
#include <string>

class ReportService {
private:
    Database& database;

public:
    explicit ReportService(Database& db);

    void inventoryReport();
    void lowStockReport();
    void salesReport();
    void transactionHistory();
};
