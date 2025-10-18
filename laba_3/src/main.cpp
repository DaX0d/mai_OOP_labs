#include <iostream>

#include "../include/figure.hpp"
#include "../include/rhomb.hpp"

int main() {
    std::vector<Point> points{Point(0, 1), Point(1, 2), Point(2, 1), Point(1, 0)};

    Rhomb rhomb(points);

    Figure* figures[] = {&rhomb};

    std::cout << *(figures[0]) << rhomb.center().x() << ", " << rhomb.center().y() << "\n";
    std::cout << static_cast<double>(*(figures[0]));

    return 0;
}
