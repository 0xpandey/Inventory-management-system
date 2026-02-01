#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
using namespace std;

class Database {
private:
    sqlite3* db;
    string dbPath;
    
    void execute(const string& sql);

public:
    Database(const string& path);
    ~Database();

    bool open();
    void close();
    void initialize();
};

#endif