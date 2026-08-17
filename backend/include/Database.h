#ifndef ROUTINGOPTIMIZER_DATABASE_H
#define ROUTINGOPTIMIZER_DATABASE_H

#include <sqlite3.h>
#include <fstream>
#include <sstream>

#include "StoreLayout.h"

class Database {
public:
    Database(const std::string& path);
    ~Database();
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    bool initializeTables();
    bool insertData();
    bool isTableEmpty(const std::string& tableName);
    bool executeSqlScript(const std::string& path);

private:
    sqlite3* db;
    bool executeQuery(const std::string& query);

};
#endif //ROUTINGOPTIMIZER_DATABASE_H