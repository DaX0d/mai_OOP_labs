#include "thirteen.h"

Thirteen::Thirteen() {
    __array.push_back((UC_T)'0');
}

Thirteen::Thirteen(const ULL_T& int_10) {
    __from_10_to_13(int_10);
}

Thirteen::Thirteen(const std::string& int_str) {
    __from_str_to_13(int_str);
}

Thirteen::Thirteen(const Thirteen& other): __array(other.__array) {}

Thirteen& Thirteen::operator=(Thirteen&& other) noexcept {
    if (this != &other) {
        __array = std::move(other.__array);
        other.__array.clear();
    }
    return *this;
}

Thirteen::Thirteen(Thirteen&& other) noexcept: 
    __array(std::move(other.__array)) {}

std::vector<UC_T> Thirteen::get_as_array() const {
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

ULL_T Thirteen::get_as_int10() const {
    ULL_T ans = 0;
    int n = __array.size();
    for (int i = 0; i < n; ++i) {
        UC_T ch = __array[i];
        short val = (ch < (UC_T)'A') ? (ch - (UC_T)'0') : (10 + ch - (UC_T)'A');
        ans += val * pow(13, i);
    }
    return ans;
}

Thirteen Thirteen::operator+(const Thirteen& rhs) const {
    const UC_T alphabet[] = "0123456789ABC";
    int n1 = __array.size(), n2 = rhs.__array.size(),
        n = std::max(n1, n2);
    Thirteen ans;
    ans.__array.clear();

    int sum = 0,
        tmp = 0,
        a, b;
    for (int i = 0; i < n; ++i) {
        if (i < n1) {
            UC_T ch = __array[i];
            a = (ch < (UC_T)'A') ? (ch - (UC_T)'0') : (10 + ch - (UC_T)'A');
        } else {
            a = 0;
        }
        if (i < n2) {
            UC_T ch = rhs.__array[i];
            b = (ch < (UC_T)'A') ? (ch - (UC_T)'0') : (10 + ch - (UC_T)'A');
        } else {
            b = 0;
        }
        sum = a + b + tmp;
        tmp = sum / 13;
        ans.__array.push_back(alphabet[sum % 13]);
    }
    if (tmp) ans.__array.push_back(alphabet[tmp]);

    return ans;
}

Thirteen Thirteen::operator-(const Thirteen& rhs) const {
    return Thirteen();
}

Thirteen Thirteen::operator+=(const Thirteen& rhs) {
    return Thirteen();
}

Thirteen Thirteen::operator-=(const Thirteen& rhs) {
    return Thirteen();
}

bool Thirteen::operator>(const Thirteen& rhs) const {
    int n1 = __array.size(), n2 = rhs.__array.size();
    if (n1 < n2) {
        return false;
    } else {
        if (n1 > n2) return true;
    }
    for (int i = n1 - 1; i >= 0; --i) {
        if (__array[i] > rhs.__array[i]) return true;
    }
    return false;
}

bool Thirteen::operator<(const Thirteen& rhs) const {
    return rhs > *this;
}

bool Thirteen::operator==(const Thirteen& rhs) const {
    return __array == rhs.__array;
}

void Thirteen::__from_10_to_13(const ULL_T& int_10) {
    if (int_10 == 0) {
        __array.push_back('0');
        return;
    }
    const UC_T alphabet[] = "0123456789ABC";
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

        __array.push_back((UC_T)ch);
    }
}
