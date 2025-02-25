


#include "decimals.hpp"
#include "class.hpp"



void TestDivision() {
    Assert(DivisionByTwo("3") == "1");
    Assert(DivisionByTwo("2") == "1");
    Assert(DivisionByTwo("4.4") == "2.2");
    Assert(DivisionByTwo("0") == "0");
    Assert(DivisionByTwo("3.3") == "1");
    Assert(DivisionByTwo("123456789") == "61728394");
    Assert(DivisionByTwo("-1") != "0");
    Assert(DivisionByTwo("-4") == "2");
}

void TestDecimalToBinary() {

    Assert(decimalToBinary("3") == "11");
    Assert(decimalToBinary("0") == "0");
    Assert(decimalToBinary("123456789") == "111010110111100110100010101");
    Assert(decimalToBinary("44012416") == "10100111111001001110000000");
    Assert(decimalToBinary("-1202830") == "-100100101101010001110");
    Assert(decimalToBinary("-0") == "0");
    
}

void TestMultiplyByTwo() {

    Assert(MultiplyByTwo("3") == "06");
    Assert(MultiplyByTwo("0") == "00");
    Assert(MultiplyByTwo("324623049632849623049") == "0649246099265699246098");
    Assert(MultiplyByTwo("1123") == "02246");
    Assert(MultiplyByTwo("-1202830") == "-02405660");
    Assert(MultiplyByTwo("4") == "08");
    Assert(MultiplyByTwo("-0") == "00");

}

void TestBinaryToDivision_whole() {

    Assert(BinaryToDivision_whole("1111") == "15");
    Assert(BinaryToDivision_whole("000000") == "0");
    Assert(BinaryToDivision_whole("101010111111101111") == "176111");
    Assert(BinaryToDivision_whole("-11110") == "-30");
    Assert(BinaryToDivision_whole("-0") == "0");
    Assert(BinaryToDivision_whole("1") == "1");

}

void TestBinaryToDivision_fractional() { 
    Assert(BinaryToDivision_fractional("1111") == "9375");
    Assert(BinaryToDivision_fractional("0000") == "0");
    Assert(BinaryToDivision_fractional("101010111111101111") == "671810150146484375");
    Assert(BinaryToDivision_fractional("-11110") == "-9375");
    Assert(BinaryToDivision_fractional("-0") == "0");
    Assert(BinaryToDivision_fractional("1010100101110") == "661865234375");

}

void Testdecimal_2() {
    int capacity = 10; 

    Assert(decimal_2("1345", capacity) == "0010001001");
    Assert(decimal_2("22", capacity) == "0011100001");
    Assert(decimal_2("2463", capacity) == "0011111100");
    Assert(decimal_2("0", capacity) == "0");
    Assert(decimal_2("-0", capacity) == "0");
    Assert(decimal_2("-7567", capacity) == "-1100000110");
}

void TestSetPrecision() {

    Assert(SetPrecision(10) == 10);
    Assert(SetPrecision(0) == 0); 
    Assert(SetPrecision(-1) == binary_precision);
    Assert(SetPrecision(200) == 201);
    Assert(SetPrecision(-2479438244) == binary_precision);
    Assert(SetPrecision(1000) == 1001);
}

void TestOperator_Equality() {

    LongNumber a = 10;
    LongNumber b = 10;
    
    a.sign = 1;
    b.sign = 1;
   
    Assert(a.sign == b.sign);

    a.MyVector.push_back(20);
    b.MyVector.push_back(30);  

    Assert(a == b); 
    Assert(a.MyVector.size() == b.MyVector.size()); 

    a.sign = -1;
    b.sign = -1;
    a.MyVector.clear(); 
    b.MyVector.clear();
    a.MyVector.push_back(120);
    b.MyVector.push_back(120);
    Assert(a == b);

    a.sign = 1;
    b.sign = -1;
    a.MyVector.push_back(120);
    b.MyVector.push_back(120);

    Assert(a == b);
}

void TestOperator_NotEquality() {

    LongNumber a = 10;
    LongNumber b = -10;



    a.sign = 1;
    b.sign = 1;

    Assert(a.sign != b.sign);

    a.MyVector.push_back(20);
    b.MyVector.push_back(30);

    Assert(a != b);
    Assert(a.MyVector.size() != b.MyVector.size());

    a.sign = -1;
    b.sign = -1;
    a.MyVector.clear();
    b.MyVector.clear();
    a.MyVector.push_back(120);
    b.MyVector.push_back(120);
    Assert(a != b);

    a.sign = 1;
    b.sign = -1;
    a.MyVector.push_back(120);
    b.MyVector.push_back(120);

    Assert(a != b);
}

void TestOperator_More() {

    LongNumber a = 30;
    LongNumber b = 10;

    a.sign = 1;
    b.sign = 1;

    Assert(a > b);

    a.MyVector.push_back(20);
    b.MyVector.push_back(30);

    Assert(a > b);
    Assert(a.MyVector.size() > b.MyVector.size());

    a.sign = -1;
    b.sign = -1;
    a.MyVector.clear();
    b.MyVector.clear();
    a.MyVector.push_back(120);
    b.MyVector.push_back(120);
    Assert(a > b);

    a.sign = 1;
    b.sign = -1;
    a.MyVector.push_back(120);
    b.MyVector.push_back(120);

    Assert(a > b);
}


