#include "Node.h"

int Node::idCounter = 0;

Node::Node() {
    ++idCounter;
    this->id = idCounter;
}

Node::Node(int x, int y): Node() {
    this->x = x;
    this->y = y;
}

int Node::getX() const {
    return this->x;
}

int Node::getY() const {
    return this->y;
}

int Node::getId() const {
    return this->id;
}

void Node::setX(int x) {
    this->x = x;
}

void Node::setY(int y) {
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
