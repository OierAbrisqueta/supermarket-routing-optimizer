#include <iostream>
#include <vector>

#include "ApiServer.h"
#include "StoreLayout.h"
#include "RouteEngine.h"
#include "Item.h"
#include "Database.h"

using namespace std;

int main(void) {
    Database db("supermarket.db");
    db.initializeTables();
    db.insertData();

    int port = 8000;
    size_t threads = 4;
    ApiServer server(port, threads, "supermarket.db");

    server.start();

    return 0;
}