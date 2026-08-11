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
    return {};
}