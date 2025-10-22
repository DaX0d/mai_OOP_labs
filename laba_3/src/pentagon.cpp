#include "../include/pentagon.hpp"

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

    Point side1 = __points[1] - __points[0],
          side2 = __points[2] - __points[1],
          side3 = __points[3] - __points[2],
          side4 = __points[4] - __points[3],
          side5 = __points[0] - __points[4];

    if (side1.len() == 0
     || side1.len() != side2.len()
     || side1.len() != side3.len()
     || side1.len() != side4.len()
     || side1.len() != side5.len()) {
        throw std::invalid_argument("Wrong length of sides in pentagon");
    }
}
