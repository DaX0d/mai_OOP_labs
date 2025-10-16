#pragma once

#include "figure.hpp"

class Rhomb: public Figure {
    Rhomb() = default;
    Rhomb(std::vector<Point> points);
    virtual ~Rhomb() {};
};
