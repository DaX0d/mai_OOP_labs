#include "figure.hpp"

class Pentagon: public Figure {
public:
    Pentagon();
    Pentagon(std::vector<Point>& points);
    virtual ~Pentagon() {}

    virtual Point center() const override;
    virtual operator double() const override;

protected:
    virtual std::ostream& __write(std::ostream& out) const override;
    virtual std::istream& __read(std::istream& inp) override;

public:
    void __check_pentagon() const;
};
