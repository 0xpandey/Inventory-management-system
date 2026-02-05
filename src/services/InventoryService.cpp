#include "InventoryService.h"
#include <iostream>

InventoryService::InventoryService(
    ProductRepository& p,
    StockRepository& s,
    TransactionRepository& t
) : productRepo(p), stockRepo(s), transactionRepo(t) {}

void InventoryService::addProduct() {
    std::string name, category;
    double price;
    int quantity, threshold;

    std::cout << "Product name: ";
    std::cin >> name;

    std::cout << "Category: ";
    std::cin >> category;

    std::cout << "Price: ";
    std::cin >> price;

    std::cout << "Initial quantity: ";
    std::cin >> quantity;

    std::cout << "Threshold: ";
    std::cin >> threshold;

    Product product{0, name, category, price, 1, ""};
    int productId = productRepo.addProduct(product);

    stockRepo.createStock(productId, quantity, threshold);
    std::cout << "[Okay] Product added successfully\n";
}

void InventoryService::buyStock() {
    int productId, quantity;
    double price;

    std::cout << "Product ID: ";
    std::cin >> productId;

    std::cout << "Quantity to buy: ";
    std::cin >> quantity;

    std::cout << "Purchase price: ";
    std::cin >> price;

    transactionRepo.buy(productId, quantity, price);

    std::cout << "[Done] Stock updated\n";
}

void InventoryService::sellStock() {
    int productId, quantity;
    double price;

    std::cout << "Product ID: ";
    std::cin >> productId;

    std::cout << "Quantity to sell: ";
    std::cin >> quantity;

    std::cout << "Selling price: ";
    std::cin >> price;

    transactionRepo.sell(productId, quantity, price);

    std::cout << "[Recorded] Sale recorded\n";
}
