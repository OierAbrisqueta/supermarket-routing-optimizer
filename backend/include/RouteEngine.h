#ifndef ROUTINGOPTIMIZER_ROUTEENGINE_H
#define ROUTINGOPTIMIZER_ROUTEENGINE_H

#pragma once
#include "StoreLayout.h"
#include "Item.h"

class RouteEngine {
public:
    RouteEngine(const StoreLayout& storeLayout);

    [[nodiscard]] std::vector<int> calculateShortestPath(int startId, int endId) const;
    [[nodiscard]] double hScore(int start, int end) const;
    [[nodiscard]] double calculateDistance(const std::vector<int>& path) const;

    std::vector<int> calculateOptimalRoute(int startId, int endId, const std::vector<Item>& list);
    std::vector<int> twoOpt(int startId, int endId, const std::vector<Item>& list, const std::unordered_map<int, std::unordered_map<int, double>>& distMatrix);
    std::vector<int> branchAndBound(int startId, int endId, const std::vector<Item>& list, const std::vector<int>& bestPathFromTwoOpt,
                                                 const std::unordered_map<int, std::unordered_map<int, double>>& distMatrix);
    void bbHelper(int currentNode, int endId, double currentCost, std::vector<int>& currentPath, std::unordered_map<int, bool>& visited,
            std::vector<int>& bestPath, double& bestCost, const std::unordered_map<int, std::unordered_map<int, double>>& distMatrix,
            std::chrono::time_point<std::chrono::steady_clock> startTime, int timeLimitMs, const std::vector<Item>& list);

private:
    const StoreLayout& layout;
    std::unordered_map<int, std::unordered_map<int, double>> distanceMatrixCache;
};

#endif //ROUTINGOPTIMIZER_ROUTEENGINE_H