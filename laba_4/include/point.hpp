#pragma once

#include <concepts>
#include <cmath>

template<typename T>
concept Scalar = std::is_scalar_v<T>;


template<Scalar T>
class Point {
public:
    Point(): __x(0), __y(0) {}
    Point(const T x, const T y): __x(x), __y(y) {}
    ~Point() {}

    T x() const {return __x;}
    T y() const {return __y;}
    T len() const;

    Point operator+(const Point& rhs) const;
    Point operator-(const Point& rhs) const;
    T operator*(const Point& rhs) const;

    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const {return !(*this == rhs);}
    
private:
    T __x;
    T __y;
};


template<Scalar T>
T Point<T>::len() const {
    return std::sqrt(__x * __x + __y * __y);
}

template<Scalar T>
Point<T> Point<T>::operator+(const Point& rhs) const {
    return Point(__x + rhs.__x, __y + rhs.__y);
}

template<Scalar T>
Point<T> Point<T>::operator-(const Point& rhs) const {
    return Point(__x - rhs.__x, __y - rhs.__y);
}

template<Scalar T>
T Point<T>::operator*(const Point& rhs) const {
    return __x * rhs.__x + __y * rhs.__y;
}

template<Scalar T>
bool Point<T>::operator==(const Point& rhs) const {
    return (__x == rhs.__x) && (__y == rhs.__y);
}
