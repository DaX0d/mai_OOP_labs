#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

#include "point.hpp"


template<Scalar T>
class Figure {
public:
    Figure() = default;
    Figure(const std::vector<Point<T>>& points);
    Figure(const Figure<T>& fig);
    Figure(Figure<T>&& fig) noexcept = default;
    virtual ~Figure() = default;

    Figure<T>& operator=(const Figure<T>& rhs);
    Figure<T>& operator=(Figure<T>&& rhs) noexcept = default;

    virtual bool operator==(const Figure<T>& rhs) const;

    virtual Point<T> center() const;
    virtual operator double() const;

    friend std::ostream& operator<<(std::ostream& out, const Figure<T>& fig) { return fig.__write(out); }
    friend std::istream& operator>>(std::istream& inp, Figure<T>& fig) { return fig.__read(inp); }

protected:
    std::vector<std::unique_ptr<Point<T>>> __points;

    virtual std::ostream& __write(std::ostream& out) const { return out; }
    virtual std::istream& __read(std::istream& inp) { return inp; }
};


template<Scalar T>
Figure<T>::Figure(const std::vector<Point<T>>& points) {
    for (const auto& p: points)
        __points.push_back(std::make_unique<Point<T>>(p));
}

template<Scalar T>
Figure<T>::Figure(const Figure<T>& fig) {
    for (const auto& p: fig.__points)
        __points.push_back(std::make_unique<Point<T>>(*p));
}

template<Scalar T>
Figure<T>& Figure<T>::operator=(const Figure<T>& rhs) {
    if (this != &rhs) {
        __points.clear();
        for (const auto& p : rhs.__points)
            __points.push_back(std::make_unique<Point<T>>(*p));
    }
    return *this;
}

template<Scalar T>
bool Figure<T>::operator==(const Figure<T>& rhs) const {
    const double EPS = 1e-6;
    return (__points.size() == rhs.__points.size()) &&
           (std::fabs(static_cast<double>(*this) - static_cast<double>(rhs)) <= EPS);
}

template<Scalar T>
Point<T> Figure<T>::center() const {
    if (__points.empty())
        return Point<T>();

    Point<T> sum;
    for (const auto& p : __points)
        sum = sum + *p;
    return Point<T>(sum.x() / __points.size(), sum.y() / __points.size());
}

template<Scalar T>
Figure<T>::operator double() const {
    if (__points.size() < 3)
        return 0.0;

    double area = 0.0;
    int n = __points.size();
    for (int i = 0; i < n; ++i) {
        const Point<T>& p1 = *__points[i];
        const Point<T>& p2 = *__points[(i + 1) % n];
        area += p1.x() * p2.y() - p2.x() * p1.y();
    }
    return std::abs(area) / 2.0;
}
