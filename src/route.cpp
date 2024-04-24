#include <vector>
#include <utility>
#include <stdexcept>
#include "route.h"


Route::Route() : route() {} // Costruttore di default
Route::Route(std::vector<std::pair<int, int>> route) : route(route) {}

const std::vector<std::pair<int, int>>& Route::getRoute() const { return route; }

const std::pair<int, int>& Route::getPoint(int index) const {
    if (index < 0 || index >= route.size()) {
        throw std::out_of_range("Index is out of range");
    }
    return route[index];
}

void Route::addPoint(int x, int y) {
    route.push_back(std::make_pair(x, y));
}
