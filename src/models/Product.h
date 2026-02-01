//Product.h will bridge between my db and code for products table

#ifndef PRODUCT_H
#define PRODUCT_H
using namespace std;
#include <string>

class Product {
public:
    int id;                     
    string name;           
    string category;       
    double price;               
    bool isActive;             
    string createdAt;     

    //Constructor for new products
    Product(const string& name,
            const string& category,
            double price)
        : id(-1),
          name(name),
          category(category),
          price(price),
          isActive(true) {}

    //Constructor for products loaded from DB
    Product(int id,
            const string& name,
            const string& category,
            double price,
            bool isActive,
            const string& createdAt)
        : id(id),
          name(name),
          category(category),
          price(price),
          isActive(isActive),
          createdAt(createdAt) {}
};

#endif