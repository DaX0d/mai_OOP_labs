#pragma once

#include <vector>
#include <string>
#include <exception>

typedef unsigned long long ULL_T;

class Thirteen {
public:
    Thirteen();
    Thirteen(const ULL_T& int_10); // ✅
    Thirteen(const std::string& int_str); // ✅
    Thirteen(const Thirteen& other); // ✅
    Thirteen(Thirteen&& other) noexcept; // ✅
    virtual ~Thirteen() noexcept {}; // ✅

    Thirteen& operator=(Thirteen&& other) noexcept; // ✅

    std::vector<unsigned char> get_as_array() const; // ✅
    std::string get_as_string() const; // ✅

    Thirteen operator + (const Thirteen& rhs) const;
    Thirteen operator - (const Thirteen& rhs) const;

    bool operator > (const Thirteen& rhs) const; // ✅
    bool operator < (const Thirteen& rhs) const; // ✅
    bool operator == (const Thirteen& rhs) const; // ✅

private:
    std::vector<unsigned char> __array;
    // Запись идет в обратном подядке, т.е. начиная с маладшего разряда

    void __from_10_to_13(const ULL_T& int_10); // ✅
    void __from_str_to_13(const std::string& str_int); // ✅
};
