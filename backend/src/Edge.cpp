#include "Edge.h"

Edge::Edge() {
    ++idCounter;
    this->id = idCounter;
}

const Node& Edge::getNode1() const {
    return this->node1;
}

const Node& Edge::getNode2() const {
    return this->node2;
}

int Edge::getId() const {
    return this->id;
}

void Edge::setNode1(const Node& newNode1) {
    this->node1 = newNode1;
}

void Edge::setNode2(const Node& newNode2) {
    this->node2 = newNode2;
}

bool Edge::operator==(const Edge& other) const {
    return this->getNode1().getId() == other.getNode1().getId() &&
               this->getNode2().getId() == other.getNode2().getId();
}

void Edge::printEdge() const {
    std::cout << "Edge Id: " << this->id << " | Area 1: " << this->getNode1().getId() << " | Area 2: " << this->getNode2().getId() << std::endl;
}