#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cmath>

#include "figure.hpp"


template<Scalar T>
class Rectangle: public Figure<T> {
public:
    Rectangle() = default;
    Rectangle(const std::vector<Point<T>>& points);
    Rectangle(const Figure<T>& fig);
    // Rectangle(Figure<T>&& fig) noexcept = default;
    virtual ~Rectangle() = default;

protected:
    virtual std::ostream& __write(std::ostream& out) const override;
    virtual std::istream& __read(std::istream& inp) override;

private:
    void __check_rectangle() const;
};


template<Scalar T>
Rectangle<T>::Rectangle(const std::vector<Point<T>>& points):
    Figure<T>(points)
{
    __check_rectangle();
}

template<Scalar T>
Rectangle<T>::Rectangle(const Figure<T>& fig):
    Figure<T>(fig)
{
    __check_rectangle();
}

template<Scalar T>
std::ostream& Rectangle<T>::__write(std::ostream& out) const {
    out << "Rectangle: ";
    for (const auto& p : this->__points)
        out << "(" << p->x() << ", " << p->y() << ") ";
    return out;
}

template<Scalar T>
std::istream& Rectangle<T>::__read(std::istream& inp) {
    std::vector<Point<T>> pts(4);
    for (int i = 0; i < 4; ++i) {
        T x, y;
        inp >> x >> y;
        pts.push_back(Point<T>(x, y));
    }

    this->__points.clear();
    for (auto& p : pts)
        this->__points.push_back(std::make_unique<Point<T>>(p));

    __check_rectangle();
    return inp;
}

template<Scalar T>
void Rectangle<T>::__check_rectangle() const {
    if (this->__points.size() != 4)
        throw std::invalid_argument("Wrong count of points for rectangle");

    const T EPS = (T)1e-6;

    T prev_cross = 0;
    for (int i = 0; i < 4; ++i) {
        Point<T> a = *this->__points[i];
        Point<T> b = *this->__points[(i + 1) % 4];
        Point<T> c = *this->__points[(i + 2) % 4];

        Point<T> ab = b - a;
        Point<T> bc = c - b;

        T cross = ab.x() * bc.y() - ab.y() * bc.x();

        if (i == 0)
            prev_cross = cross;
        else if (cross * prev_cross < -EPS)
            throw std::invalid_argument("Rectangle is not convex");
    }

    for (int i = 0; i < 4; ++i) {
        Point<T> a = *this->__points[i];
        Point<T> b = *this->__points[(i + 1) % 4];
        Point<T> c = *this->__points[(i + 2) % 4];

        Point<T> ab = b - a;
        Point<T> bc = c - b;

        if (std::fabs(ab * bc) > EPS)
            throw std::invalid_argument("All rectangle angles must be 90 degrees");
    }
}
