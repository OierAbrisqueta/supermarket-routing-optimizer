#include "Edge.h"

int Edge::idCounter = 0;

Edge::Edge() {
    ++idCounter;
    this->id = idCounter;
}

Edge::Edge(int idNode1, int idNode2): Edge() {
    this->idNode1 = idNode1;
    this->idNode2 = idNode2;
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