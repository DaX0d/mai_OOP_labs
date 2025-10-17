#pragma once

#include "figure.hpp"

class Rhomb: public Figure {
public:
    Rhomb();
    Rhomb(std::vector<Point>& points);
    virtual ~Rhomb() {};

protected:
    virtual std::ostream& __write(std::ostream& out) const override;
};
