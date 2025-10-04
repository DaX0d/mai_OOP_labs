#include <iostream>
#include "thirteen.h"

int main() {
    Thirteen one = 13;
    Thirteen two{"26"};
    std::string o = one.get_as_string();
    std::vector<unsigned char> t = two.get_as_array();
    std::cout << o << std::endl;
    std::cout << t[0] << t[1] << std::endl;
    return 0;
}
