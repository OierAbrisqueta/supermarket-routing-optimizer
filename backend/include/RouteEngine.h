#ifndef ROUTINGOPTIMIZER_ROUTEENGINE_H
#define ROUTINGOPTIMIZER_ROUTEENGINE_H
#include "StoreLayout.h"
#include "Item.h"

class RouteEngine {
public:
    RouteEngine(const StoreLayout& storeLayout);

    std::vector<int> calculateShortestPath(int startId, int endId) const;
    std::vector<int> calculateOptimalRoute(int startId, int endId, const std::vector<Item>& list);

    [[nodiscard]] double hScore(int start, int end) const;

private:
    const StoreLayout& layout;
    std::unordered_map<int, std::unordered_map<int, double>> distanceMatrixCache;
};

#endif //ROUTINGOPTIMIZER_ROUTEENGINE_H