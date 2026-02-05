#include <iostream>
#include "database/Database.h"
#include "repository/ProductRepository.h"
#include "repository/StockRepository.h"
#include "repository/TransactionRepository.h"
#include "services/InventoryService.h"
#include "services/ReportService.h"

void showMenu() {
    std::cout << "\n===== INVENTORY MANAGEMENT SYSTEM =====\n";
    std::cout << "1. Add Product\n";
    std::cout << "2. Buy Stock\n";
    std::cout << "3. Sell Stock\n";
    std::cout << "4. Inventory Report\n";
    std::cout << "5. Low Stock Report\n";
    std::cout << "6. Sales Report\n";
    std::cout << "7. Transaction History\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose option: ";
}

int main() {
    try {
        Database db("../data/inventory.db");
        db.open();
        db.initialize();
        ProductRepository productRepository(db);
        StockRepository stockRepository(db);
        TransactionRepository transactionRepository(db, productRepository, stockRepository);

        InventoryService inventoryService(productRepository, stockRepository, transactionRepository);
        ReportService reportService(db);

        int choice;
        do {
            showMenu();
            std::cin >> choice;

            switch (choice) {
            case 1: inventoryService.addProduct(); break;
            case 2: inventoryService.buyStock(); break;
            case 3: inventoryService.sellStock(); break;
            case 4: reportService.inventoryReport(); break;
            case 5: reportService.lowStockReport(); break;
            case 6: reportService.salesReport(); break;
            case 7: reportService.transactionHistory(); break;
            case 0: std::cout << "👋 Exiting...\n"; break;
            default: std::cout << "❌ Invalid option\n";
            }
        } while (choice != 0);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
