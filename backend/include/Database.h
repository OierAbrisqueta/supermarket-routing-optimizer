#ifndef ROUTINGOPTIMIZER_DATABASE_H
#define ROUTINGOPTIMIZER_DATABASE_H

#include <sqlite3.h>
#include <fstream>
#include <sstream>

#include "Item.h"
#include "StoreLayout.h"
#include "Node.h"
#include "Edge.h"

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

    [[nodiscard]] StoreLayout getStoreLayout(int storeId) const;
    [[nodiscard]] std::vector<Item> getItems(int storeId, std::vector<int> productIds) const;
    [[nodiscard]] std::vector<Node> getAreas(int storeId) const;
    [[nodiscard]] std::vector<Edge> getEdges(int storeId) const;

private:
    sqlite3* db;
    bool executeQuery(const std::string& query);

};
#endif //ROUTINGOPTIMIZER_DATABASE_H