void TestOperator_NotMore() {

    LongNumber a;
    LongNumber b;
    a.MyVector.clear();
    b.MyVector.clear(); 

    a = 10;
    b = 20;



    a.sign = 1;
    b.sign = 1;

    Assert(a < b);

    a.MyVector.push_back(20);
    b.MyVector.push_back(30);

    Assert(a < b);
    Assert(a.MyVector.size() < b.MyVector.size());

    a.sign = -1;
    b.sign = -1;
    a.MyVector.clear();
    b.MyVector.clear();
    a.MyVector.push_back(120);
    b.MyVector.push_back(120);
    Assert(a < b);

    a.sign = 1;
    b.sign = -1;
    a.MyVector.push_back(120);
    b.MyVector.push_back(120);

    Assert(a < b);
}

void TestOperator_Division() {
    
    LongNumber a = 10;
    LongNumber b = 2;
    LongNumber c = 5;

    LongNumber d = a / b; 

    LongNumber* p = &d;  
     
    Assert(p != NULL); 
    Assert(d.sign == c.sign); 
    Assert(c.MyVector.size() == d.MyVector.size()); 
    int flag = 1;
    if (c.MyVector.size() == d.MyVector.size()) { 
        for (int i = 0; i < c.MyVector.size(); i++) { 
            if (c.MyVector[i] != d.MyVector[i]) { 
                flag = 0; 
                break;
            }
        }
    }

    Assert(flag == 1); 
    Assert(d == c); 
    
}

void TestOperator_Sum() {

    LongNumber a = 10; 
    LongNumber b = 2;
    LongNumber c = 12;
    LongNumber d = a + b;

    LongNumber* p = &d;

    Assert(p != NULL);
    Assert(d.sign == c.sign);
    Assert(c.MyVector.size() == d.MyVector.size());
    int flag = 1;
    if (c.MyVector.size() == d.MyVector.size()) {
        for (int i = 0; i < c.MyVector.size(); i++) {
            if (c.MyVector[i] != d.MyVector[i]) {
                flag = 0;
                break;
            }
        }
    }

    Assert(flag == 1);
    Assert(d == c);

}


void TestOperator_Minus() {

    LongNumber a = 10;
    LongNumber b = 2;
    LongNumber c = 8;

    LongNumber d = a - b;

    LongNumber* p = &d;

    Assert(p != NULL);
    Assert(d.sign == c.sign);
    Assert(c.MyVector.size() == d.MyVector.size());
    int flag = 1;
    if (c.MyVector.size() == d.MyVector.size()) {
        for (int i = 0; i < c.MyVector.size(); i++) {
            if (c.MyVector[i] != d.MyVector[i]) {
                flag = 0;
                break;
            }
        }
    }

    Assert(flag == 1);
    Assert(d == c);

}

void TestOperator_Multiply() {
    
    LongNumber a = 10;
    LongNumber b = 2;
    LongNumber c = 20;

    LongNumber d = a * b;

    LongNumber* p = &d;

    Assert(p != NULL);
    Assert(d.sign == c.sign);
    Assert(c.MyVector.size() == d.MyVector.size());
    int flag = 1;
    if (c.MyVector.size() == d.MyVector.size()) {
        for (int i = 0; i < c.MyVector.size(); i++) {
            if (c.MyVector[i] != d.MyVector[i]) {
                flag = 0;
                break;
            }
        }
    }

    Assert(flag == 1);
    Assert(d == c);

}




int main() {



    //                 TESTS

    //std::cout << "TestDivision:" << std::endl;
    //TestDivision();
    //std::cout << std::endl;

    //std::cout << "TestDecimalToBinary:" << std::endl;
    //TestDecimalToBinary();
    //std::cout << std::endl;

    //std::cout << "TestMultiplyByTwo:" << std::endl;
    //TestMultiplyByTwo();
    //std::cout << std::endl;

    //std::cout << "TestBinaryToDivision_whole:" << std::endl;
    //TestBinaryToDivision_whole();
    //std::cout << std::endl;

    //TestBinaryToDivision_fractional();
    //std::cout << std::endl;

    //Testdecimal_2();
    //std::cout << std::endl;

    //TestSetPrecision();
    //std::cout << std::endl;

    //TestOperator_NotEquality(); 
    //std::cout << std::endl;

    //TestOperator_Equality(); 
    //std::cout << std::endl;

    //TestOperator_More(); 
    //std::cout << std::endl;

    //TestOperator_NotMore(); 
    //std::cout << std::endl;

    //TestOperator_Division(); 
    //std::cout << std::endl;

    //TestOperator_Sum();  
    //std::cout << std::endl;

    //TestOperator_Minus();
    //std::cout << std::endl;

    //TestOperator_Multiply(); 
    //std::cout << std::endl;


}
