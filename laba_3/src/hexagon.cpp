#include "../include/hexagon.hpp"

#include <cmath>

Hexagon::Hexagon(std::vector<Point> points):
    Figure(points)
{
    __check_hexagon();
}

std::ostream& Hexagon::__write(std::ostream& out) const {
    out << "Hexagon{(" << __points[0].x() << ", " << __points[0].y() << ")";
    for (int i = 1; i < 6; ++i) {
        out << ", (";
        out << __points[i].x() << ", " << __points[i].y() << ")";
    }
    out << "}\n";
    return out;
}

std::istream& Hexagon::__read(std::istream& inp) {
    __points.clear();
    for (int i = 0; i < 6; ++i) {
        double tx, ty;
        inp >> tx >> ty;
        __points.push_back(Point(tx, ty));
    }
    __check_hexagon();
    return inp;
}

void Hexagon::__check_hexagon() const {
    if (__points.size() != 6)
        throw std::invalid_argument("Wrong count of points for hexagon");

    const double EPS = 1e-6;

    double len1 = (__points[1] - __points[0]).len();
    for (int i = 1; i < 6; ++i) {
        double len = (__points[(i + 1) % 6] - __points[i]).len();
        if (std::fabs(len - len1) > EPS)
            throw std::invalid_argument("Wrong length of sides in hexagon");
    }

    double prev_cross = 0;
    for (int i = 0; i < 6; ++i) {
        Point a = __points[i];
        Point b = __points[(i + 1) % 6];
        Point c = __points[(i + 2) % 6];
        double cross = (b.x() - a.x()) * (c.y() - b.y()) - (b.y() - a.y()) * (c.x() - b.x());
        if (i == 0)
            prev_cross = cross;
        else if (cross * prev_cross < -EPS)
            throw std::invalid_argument("Hexagon is not convex");
    }
}
