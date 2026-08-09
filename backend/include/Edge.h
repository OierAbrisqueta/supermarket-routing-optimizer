#ifndef ROUTINGOPTIMIZER_EDGE_H
#define ROUTINGOPTIMIZER_EDGE_H

#include "Node.h"

class Edge {
public:
    Edge();

    [[nodiscard]] const Node& getNode1() const;
    [[nodiscard]] const Node& getNode2() const;
    [[nodiscard]] int getId() const;

    void setNode1(const Node& newNode1);
    void setNode2(const Node& newNode2);

    void printEdge() const;
    bool operator==(const Edge& other) const;

private:
    int id;
    Node node1;
    Node node2;

    static int idCounter;
};

#endif //ROUTINGOPTIMIZER_EDGE_H