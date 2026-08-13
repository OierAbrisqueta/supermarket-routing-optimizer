#include <iostream>
#include <vector>
#include "StoreLayout.h"
#include "RouteEngine.h"
#include "Item.h"

using namespace std;

int main(void) {
    StoreLayout store;

    Node entrance(0, 0);
    Node aisle1(0, 5);
    Node aisle2(5, 5);
    Node aisle3(5, 0);
    Node checkout(2, 2);
    
    store.addNode(entrance);
    store.addNode(aisle1);
    store.addNode(aisle2);
    store.addNode(aisle3);
    store.addNode(checkout);

    store.addEdge(Edge(entrance.getId(), aisle1.getId()));
    store.addEdge(Edge(aisle1.getId(), aisle2.getId()));
    store.addEdge(Edge(aisle2.getId(), aisle3.getId()));
    store.addEdge(Edge(aisle3.getId(), checkout.getId()));
    store.addEdge(Edge(entrance.getId(), aisle3.getId()));

    store.printLayout();

    vector<Item> shoppingList;
    shoppingList.push_back(Item("Milk", aisle2));
    shoppingList.push_back(Item("Bread", aisle1));
    
    cout << "\n--- Starting Route Engine ---" << endl;
    RouteEngine engine(store);

    vector<int> optimalPath = engine.calculateOptimalRoute(entrance.getId(), checkout.getId(), shoppingList);
    
    cout << "Optimal Route Node IDs: ";
    for (int nodeId : optimalPath) {
        cout << nodeId << " -> ";
    }

    return 0;
}