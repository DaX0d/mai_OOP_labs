#include "../include/pentagon.hpp"

#include <cmath>

Pentagon::Pentagon():
    Figure()
{}

Pentagon::Pentagon(std::vector<Point>& points):
    Figure(points)
{
    __check_pentagon();
}

Point Pentagon::center() const {
    return Point();
}

Pentagon::operator double() const {
    return -1;
}

std::ostream& Pentagon::__write(std::ostream& out) const {
    out << "Pentagon((" << __points[0].x() << ", " << __points[1].y() << ")";
    for (int i = 1; i < 5; ++i) {
        out << ", (";
        out << __points[i].x() << ", " << __points[i].y() << ")";
    }
    out << ")\n";
    return out;
}

std::istream& Pentagon::__read(std::istream& inp) {
    return inp;
}

void Pentagon::__check_pentagon() const {
    if (__points.size() != 5) {
        throw std::invalid_argument("Wrong count of poins for pentagon");
    }

    const double EPS = 1e-6;

    double len1 = (__points[1] - __points[0]).len();
    for (int i = 1; i < 5; ++i) {
        double len = (__points[(i + 1) % 5] - __points[i]).len();
        if (std::fabs(len - len1) > EPS)
            throw std::invalid_argument("Wrong length of sides in pentagon");
    }

    double prev_cross = 0;
    for (int i = 0; i < 5; ++i) {
        Point a = __points[i];
        Point b = __points[(i + 1) % 5];
        Point c = __points[(i + 2) % 5];
        double cross = (b.x() - a.x()) * (c.y() - b.y()) - (b.y() - a.y()) * (c.x() - b.x());
        if (i == 0)
            prev_cross = cross;
        else if (cross * prev_cross < -EPS)
            throw std::invalid_argument("Pentagon is not convex");
    }
}
