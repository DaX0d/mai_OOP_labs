#pragma once

#include <iostream>

class Figure {
public:
    Figure() = default;
    virtual ~Figure() {}

    virtual std::ostream& operator<<(std::ostream& out);
};
