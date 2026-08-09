#include "Item.h"

Item::Item() {
    ++idCounter;
    this->id = idCounter;
}

int Item::getId() const {
    return this->id;
}
std::string Item::getName() const {
    return this->name;
}

const Node& Item::getArea() const {
    return this->area;
}

void Item::setName(std::string newName) {
    this->name = newName;
}

void Item::setArea(const Node& newArea) {
    this->area = newArea;
}

void Item::printItem() const {
    std::cout << "ItemId: " << this->id << " | Name: " << this->name << " | Area: [" << this->area.toString() << "]" << std::endl;
}