#include "../include/rhomb.hpp"

Rhomb::Rhomb():
    Figure()
{}

Rhomb::Rhomb(std::vector<Point>& points):
    Figure(points)
{
    __check_rhomb();
}

Point Rhomb::center() const {
    return Point(
        (__points[2] - __points[0]).x() / 2 + __points[0].x(),
        (__points[2] - __points[0]).y() / 2 + __points[0].y()
    );
}

Rhomb::operator double() const {
    return (__points[2] - __points[0]).len() * (__points[3] - __points[1]).len();
}

std::ostream& Rhomb::__write(std::ostream& out) const {
    out << "Rhomb{(" << __points[0].x() << ", " << __points[0].y() << "), (";
    out << __points[1].x() << ", " << __points[1].y() << "), (";
    out << __points[2].x() << ", " << __points[2].y() << "), (";
    out << __points[3].x() << ", " << __points[3].y() << ")}\n";
    return out;
}

std::istream& Rhomb::__read(std::istream& inp) {
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

    Point side1 = __points[1] - __points[0],
          side2 = __points[2] - __points[1],
          side3 = __points[3] - __points[2],
          side4 = __points[0] - __points[3];

    if (side1.len() == 0
     || side1.len() != side2.len()
     || side2.len() != side3.len()
     || side3.len() != side4.len())
    {
        throw std::invalid_argument("Wrong length of sides");
    }

    if ((__points[2] - __points[0]) * (__points[3] - __points[1]) != 0) {
        throw std::invalid_argument("Daigonals don't intersect at a right angle");
    }
}
