#include "Node.h"

std::atomic<int> Node::idCounter{0};

Node::Node() {
    ++idCounter;
    this->id = idCounter;
}

Node::Node(double x, double y): Node() {
    this->x = x;
    this->y = y;
}

Node::Node(int id, double x, double y) {
    this->id = id;
    this->x = x;
    this->y = y;

    int currentCounter = idCounter.load();
    while (id >= currentCounter && !idCounter.compare_exchange_weak(currentCounter, id)) {
    }
}

double Node::getX() const {
    return this->x;
}

double Node::getY() const {
    return this->y;
}

int Node::getId() const {
    return this->id;
}

void Node::setX(double x) {
    this->x = x;
}

void Node::setY(double y) {
    this->y = y;
}

void Node::printNode() const {
    std::cout << "Node ID: " << this->id << " | X: " << this->x << " | Y: " << this->y << std::endl;
}
std::string Node::toString() const {
    return "Node ID: " + std::to_string(id) + " | X: " +
        std::to_string(x) + " | Y: " + std::to_string(y);
}

bool Node::operator==(const Node& node) const {
    return this->id == node.getId();
}
