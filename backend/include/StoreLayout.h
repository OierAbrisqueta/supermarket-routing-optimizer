#ifndef ROUTINGOPTIMIZER_STORELAYOUT_H
#define ROUTINGOPTIMIZER_STORELAYOUT_H
#include <unordered_map>
#include "Node.h"
#include "Edge.h"
#include <vector>

class StoreLayout {
public:
    StoreLayout() = default;

    void addNode(const Node& newNode);
    void addEdge(const Edge& newEdge);
    void deleteNode(const Node& node);
    void deleteEdge(const Edge& edge);
    [[nodiscard]] std::unordered_map<int, std::vector<Edge>> getEdgesPerArea() const;
    [[nodiscard]] std::vector<Edge> getEdges() const;
    [[nodiscard]] std::vector<Node> getAreas() const;
    [[nodiscard]] std::optional<Node> getAreaById(int id) const;

    void printLayout() const;

private:
    std::unordered_map<int, std::vector<Edge>> edgesPerArea;
    std::vector<Node> areas;
};

#endif //ROUTINGOPTIMIZER_STORELAYOUT_H