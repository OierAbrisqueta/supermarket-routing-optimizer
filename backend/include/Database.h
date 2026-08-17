#ifndef ROUTINGOPTIMIZER_DATABASE_H
#define ROUTINGOPTIMIZER_DATABASE_H

#include <sqlite3.h>

#include "StoreLayout.h"

class Database {
public:
    Database(const std::string& path);
    ~Database();
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

private:
    sqlite3* db;
    void executeQuery(const std::string& query);

};
#endif //ROUTINGOPTIMIZER_DATABASE_H