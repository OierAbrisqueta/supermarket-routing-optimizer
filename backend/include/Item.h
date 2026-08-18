#ifndef ROUTINGOPTIMIZER_ITEM_H
#define ROUTINGOPTIMIZER_ITEM_H
#include <string>
#include "Node.h"
#include <atomic>

class Item {
public:
    Item();
    Item(const std::string& name, const Node& area);
    Item(int id, const std::string& name, const Node& area);

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] const Node& getArea() const;
    void setName(const std::string& newName);
    void setArea(const Node& newArea);

    void printItem() const;

private:
    int id;
    std::string name = "";
    Node area;

    static std::atomic<int> idCounter;
};

#endif //ROUTINGOPTIMIZER_ITEM_H