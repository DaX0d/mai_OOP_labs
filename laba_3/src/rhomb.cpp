#include "../include/rhomb.hpp"

#include <cmath>

Rhomb::Rhomb():
    Figure()
{}

Rhomb::Rhomb(std::vector<Point>& points):
    Figure(points)
{
    __check_rhomb();
}

// Point Rhomb::center() const {
//     return Point(
//         (__points[2] - __points[0]).x() / 2 + __points[0].x(),
//         (__points[2] - __points[0]).y() / 2 + __points[0].y()
//     );
// }

// Rhomb::operator double() const {
//     return (__points[2] - __points[0]).len() * (__points[3] - __points[1]).len();
// }

std::ostream& Rhomb::__write(std::ostream& out) const {
    out << "Rhomb{(" << __points[0].x() << ", " << __points[0].y() << "), (";
    out << __points[1].x() << ", " << __points[1].y() << "), (";
    out << __points[2].x() << ", " << __points[2].y() << "), (";
    out << __points[3].x() << ", " << __points[3].y() << ")}\n";
    return out;
}

std::istream& Rhomb::__read(std::istream& inp) {
    __points.clear();
    for (int i = 0; i < 4; ++i) {
        double tx, ty;
        inp >> tx >> ty;
        __points.push_back(Point(tx, ty));
    }
    __check_rhomb();
    return inp;
}

void Rhomb::__check_rhomb() const {
    if (__points.size() != 4) {
        throw std::invalid_argument("Wrong count of poins for rhomb");
    }

    const double EPS = 1e-6;

    double len1 = (__points[1] - __points[0]).len();
    for (int i = 1; i < 4; ++i) {
        double len = (__points[(i + 1) % 4] - __points[i]).len();
        if (std::fabs(len - len1) > EPS)
            throw std::invalid_argument("Wrong length of sides in rhomb");
    }

    if ((__points[2] - __points[0]) * (__points[3] - __points[1]) != 0) {
        throw std::invalid_argument("Daigonals don't intersect at a right angle");
    }

    double prev_cross = 0;
    for (int i = 0; i < 4; ++i) {
        Point a = __points[i];
        Point b = __points[(i + 1) % 4];
        Point c = __points[(i + 2) % 4];
        double cross = (b.x() - a.x()) * (c.y() - b.y()) - (b.y() - a.y()) * (c.x() - b.x());
        if (i == 0)
            prev_cross = cross;
        else if (cross * prev_cross < -EPS)
            throw std::invalid_argument("Rhomb is not convex");
    }
}
