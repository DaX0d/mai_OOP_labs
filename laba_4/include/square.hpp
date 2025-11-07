#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>

#include "figure.hpp"


template<Scalar T>
class Square: public Figure<T> {
public:
    Square() = default;
    Square(const std::vector<Point<T>>& points);
    Square(const Figure<T>& fig);
    // Square(Figure<T>&& fig) noexcept;
    virtual ~Square() = default;

protected:
    virtual std::ostream& __write(std::ostream& out) const override;
    virtual std::istream& __read(std::istream& inp) override;

private:
    void __check_square() const;
};


template<Scalar T>
Square<T>::Square(const std::vector<Point<T>>& points):
    Figure<T>(points)
{
    __check_square();
}

template<Scalar T>
Square<T>::Square(const Figure<T>& fig):
    Figure<T>(fig)
{
    __check_square();
}

template<Scalar T>
std::ostream& Square<T>::__write(std::ostream& out) const {
    out << "Square: ";
    for (const auto& p : this->__points)
        out << "(" << p->x() << ", " << p->y() << ") ";
    return out;
}

template<Scalar T>
std::istream& Square<T>::__read(std::istream& inp) {
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

    __check_square();
    return inp;
}

template<Scalar T>
void Square<T>::__check_square() const {
    if (this->__points.size() != 4)
        throw std::invalid_argument("Wrong count of points for square");

    std::vector<T> d;
    d.reserve(6);

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            Point<T> diff = *this->__points[i] - *this->__points[j];
            d.push_back(diff.len() * diff.len());
        }
    }

    std::sort(d.begin(), d.end());

    const T EPS = static_cast<T>(1e-6);

    bool ok = 
        std::fabs(d[0] - d[1]) < EPS &&
        std::fabs(d[1] - d[2]) < EPS &&
        std::fabs(d[2] - d[3]) < EPS &&
        std::fabs(d[4] - d[5]) < EPS &&
        std::fabs(d[4] - 2 * d[0]) < EPS;

    if (!ok)
        throw std::invalid_argument("Square is not valid");
}
