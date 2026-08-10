#include "StoreLayout.h"

#include <list>

StoreLayout::StoreLayout(std::unordered_map<int,Node> areas, std::unordered_map<int,Edge> edges) {
    for (auto& [areaId, area] : areas) {
        this->areas[areaId] = area;
        this->edgesPerArea[area.getId()];
    }
    for (auto& [edgeId, edge] : edges) {
        this->edgesPerArea[edge.getNode1()].push_back(edgeId);
        this->edgesPerArea[edge.getNode2()].push_back(edgeId);
        this->edges[edgeId] = edge;
    }
}

void StoreLayout::addNode(const Node& newNode) {
    this->areas[newNode.getId()] = newNode;
    this->edgesPerArea[newNode.getId()];
}

void StoreLayout::addEdge(const Edge& newEdge) {
    this->edgesPerArea[newEdge.getNode1()].push_back(newEdge.getId());
    this->edgesPerArea[newEdge.getNode2()].push_back(newEdge.getId());
    this->edges[newEdge.getId()] = newEdge;
}

void StoreLayout::deleteNode(int node) {
    this->areas.erase(node);

    auto it = this->edgesPerArea.find(node);
    if (it != this->edgesPerArea.end()) {
        const std::vector<int>& connectedEdges = it->second;

        for (int edgeId : connectedEdges) {
            auto edgeIt = this->edges.find(edgeId);
            if (edgeIt != this->edges.end()) {
                const Edge& e = edgeIt->second;
                int otherNodeId = (e.getNode1() == node) ? e.getNode2() : e.getNode1();

                auto otherIt = this->edgesPerArea.find(otherNodeId);
                if (otherIt != this->edgesPerArea.end()) {
                    auto& otherEdgeList = otherIt->second;
                    otherEdgeList.erase(
                        std::remove(otherEdgeList.begin(), otherEdgeList.end(), edgeId),
                        otherEdgeList.end()
                    );
                }
                this->edges.erase(edgeIt);
            }
        }
        this->edgesPerArea.erase(it);
    }
}

void StoreLayout::deleteEdge(int edgeId) {
    auto edgeIt = this->edges.find(edgeId);
    if (edgeIt != this->edges.end()) {
        const Edge& e = edgeIt->second;

        //Remove from first node's list
        auto list1It = this->edgesPerArea.find(e.getNode1());
        if (list1It != this->edgesPerArea.end()) {
            auto& list1 = list1It->second;
            list1.erase(std::remove(list1.begin(), list1.end(), edgeId), list1.end());
        }

        //Remove from second node's list
        auto list2It = this->edgesPerArea.find(e.getNode2());
        if (list2It != this->edgesPerArea.end()) {
            auto& list2 = list2It->second;
            list2.erase(std::remove(list2.begin(), list2.end(), edgeId), list2.end());
        }

        this->edges.erase(edgeIt);
    }
}

std::unordered_map<int, std::vector<int>> StoreLayout::getEdgesPerArea() const {
    return this->edgesPerArea;
}

std::vector<Edge> StoreLayout::getEdges() const {
    std::vector<Edge> edgesVector;
    for (const auto& [edgeId, edge] : this->edges) {
        edgesVector.push_back(edge);
    }
    return edgesVector;
}

std::vector<Node> StoreLayout::getAreas() const {
    std::vector<Node> nodes;
    for (const auto& [nodeId, node] : this->areas) {
        nodes.push_back(node);
    }
    return nodes;
}

std::optional<Node> StoreLayout::getAreaById(int id) const {
    for (const auto& [areaId, area] : areas) {
        if (areaId == id) return area;
    }
    return std::nullopt;
}

std::optional<Edge> StoreLayout::getEdgeById(int id) const {
    auto it = this->edges.find(id);
    if (it != this->edges.end()) {
        return it->second;
    }
    return std::nullopt;
}

void StoreLayout::printLayout() const {
    std::cout << "Number of Areas: " << this->areas.size() << " | Number of Edges: " << this->getEdges().size()
    << " | Areas and Edges:" << std::endl;
    for (const auto& [nodeId,idEdges] : this->edgesPerArea) {
        std::cout << "------------------" << std::endl;
        getAreaById(nodeId)->printNode();
        for (int e : idEdges) {
            getEdgeById(e)->printEdge();
        }
        std::cout << "------------------" << std::endl << std:: endl;
    }
}