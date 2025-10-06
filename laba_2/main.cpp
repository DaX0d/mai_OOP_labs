#include <iostream>
#include "thirteen.h"

int main() {
    Thirteen zero1 = Thirteen("C") - Thirteen(12);
    ULL_T z_10 = zero1.get_as_int10();
    std::cout << z_10 << std::endl;
    return 0;
}
