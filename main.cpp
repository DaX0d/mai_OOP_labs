#include <iostream>
#include "find_num.h"

int main() {
    std::cout << "Введите строку с числом:\n";
    std::string s;
    std::cin >> s;
    find_num(s);

    return 0;
}
