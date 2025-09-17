#include "find_num.h"

void find_num(std::string s) {
    for (char c : s) {
        if (c > 47 && c < 58) {
            std::cout << c;
        }
    }
}
