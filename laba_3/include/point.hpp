#pragma once

class Point {
public:
    Point(): __x(0), __y(0) {}
    Point(const double x, const double y): __x(x), __y(y) {}
    ~Point() {}

    double x() const {return __x;}
    double y() const {return __y;}
    double len() const;

    Point operator+(const Point& rhs) const;
    Point operator-(const Point& rhs) const;
    double operator*(const Point& rhs) const;

    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const {return !(*this == rhs);}
    
private:
    double __x;
    double __y;
};
