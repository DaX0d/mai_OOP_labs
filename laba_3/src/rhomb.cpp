#include "../include/rhomb.hpp"

Rhomb::Rhomb():
    Figure()
{}

Rhomb::Rhomb(std::vector<Point>& points):
    Figure(points)
{
    if (__points.size() != 4) {
        throw std::invalid_argument("Wrong count of poins for rhomb\n");
    }

    Point side1 = __points[1] - __points[0],
          side2 = __points[2] - __points[1],
          side3 = __points[3] - __points[2],
          side4 = __points[0] - __points[3];

    if (side1.len() != side2.len()
     || side2.len() != side3.len()
     || side3.len() != side4.len())
    {
        throw std::invalid_argument("Wrong length of sides\n");
    }

    if ((__points[2] - __points[0]) * (__points[3] - __points[1]) != 0) {
        throw std::invalid_argument("Daigonals don't intersect at a right angle\n");
    }
}

std::ostream& Rhomb::__write(std::ostream& out) const {
    out << "Rhomb{(" << __points[0].x() << ", " << __points[0].y() << "), (";
    out << __points[1].x() << ", " << __points[1].y() << "), (";
    out << __points[2].x() << ", " << __points[2].y() << "), (";
    out << __points[3].x() << ", " << __points[3].y() << ")}\n";
    return out;
}
