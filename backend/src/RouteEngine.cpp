#include "RouteEngine.h"

RouteEngine::RouteEngine(const StoreLayout& storeLayout) : layout(storeLayout) {
}

#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

struct AStarNode {
    int id;
    double fScore;

    bool operator>(const AStarNode& other) const {
        return fScore > other.fScore;
    }
};

std::vector<int> RouteEngine::calculateShortestPath(int startId, int endId) const {
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;

    std::unordered_map<int, double> gScore;
    std::unordered_map<int, int> cameFrom;

    gScore[startId] = 0;
    AStarNode nodeStart{startId, hScore(startId, endId)};
    openSet.push(nodeStart);

    auto edgesPerArea = layout.getEdgesPerArea();
    while (!openSet.empty()) {
        AStarNode current = openSet.top();
        openSet.pop();

        if (current.id == endId) {
            std::vector<int> finalPath;

            int trackId = endId;
            finalPath.push_back(trackId);

            while (cameFrom.find(trackId) != cameFrom.end()) {
                trackId = cameFrom[trackId];
                finalPath.push_back(trackId);
            }

            std::reverse(finalPath.begin(), finalPath.end());
            return finalPath;
        }

        for (int id : edgesPerArea[current.id]) {
            Edge e = layout.getEdgeById(id).value();
            int idNeighbor = e.getNode1() == current.id ? e.getNode2() : e.getNode1();
            double neighborGScore = gScore[current.id] + e.getWeight(layout);
            if (gScore.find(idNeighbor) == gScore.end() || neighborGScore < gScore[idNeighbor]) {
                gScore[idNeighbor] = neighborGScore;
                cameFrom[idNeighbor] = current.id;

                double neighborFScore = hScore(idNeighbor, endId) + neighborGScore;
                AStarNode neighbor{idNeighbor, neighborFScore};
                openSet.push(neighbor);
            }


        }
    }
    
    return {};
}

double RouteEngine::hScore(int start, int end) const {
    Node nodeStart = this->layout.getAreaById(start).value();
    Node nodeEnd = this->layout.getAreaById(end).value();
    return (std::abs(nodeStart.getX() - nodeEnd.getX()) + std::abs(nodeStart.getY() - nodeEnd.getY()));
}

std::vector<int> RouteEngine::calculateOptimalRoute(int startId, int endId, const std::vector<Item>& list) {
    std::vector<int> nodeIds;
    nodeIds.push_back(startId);
    for (int i{0}; i < list.size(); i++) {
        nodeIds.push_back(list.at(i).getArea().getId());
    }
    nodeIds.push_back(endId);

    int nNodes = nodeIds.size();
    std::vector<std::vector<double>> distanceMatrix(nNodes, std::vector<double>(nNodes, 0.0));

    for (int i{0}; i < nNodes; i++) {
        for (int j{0}; j <nNodes; j++) {
            if (i == j) {
                distanceMatrix[i][j] = 0;
            }
            if (nodeIds[i] == nodeIds[j]) {
                distanceMatrix[i][j] = 0;
            } else {
                std::vector<int> path = calculateShortestPath(i, j);
                distanceMatrix[i][j] = calculateDistance(path);
            }
        }
    }


    return {};
}

std::vector<int> RouteEngine::twoOpt(int startId, int endId, const std::vector<Item>& list) {

}

std::vector<int> RouteEngine::branchAndBound(int startId, int endId, const std::vector<Item>& list) {

}

[[nodiscard]] double RouteEngine::calculateDistance(std::vector<int> path) const {
    double sum = 0;
    int prevNode = path.at(0);
    std::unordered_map<int, std::vector<int>> edgesMap = this->layout.getEdgesPerArea();

    for (int i{1}; i < path.size(); i++) {
        int current = path.at(i);
        double min = 100000000000000;
        for (int edgeId : edgesMap.at(prevNode)) {
            Edge e = this->layout.getEdgeById(edgeId).value();
            if ((e.getNode1() == current || e.getNode2() == current) && e.getWeight(layout) < min) min = e.getWeight(layout);
        }
        prevNode = current;
        sum += min;
    }
    return sum;
}

