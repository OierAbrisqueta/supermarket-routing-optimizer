#ifndef ROUTINGOPTIMIZER_STORELAYOUT_H
#define ROUTINGOPTIMIZER_STORELAYOUT_H

#pragma once
#include <unordered_map>
#include "Node.h"
#include "Edge.h"
#include <vector>

class StoreLayout {
public:
    StoreLayout() = default;
    StoreLayout(std::unordered_map<int,Node> areas, std::unordered_map<int,Edge> edges);

    void addNode(const Node& newNode);
    void addEdge(const Edge& newEdge);
    void deleteNode(int node);
    void deleteEdge(int edge);
    [[nodiscard]] const std::unordered_map<int, std::vector<int>>& getEdgesPerArea() const;
    [[nodiscard]] std::vector<Edge> getEdges() const;
    [[nodiscard]] std::vector<Node> getAreas() const;
    [[nodiscard]] std::optional<Node> getAreaById(int id) const;
    [[nodiscard]] std::optional<Edge> getEdgeById(int id) const;

    void printLayout() const;

private:
    std::unordered_map<int, std::vector<int>> edgesPerArea;
    std::unordered_map<int,Node> areas;
    std::unordered_map<int,Edge> edges;
};

#endif //ROUTINGOPTIMIZER_STORELAYOUT_H