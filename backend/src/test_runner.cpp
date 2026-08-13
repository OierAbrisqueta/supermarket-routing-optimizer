#include <iostream>
#include <cassert>
#include "StoreLayout.h"
#include "RouteEngine.h"

using namespace std;

StoreLayout createTestMap(vector<Item>* shoppingCart = nullptr) {
    StoreLayout store;
    Node n1(0, 0);
    Node n2(0, 5);
    Node n3(5, 5);
    Node n4(5, 0);
    Node n5(10, 0);
    Edge e1(n1.getId(), n2.getId());
    Edge e2(n2.getId(), n3.getId());
    Edge e3(n1.getId(), n4.getId());
    Edge e4(n3.getId(), n4.getId());
    Edge e5(n4.getId(), n5.getId());
    store.addNode(n1);
    store.addNode(n2);
    store.addNode(n3);
    store.addNode(n4);
    store.addNode(n5);
    store.addEdge(e1);
    store.addEdge(e2);
    store.addEdge(e3);
    store.addEdge(e4);
    store.addEdge(e5);

    if (shoppingCart != nullptr) {
        Item i1("Milk", n1);
        Item i2("Bread", n2);
        Item i3("Apple", n3);
        Item i4("Wine", n5);
        shoppingCart->push_back(i1);
        shoppingCart->push_back(i2);
        shoppingCart->push_back(i3);
        shoppingCart->push_back(i4);
    }

    return store;
}

void testShortestPath() {
    StoreLayout store = createTestMap();
    RouteEngine engine(store);

    vector<int> path = engine.calculateShortestPath(1, 2);
    assert(path.size() == 2);
    assert(path[0] == 1);
    assert(path[1] == 2);

    cout << "Shortest Path Passed" << endl;
}

void testOptimalRoute() {
    vector<Item> shoppingCart;
    StoreLayout store = createTestMap(&shoppingCart);
    RouteEngine engine(store);

    vector<int> route = engine.calculateOptimalRoute(shoppingCart[0].getArea().getId(), shoppingCart[3].getArea().getId(),
        shoppingCart);
    assert(route.size() == 5);
    assert(route[0] == shoppingCart[0].getArea().getId());
    assert(route[1] == shoppingCart[1].getArea().getId());
    assert(route[4] == shoppingCart[3].getArea().getId());

    cout << "Optimal Route Passed" << endl;
}

int main() {
    testShortestPath();
    testOptimalRoute();

    cout << "All tests passed" << endl;
}