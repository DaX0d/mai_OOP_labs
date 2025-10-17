#include <iostream>

#include "../include/figure.hpp"
#include "../include/rhomb.hpp"

int main() {
    std::vector<Point> points{Point(-1, 0), Point(0, 0.5), Point(1, 0), Point(0, -0.5)};

    Rhomb rhomb(points);

    std::cout << rhomb;

    return 0;
}
