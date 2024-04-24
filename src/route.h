#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <utility>

class Route {
public:
    Route();

    Route(std::vector<std::pair<int, int>> route);

    const std::vector<std::pair<int, int>>& getRoute() const;

    const std::pair<int, int>& getPoint(int index) const;

    void addPoint(int x, int y);

private:
    std::vector<std::pair<int, int>> route;
};

#endif // ROUTE_H