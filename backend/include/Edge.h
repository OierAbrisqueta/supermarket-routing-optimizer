#ifndef ROUTINGOPTIMIZER_EDGE_H
#define ROUTINGOPTIMIZER_EDGE_H

#include "Node.h"

class Edge {
public:
    Edge();
    Edge(int idNode1, int idNode2);

    [[nodiscard]] int getNode1() const;
    [[nodiscard]] int getNode2() const;
    [[nodiscard]] int getId() const;

    void setNode1(int newIdNode1);
    void setNode2(int newIdNode2);

    void printEdge() const;
    bool operator==(const Edge& other) const;

private:
    int id;
    int idNode1;
    int idNode2;

    static int idCounter;
};

#endif //ROUTINGOPTIMIZER_EDGE_H