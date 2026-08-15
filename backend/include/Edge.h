#ifndef ROUTINGOPTIMIZER_EDGE_H
#define ROUTINGOPTIMIZER_EDGE_H

#include "Node.h"
#include <atomic>

class StoreLayout;

class Edge {
public:
    Edge();
    Edge(int idNode1, int idNode2);
    Edge(int id, int idNode1, int idNode2, double weight = 0);

    [[nodiscard]] int getNode1() const;
    [[nodiscard]] int getNode2() const;
    [[nodiscard]] int getId() const;

    void setNode1(int newIdNode1);
    void setNode2(int newIdNode2);

    void printEdge() const;
    bool operator==(const Edge& other) const;
    double getWeight(const StoreLayout& slayout);

private:
    int id;
    int idNode1;
    int idNode2;
    double weight;

    static std::atomic<int> idCounter;
};

#endif //ROUTINGOPTIMIZER_EDGE_H