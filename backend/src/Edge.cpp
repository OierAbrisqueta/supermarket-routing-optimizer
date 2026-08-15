#include "Edge.h"
#include "StoreLayout.h"
#include <cmath>

std::atomic<int> Edge::idCounter{0};

Edge::Edge() {
    ++idCounter;
    this->id = idCounter;
    this->weight = 0;
}

Edge::Edge(int idNode1, int idNode2): Edge() {
    this->idNode1 = idNode1;
    this->idNode2 = idNode2;
    this->weight = 0;
}

Edge::Edge(int id, int idNode1, int idNode2, double weight = 0) {
    this->id = id;
    this->idNode1 = idNode1;
    this->idNode2 = idNode2;
    this->weight = 0;

    int currentCounter = idCounter.load();
    while (id >= currentCounter && !idCounter.compare_exchange_weak(currentCounter, id)) {
    }
}

int Edge::getNode1() const {
    return this->idNode1;
}

int Edge::getNode2() const {
    return this->idNode2;
}

int Edge::getId() const {
    return this->id;
}

void Edge::setNode1(int newIdNode1) {
    this->idNode1 = newIdNode1;
}

void Edge::setNode2(int newIdNode2) {
    this->idNode2 = newIdNode2;
}

bool Edge::operator==(const Edge& other) const {
    return (this->getNode1() == other.getNode1() &&
    this->getNode2() == other.getNode2()) || (this->getNode1() == other.getNode2() &&
    this->getNode2() == other.getNode1());
}

void Edge::printEdge() const {
    std::cout << "Edge Id: " << this->id << " | Area 1: " << this->getNode1() << " | Area 2: " << this->getNode2() << std::endl;
}

double Edge::getWeight(const StoreLayout& slayout) {
    Node node1 = slayout.getAreaById(this->idNode1).value();
    Node node2 = slayout.getAreaById(this->idNode2).value();
    double distance = std::abs(node1.getX() - node2.getX()) + std::abs(node1.getY() - node2.getY());
    this->weight = distance;
    return distance;
}