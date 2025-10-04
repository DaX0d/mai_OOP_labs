#include "thirteen.h"

Thirteen::Thirteen(): __array('0', '\0') {}

Thirteen::Thirteen(const ULL_T& int_10) {
    __from_10_to_13(int_10);
}

Thirteen::Thirteen(const std::string& int_str) {
    __from_str_to_13(int_str);
}

Thirteen::Thirteen(const Thirteen& other): __array(other.__array) {}

Thirteen::Thirteen(Thirteen&& other) {
}

std::vector<unsigned char> Thirteen::get_as_array() const {
    return __array;
}

std::string Thirteen::get_as_string() const {
    unsigned n = __array.size();
    std::string ans = "";
    for (int i = n - 1; i >= 0; --i) {
        ans += __array[i];
    }
    return ans;
}

void Thirteen::__from_10_to_13(const ULL_T& int_10) {
    if (int_10 == 0) {
        __array.push_back('0');
        return;
    }
    const unsigned char alphabet[] = "0123456789ABC";
    ULL_T tmp = int_10;
    while (tmp > 0) {
        int digit = (tmp % 13);
        __array.push_back(alphabet[digit]);
        tmp /= 13;
    }
}

void Thirteen::__from_str_to_13(const std::string& str_int) {
    for (int i = str_int.length() - 1; i >= 0; --i) {
        char ch = str_int[i];

        if (
            !(ch >= '0' && ch <= '9')
            && !(ch >= 'A' && ch <= 'C')
        ) throw std::exception();

        __array.push_back((unsigned char)ch);
    }
}
