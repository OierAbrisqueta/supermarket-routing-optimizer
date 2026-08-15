#ifndef ROUTINGOPTIMIZER_NODE_H
#define ROUTINGOPTIMIZER_NODE_H

#include <iostream>
#include <atomic>

class Node {
public:
    Node();
    Node(double x, double y);
    Node(int id, double x, double y);

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] int getId() const;
    void setX(double x);
    void setY(double y);

    void printNode() const;
    [[nodiscard]] std::string toString() const;

    bool operator==(const Node& node) const;

private:
    int id;
    double x = -1;
    double y = -1;

    static std::atomic<int> idCounter;
};

#endif //ROUTINGOPTIMIZER_NODE_H