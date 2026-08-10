#ifndef ROUTINGOPTIMIZER_NODE_H
#define ROUTINGOPTIMIZER_NODE_H

#include <iostream>
#include <atomic>

class Node {
public:
    Node();
    Node(int x, int y);

    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getId() const;
    void setX(int x);
    void setY(int y);

    void printNode() const;
    [[nodiscard]] std::string toString() const;

    bool operator==(const Node& node) const;

private:
    int id;
    int x = -1;
    int y = -1;

    static std::atomic<int> idCounter;
};

#endif //ROUTINGOPTIMIZER_NODE_H