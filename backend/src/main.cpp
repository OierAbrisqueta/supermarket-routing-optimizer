#include <iostream>
#include <vector>
#include "StoreLayout.h"
#include "RouteEngine.h"
#include "Item.h"
#include "Database.h"

using namespace std;

int main(void) {
    Database db("supermarket.db");
    db.initializeTables();
    db.insertData();

    if (!db.isTableEmpty("Edge")) cout << "Table Edge is not empty" << endl;

    return 0;
}