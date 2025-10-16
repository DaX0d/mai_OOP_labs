#include "../include/point.hpp"

float Point::len() const {
    return __x * __x + __y * __y;
}

Point Point::operator+(const Point& rhs) const {
    return Point(__x + rhs.__x, __y + rhs.__y);
}

Point Point::operator-(const Point& rhs) const {
    return Point(__x - rhs.__x, __y - rhs.__y);
}

float Point::operator*(const Point& rhs) const {
    return __x * rhs.__x + __y * rhs.__y;
}

bool Point::operator==(const Point& rhs) const {
    return (__x == rhs.__x) && (__y == rhs.__y);
}
