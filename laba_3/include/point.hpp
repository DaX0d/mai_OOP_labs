#pragma once

class Point {
public:
    Point(): __x(0), __y(0) {}
    Point(const float x, const float y): __x(x), __y(y) {}
    ~Point() {}

    float x() const {return __x;}
    float y() const {return __y;}

    Point operator+(const Point& rhs) const;
    Point operator-(const Point& rhs) const;
    float operator*(const Point& rhs) const;

    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const {return !(*this == rhs);}
private:
    float __x;
    float __y;
};
