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
    return std::string();
}

void Thirteen::__from_10_to_13(const ULL_T& int_10) {
    
}

void Thirteen::__from_str_to_13(const std::string& str_int) {

}
