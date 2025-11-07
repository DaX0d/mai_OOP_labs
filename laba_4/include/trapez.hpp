#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cmath>

#include "figure.hpp"


template<Scalar T>
class Trapezoid: public Figure<T> {
public:
    Trapezoid() = default;
    Trapezoid(const std::vector<Point<T>>& points);
    Trapezoid(const Figure<T>& fig);
    virtual ~Trapezoid() = default;

protected:
    virtual std::ostream& __write(std::ostream& out) const override;
    virtual std::istream& __read(std::istream& inp) override;

private:
    void __check_trapezoid() const;

    static T cross(const Point<T>& u, const Point<T>& v) {
        return u.x() * v.y() - u.y() * v.x();
    }
};


template<Scalar T>
Trapezoid<T>::Trapezoid(const std::vector<Point<T>>& points):
    Figure<T>(points)
{
    __check_trapezoid();
}

template<Scalar T>
Trapezoid<T>::Trapezoid(const Figure<T>& fig):
    Figure<T>(fig)
{
    __check_trapezoid();
}

template<Scalar T>
std::ostream& Trapezoid<T>::__write(std::ostream& out) const {
    out << "Trapezoid: ";
    for (const auto& p: this->__points)
        out << "(" << p->x() << ", " << p->y() << ") ";
    return out;
}

template<Scalar T>
std::istream& Trapezoid<T>::__read(std::istream& inp) {
    std::vector<Point<T>> pts(4);
    for (int i = 0; i < 4; ++i) {
        T x, y;
        inp >> x >> y;
        pts.push_back(Point<T>(x, y));
    }

    this->__points.clear();
    this->__points.reserve(4);
    for (auto& p: pts)
        this->__points.push_back(std::make_unique<Point<T>>(p));

    __check_trapezoid();
    return inp;
}

template<Scalar T>
void Trapezoid<T>::__check_trapezoid() const {
    if (this->__points.size() != 4)
        throw std::invalid_argument("Wrong count of points for trapezoid");

    const T EPS = (T)1e-6;

    T prev_cross = 0;
    for (int i = 0; i < 4; ++i) {
        Point<T> a = *this->__points[i];
        Point<T> b = *this->__points[(i + 1) % 4];
        Point<T> c = *this->__points[(i + 2) % 4];

        Point<T> ab = b - a;
        Point<T> bc = c - b;

        T cross_val = ab.x() * bc.y() - ab.y() * bc.x();

        if (i == 0)
            prev_cross = cross_val;
        else if (cross_val * prev_cross < -EPS)
            throw std::invalid_argument("Trapezoid is not convex");
    }

    Point<T> a = *this->__points[0];
    Point<T> b = *this->__points[1];
    Point<T> c = *this->__points[2];
    Point<T> d = *this->__points[3];

    Point<T> ab = b - a;
    Point<T> cd = d - c;
    Point<T> bc = c - b;
    Point<T> ad = a - d;

    bool ok =
        std::fabs(cross(ab, cd)) < EPS ||
        std::fabs(cross(bc, ad)) < EPS;

    if (!ok)
        throw std::invalid_argument("Trapezoid must have one pair of parallel sides");
}
