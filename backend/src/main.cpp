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

    int storeId = 1;
    std::vector<int> productIds = {1, 2};
    int startNodeId = 1;
    int endNodeId = 5;

    StoreLayout store = db.getStoreLayout(storeId);
    store.printLayout();
    std::vector<Item> shoppingList = db.getItems(storeId, productIds);
    for (Item item : shoppingList) {
        item.printItem();
    }

    RouteEngine engine(store);
    std::vector<int> optimalPath = engine.calculateOptimalRoute(startNodeId, endNodeId, shoppingList);

    return 0;
}