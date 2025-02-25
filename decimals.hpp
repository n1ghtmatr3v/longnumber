#ifndef decimals_HPP
#define decimals_HPP

#include <iostream>
#include <initializer_list>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>


static int binary_precision = 200; 
static int super_new_binary_precision = 200; 

static void Assert(bool condition) {

    if (condition) {
        std::cout << "OK " << std::endl;
    }
    else {
        std::cout << "FAIL " << std::endl;
    }
}

static int SetPrecision(int value) {

    if (value < 0) {
        return binary_precision;
    }

    else { //  value >= 0 
        binary_precision = value;
    }

    if (binary_precision > super_new_binary_precision) {
        super_new_binary_precision = binary_precision; 
    }

    return binary_precision;
}




// деление на 2, чтобы выделить целую часть для дальнейшего перевода в 2-ую систему счисления
static std::string DivisionByTwo(std::string str) {
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
static std::string decimalToBinary(std::string str) {
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
static std::string MultiplyByTwo(std::string str) {
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

static std::string BinaryToDivision_whole(std::string str) {

    std::string new_str = std::string(1, str[0]);

    for (int i = 1; i < str.size(); i++) {
        new_str = MultiplyByTwo(new_str);
        if (new_str[0] == '0') {
            new_str = new_str.substr(1, new_str.size());
        }
        new_str[new_str.size() - 1] += str[i] - '0';
    }

    return new_str;
}

static std::string BinaryToDivision_fractional(std::string str) {

    std::string new_str = "";
    std::string cur_frac = "0";
    new_str = BinaryToDivision_whole(str);



    int k = 0;

    //std::cout << "!!!" << new_str << std::endl;
    for (int i = 0; i < str.size(); i++) {
        int flag = 0;
        int size = cur_frac.size();

        if ((cur_frac[cur_frac.size() - 1] - '0') % 2 != 0) {
            flag = 1;
        }
        else {
            flag = 0;
        }
        cur_frac = DivisionByTwo(cur_frac);
        cur_frac = std::string(size - cur_frac.size(), '0') + cur_frac;

        if (flag == 1) {
            cur_frac += "5";
        }

        if ((new_str[new_str.size() - 1] - '0') % 2 != 0) {
            cur_frac[0] += 5;
        }

        new_str = DivisionByTwo(new_str);

    }

    return cur_frac;
}

// Функция для перевода дробного числа в двоичную систему
static std::string decimal_2(std::string str, int k) {
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




#endif