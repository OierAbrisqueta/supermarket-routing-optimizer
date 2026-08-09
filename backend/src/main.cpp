#include <iostream>
#include <StoreLayout.h>

using namespace std;

int main(void) {
    StoreLayout store;
    Node node1;
    node1.setX(1);
    node1.setY(1);
    store.addNode(node1);
    Node node2;
    node1.setX(2);
    node1.setY(2);
    store.addNode(node2);
    Node node3;
    node1.setX(4);
    node1.setY(4);
    store.addNode(node3);
    Edge edge1;
    edge1.setNode1(node1);
    edge1.setNode2(node2);
    store.addEdge(edge1);
    Edge edge2;
    edge2.setNode1(node1);
    edge2.setNode2(node3);
    store.addEdge(edge2);
    store.printLayout();
    return 0;
}