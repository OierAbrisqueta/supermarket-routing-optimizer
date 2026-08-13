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

    std::unordered_map<int, std::unordered_map<int, double>> distMatrix;

    for (int i{0}; i < nNodes; i++) {
        for (int j{0}; j < nNodes; j++) {
            int idA = nodeIds[i];
            int idB = nodeIds[j];
            
            if (idA == idB) {
                distMatrix[idA][idB] = 0.0;
            } else {
                std::vector<int> path = calculateShortestPath(idA, idB);
                distMatrix[idA][idB] = calculateDistance(path);
            }
        }
    }

    return twoOpt(startId, endId, list, distMatrix);
}

std::vector<int> RouteEngine::twoOpt(int startId, int endId, const std::vector<Item>& list, const std::unordered_map<int, std::unordered_map<int, double>>& distMatrix) {
    std::vector<int> current;
    current.push_back(startId);
    for (const Item& item : list) {
        current.push_back(item.getArea().getId());
    }
    current.push_back(endId);

    bool improvement = true;
    while (improvement) {
        improvement = false;

        for (int i = 1; i < current.size() - 2; i++) {
            for (int k = i + 1; k < current.size() - 1; k++) {
                int beforeCut1 = current[i - 1];
                int afterCut1  = current[i];

                int beforeCut2 = current[k];
                int afterCut2  = current[k + 1];

                double distanceChange =
                    - distMatrix.at(beforeCut1).at(afterCut1)
                    - distMatrix.at(beforeCut2).at(afterCut2)
                    + distMatrix.at(beforeCut1).at(beforeCut2)
                    + distMatrix.at(afterCut1).at(afterCut2);

                if (distanceChange < -0.0001) {
                    std::reverse(current.begin() + i, current.begin() + k + 1);
                    improvement = true;
                }
            }
        }
    }
    
    return current;
}

std::vector<int> RouteEngine::branchAndBound(int startId, int endId, const std::vector<Item>& list, std::vector<int> bestPathFromTwoOpt,
                                                 const std::unordered_map<int, std::unordered_map<int, double>>& distMatrix) {
    double bestCost = calculateDistance(bestPathFromTwoOpt);
    std::vector<int> bestPath = bestPathFromTwoOpt;

    std::vector<int> currentPath;
    currentPath.push_back(startId);

    std::unordered_map<int, bool> visited;
    for (int i{0}; i < list.size(); i++) {
        visited[list.at(i).getArea().getId()] = false; // Use [] instead of .at() when adding new elements
    }

    auto startTime = std::chrono::steady_clock::now();
    int timeLimit = 500;

    bbHelper(startId, endId, 0.0, currentPath, visited, bestPath, bestCost, distMatrix, startTime, timeLimit, list);

    return bestPath;
}

void RouteEngine::bbHelper(int currentNode, int endId, double currentCost, std::vector<int>& currentPath, std::unordered_map<int, bool>& visited,
            std::vector<int>& bestPath, double& bestCost, const std::unordered_map<int, std::unordered_map<int, double>>& distMatrix,
            std::chrono::time_point<std::chrono::steady_clock> startTime, int timeLimitMs, const std::vector<Item>& list) {
    auto now = std::chrono::steady_clock::now();
    auto totalTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
    if (totalTime > timeLimitMs) return;

    if (currentCost > bestCost) return;

    if (currentPath.size() == list.size() + 1) {
        double finalCost = currentCost + distMatrix.at(currentNode).at(endId);
        if (finalCost < bestCost) {
            bestCost = finalCost;
            bestPath = currentPath;
            bestPath.push_back(endId); // Add the end node only to the bestPath copy!
        }
        return;
    }

    for (auto& [nodeId, isVisited] : visited) {
        if (!isVisited) {
            visited.at(nodeId) = true;
            currentPath.push_back(nodeId);
            double interCost = currentCost + distMatrix.at(currentNode).at(nodeId);
            bbHelper(nodeId, endId, interCost, currentPath, visited, bestPath, bestCost, distMatrix, startTime, timeLimitMs, list);
            currentPath.pop_back();
            visited.at(nodeId) = false;
        }
    }
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

