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

Point Figure::center() const {
    if (__points.empty())
        return Point();

    Point sum;
    for (const Point& p : __points)
        sum = sum + p;
    return Point(sum.x() / __points.size(), sum.y() / __points.size());
}

Figure::operator double() const {
    if (__points.size() < 3)
        return 0.0;

    double area = 0.0;
    int n = __points.size();
    for (int i = 0; i < n; ++i) {
        const Point& p1 = __points[i];
        const Point& p2 = __points[(i + 1) % n];
        area += p1.x() * p2.y() - p2.x() * p1.y();
    }
    return std::abs(area) / 2.0;
}
