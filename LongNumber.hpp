
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


// деление на 2, чтобы выделить целую часть для дальнейшего перевода в 2-ую систему счисления
std::string DivisionByTwo(std::string str) {
    int k = 0;
    std::string new_str = "";

    for (int i = 0; i < str.size(); i++) {
        k = k * 10 + (str[i] - '0');
        new_str.push_back(k / 2 + '0');
        k = k % 2;
    }
    for (int i = 0; i < new_str.size(); i++) {
        if (new_str[i] != '0') {
            return new_str.substr(i, new_str.size());
        }
    }
    return "0";
}




// Функция для перевода целого числа в двоичную систему
std::string decimalToBinary(std::string str) {
    std::string binary = "";
    if (str == "0") {
        return "0";
    }
    while (str[0] != '0') {
        if ((str.back() - '0') % 2 == 0) {
            binary = "0" + binary;
        }
        else {
            binary = "1" + binary;
        }
        str = DivisionByTwo(str);
    }
    return binary;
}

// умножение на 2, чтобы выделить целую часть для дальнейшего перевода в 2-ую систему счисления
std::string MultiplyByTwo(std::string str) {
    int k = 0;
    std::string new_str = "";

    for (int i = str.size() - 1; i >= 0; i--) {
        new_str.push_back((((str[i] - '0') * 2) % 10 + k) + '0');
        k = ((str[i] - '0') * 2) / 10;
    }
    new_str.push_back(k + '0');
    reverse(new_str.begin(), new_str.end());
    return new_str;
}







// Функция для перевода дробного числа в двоичную систему
std::string decimal_2(std::string str, int k) {
    std::string binary = "";
    while (binary.size() < k) {
        int flag = 0;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] != '0') {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            break;
        }

        str = MultiplyByTwo(str);
        if (str[0] == '1') {
            binary += "1";
        }
        else {
            binary += "0";
        }
        str = str.substr(1, str.size());
    }
    return binary;
}



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

    LongNumber(const LongNumber& other) { // 
        sign = other.sign;
        MyVector = other.MyVector;
    }

    LongNumber& operator = (const LongNumber& other) {
        
        if (this != &other) {
            sign = other.sign;
            MyVector = other.MyVector;
        }
        return *this;
    }

    ~LongNumber () { // деструктор

        MyVector.clear();

    }

    LongNumber() { // конструктор
        sign = 1;
        MyVector.assign(201, 0);
    }

    


};

LongNumber operator ""_longnum(long double number) {

    std::string new_str = std::to_string(number);

    LongNumber a;

    //std::cout << new_str << std::endl;

    if (new_str[0] == '-') {
        a.sign = -1;
        new_str = new_str.substr(1, new_str.size());
    }
    else {
        a.sign = 1;
    }

    std::string whole_part = ""; // целая часть
    std::string fractional_part = ""; // дробная часть

    int pozition = -1; // позиция точки
    for (int i = 0; i < new_str.size(); i++) {
        if (new_str[i] == ',') {
            pozition = i;
            break;
        }
    }
    if (pozition != -1) {
        whole_part = new_str.substr(0, pozition);
        fractional_part = new_str.substr(pozition + 1, new_str.size());
        if (pozition == 0) {
            whole_part = "0";
        }
    }

    else {
        whole_part = new_str;
        fractional_part = "0";
    }



    whole_part = decimalToBinary(whole_part);
    fractional_part = decimal_2(fractional_part, 200);




    while (fractional_part.size() < 200) {
        fractional_part.push_back('0');
    }



    reverse(whole_part.begin(), whole_part.end());
    reverse(fractional_part.begin(), fractional_part.end());


    a.MyVector.clear();

    for (char x : fractional_part) { // перебрать все символы в fractional_part
        a.MyVector.push_back(x - '0');
    }
    for (char x : whole_part) { // перебрать все символы в whole_part
        a.MyVector.push_back(x - '0');
    }

    return a;
}

#endif