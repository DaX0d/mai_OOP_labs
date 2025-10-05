#include <iostream>
#include "thirteen.h"

int main() {
    Thirteen zero1 = Thirteen(13);
    Thirteen zero2 = Thirteen("10");
    std::cout << (zero1 == zero2) << std::endl;
    return 0;
}
