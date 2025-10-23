#pragma once

#include "figure.hpp"

class Hexagon: public Figure {
public:
    Hexagon() = default;
    Hexagon(std::vector<Point> points);
    virtual ~Hexagon() {}

protected:
    virtual std::ostream& __write(std::ostream& out) const override;
    virtual std::istream& __read(std::istream& inp) override;

private:
    void __check_hexagon() const;
};
