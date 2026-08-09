#include "StoreLayout.h"

#include <list>

void StoreLayout::addNode(const Node& newNode) {
    this->areas.push_back(newNode);
    this->edgesPerArea[newNode.getId()];
}

void StoreLayout::addEdge(const Edge& newEdge) {
    this->edgesPerArea[newEdge.getNode1().getId()].push_back(newEdge);
    this->edgesPerArea[newEdge.getNode2().getId()].push_back(newEdge);
}

void StoreLayout::deleteNode(const Node& node) {
    areas.erase(std::remove(areas.begin(), areas.end(), node), areas.end());
    for (auto& [nodeId, edges] : this->edgesPerArea) {
        edges.erase(
        std::remove_if(edges.begin(), edges.end(),
        [&node](const Edge& e) {return (e.getNode2().getId() == node.getId() || e.getNode1().getId() == node.getId());}
            ),
            edges.end()
        );
    }
    this->edgesPerArea.erase(node.getId());
}

void StoreLayout::deleteEdge(const Edge& edge) {
    std::vector<Edge> edgeList1 = this->edgesPerArea[edge.getNode1().getId()];
    edgeList1.erase(
        std::remove(edgeList1.begin(), edgeList1.end(), edge),
        edgeList1.end()
    );

    std::vector<Edge> edgeList2 = this->edgesPerArea[edge.getNode2().getId()];
    edgeList2.erase(
        std::remove(edgeList2.begin(), edgeList2.end(), edge),
        edgeList2.end()
    );
}

std::unordered_map<int, std::vector<Edge>> StoreLayout::getEdgesPerArea() const {
    return this->edgesPerArea;
}

std::vector<Edge> StoreLayout::getEdges() const {
    std::vector<Edge> listEdges;
    for (auto& [nodeId, edges] : this->edgesPerArea) {
        for (Edge e : edges) {
            if (std::find(listEdges.begin(), listEdges.end(), e) == listEdges.end()) {
                listEdges.push_back(e);
            }
        }
    }
    return listEdges;
}

std::vector<Node> StoreLayout::getAreas() const {
    return this->areas;
}

std::optional<Node> StoreLayout::getAreaById(int id) const {
    for (Node area : areas) {
        if (area.getId() == id) return area;
    }
    return std::nullopt;
}

void StoreLayout::printLayout() const {
    std::cout << "Number of Areas: " << this->areas.size() << " | Number of Edges: " << this->getEdges().size()
    << " | Areas and Edges:" << std::endl;
    for (const auto& [nodeId, edges] : this->edgesPerArea) {
        std::cout << "------------------" << std::endl;
        getAreaById(nodeId)->printNode();
        for (Edge e : edges) {
            e.printEdge();
        }
        std::cout << "------------------" << std::endl << std:: endl;
    }
}