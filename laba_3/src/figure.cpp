#include "../include/figure.hpp"

Figure::Figure(std::vector<Point>& points):
    __points(points)
{}

Figure::Figure(const Figure& fig):
    __points(fig.__points)
{}

Figure::Figure(Figure&& fig):
    __points(std::move(fig.__points))
{}

Figure& Figure::operator=(const Figure& rhs) {
    if (this != &rhs) {
        __points = rhs.__points;
    }
    return *this;
}

bool Figure::operator==(const Figure& rhs) const {
    return (__points.size() == rhs.__points.size()) && (static_cast<double>(*this) == static_cast<double>(rhs));
}
