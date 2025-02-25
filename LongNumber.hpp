
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



void Assert(bool condition);
int SetPrecision(int value);

static int flag_division = -1;


class LongNumber {
private:

    std::vector<int> MyVector;
    int sign;

public:

    friend std::istream& operator >> (std::istream& in, LongNumber& other);
    friend std::ostream& operator << (std::ostream& out, LongNumber& other);
    friend LongNumber operator ""_longnum(long double number);
    friend void TestOperator_Equality();
    friend void TestOperator_NotEquality();
    friend void TestOperator_More();
    friend void TestOperator_NotMore();
    friend void TestOperator_Division();
    friend void TestOperator_Sum();
    friend void TestOperator_Minus();
    friend void TestOperator_Multiply();
    

    friend LongNumber sqrt_for_10005(int precision);
    friend LongNumber calculate_pi_chudnovsky(int precision);
    
    //friend LongNumber sqrt_for_10005(int target_precision); 


    bool operator == (const LongNumber& other);
    bool operator != (const LongNumber& other); 
    bool operator > (const LongNumber& other);
    bool operator < (const LongNumber& other);

    LongNumber operator / (const LongNumber& other);
    LongNumber operator * (const LongNumber& other);
    LongNumber operator + (LongNumber& other);
    LongNumber operator - (LongNumber& other);


    
    LongNumber abs() const;

    LongNumber(long double value);
    LongNumber(int value);


    LongNumber(const LongNumber& other); 


    LongNumber& operator = (const LongNumber& other);


    ~LongNumber();// деструктор


    LongNumber(); // конструктор
        
    
    
};



LongNumber operator ""_longnum(long double number);



#endif