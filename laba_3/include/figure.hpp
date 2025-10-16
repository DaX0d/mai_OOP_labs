#pragma once

#include <iostream>
#include <vector>

#include "point.hpp"

class Figure {
public:
    Figure() = default;
    virtual ~Figure() {}

    virtual Point center() const;

    virtual operator double() const;

    friend std::ostream& operator<<(std::ostream& out, Figure& fig) {return fig.__write(out);}
    friend std::istream& operator>>(std::istream& inp, Figure& fig) {return fig.__read(inp);}

protected:
    std::vector<Point> __points;

    virtual std::ostream& __write(std::ostream& out) const;
    virtual std::istream& __read(std::istream& inp);
};
