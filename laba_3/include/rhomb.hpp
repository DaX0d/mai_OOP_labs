#pragma once

#include "figure.hpp"

class Rhomb: public Figure {
public:
    Rhomb();
    Rhomb(std::vector<Point>& points);
    virtual ~Rhomb() {};

    virtual Point center() const override;
    virtual operator double() const override;

protected:
    virtual std::ostream& __write(std::ostream& out) const override;
    virtual std::istream& __read(std::istream& inp) override;

private:
    void __check_rhomb() const;
};
