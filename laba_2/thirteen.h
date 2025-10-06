#pragma once

#include <vector>
#include <string>
#include <exception>
#include <math.h>

typedef unsigned long long ULL_T;
typedef unsigned char UC_T;

class Thirteen {
public:
    Thirteen();
    Thirteen(const ULL_T& int_10); // ✅
    Thirteen(const std::string& int_str); // ✅
    Thirteen(const Thirteen& other); // ✅
    Thirteen(Thirteen&& other) noexcept; // ✅
    virtual ~Thirteen() noexcept {}; // ✅

    Thirteen& operator = (Thirteen&& other) noexcept; // ✅

    std::vector<UC_T> get_as_array() const; // ✅
    std::string get_as_string() const; // ✅
    ULL_T get_as_int10() const;

    Thirteen operator + (const Thirteen& rhs) const;
    Thirteen operator - (const Thirteen& rhs) const;

    Thirteen operator += (const Thirteen& rhs);
    Thirteen operator -= (const Thirteen& rhs);

    bool operator > (const Thirteen& rhs) const; // ✅
    bool operator < (const Thirteen& rhs) const; // ✅
    bool operator == (const Thirteen& rhs) const; // ✅

private:
    std::vector<UC_T> __array;
    // Запись идет в обратном подядке, т.е. начиная с маладшего разряда

    void __from_10_to_13(const ULL_T& int_10); // ✅
    void __from_str_to_13(const std::string& str_int); // ✅
};
