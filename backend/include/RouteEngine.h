#ifndef ROUTINGOPTIMIZER_ROUTEENGINE_H
#define ROUTINGOPTIMIZER_ROUTEENGINE_H
#include "StoreLayout.h"
#include "Item.h"

class RouteEngine {
public:
    RouteEngine(const StoreLayout& storeLayout);

    [[nodiscard]] std::vector<int> calculateShortestPath(int startId, int endId) const;
    [[nodiscard]] double hScore(int start, int end) const;
    [[nodiscard]] double calculateDistance(std::vector<int> path) const;

    std::vector<int> calculateOptimalRoute(int startId, int endId, const std::vector<Item>& list);
    std::vector<int> twoOpt(int startId, int endId, const std::vector<Item>& list);
    std::vector<int> branchAndBound(int startId, int endId, const std::vector<Item>& list);

private:
    const StoreLayout& layout;
    std::unordered_map<int, std::unordered_map<int, double>> distanceMatrixCache;
};

#endif //ROUTINGOPTIMIZER_ROUTEENGINE_H