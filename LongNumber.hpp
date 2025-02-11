
#ifndef LONGNUMBER_HPP
#define LONGNUMBER_HPP

#include <iostream>
#include <initializer_list>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>


class LongNumber {
private:

    std::vector<bool> MyVector;
    int sign;

public:
    friend bool operator == (LongNumber& a, LongNumber& b);
    friend bool operator != (LongNumber& a, LongNumber& b);
    friend bool operator > (LongNumber& a, LongNumber& b);
    friend bool operator < (LongNumber& a, LongNumber& b);
    friend std::istream& operator >> (std::istream& in, LongNumber& a);
    friend std::ostream& operator << (std::ostream& out, LongNumber& a);
    friend LongNumber operator + (LongNumber& a, LongNumber& b);
    friend LongNumber operator - (LongNumber& a, LongNumber& b);
    friend LongNumber operator * (LongNumber& a, LongNumber& b);
    friend LongNumber operator ""_longnum(long double number);
    friend LongNumber operator / (LongNumber& a, LongNumber& b);

    LongNumber(const LongNumber& other); // оператор присваивания

    LongNumber& operator = (const LongNumber& other); // конструктор копирования 

    ~LongNumber (); // деструктор 

    LongNumber(); // конструктор
};

LongNumber operator ""_longnum(long double number);

#endif