#ifndef ROUTINGOPTIMIZER_ITEM_H
#define ROUTINGOPTIMIZER_ITEM_H
#include <string>
#include "Node.h"

class Item {
public:
    Item();

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] const Node& getArea() const;
    void setName(std::string newName);
    void setArea(const Node& newArea);

    void printItem() const;

private:
    int id;
    std::string name = "";
    Node area;

    static int idCounter;
};

#endif //ROUTINGOPTIMIZER_ITEM_H