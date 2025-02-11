#include "LongNumber.hpp"


std::string BinaryToDivision_whole(std::string str) {

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

std::string BinaryToDivision_fractional(std::string str) {

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



bool operator == (LongNumber& a, LongNumber& b) {
    if (a.sign != b.sign) {
        return false;
    }

    if (a.MyVector == b.MyVector) {
        return true;
    }
    else {
        return false;
    }
}

bool operator != (LongNumber& a, LongNumber& b) {
    return !(a == b);
}

bool operator > (LongNumber& a, LongNumber& b) {
    if (a.sign != b.sign) {
        return a.sign > b.sign;
    }

    if (a.sign == 1) {
        if (a.MyVector.size() > b.MyVector.size()) {
            return true;
        }
        if (a.MyVector.size() < b.MyVector.size()) {
            return false;
        }
        for (int i = a.MyVector.size() - 1; i >= 0; i--) {
            if (a.MyVector[i] > b.MyVector[i]) {
                return true;
            }
            else if (a.MyVector[i] < b.MyVector[i]) {
                return false;
            }
        }
        return false;
    }

    if (a.sign == -1) {
        if (a.MyVector.size() > b.MyVector.size()) {
            return false;
        }
        if (a.MyVector.size() < b.MyVector.size()) {
            return true;
        }
        for (int i = a.MyVector.size() - 1; i >= 0; i--) {
            if (a.MyVector[i] > b.MyVector[i]) {
                return false;
            }
            else if (a.MyVector[i] < b.MyVector[i]) {
                return true;
            }
        }
        return false;
    }
}

bool operator < (LongNumber& a, LongNumber& b) {
    return !(a > b) && (a != b);
}

std::istream& operator >> (std::istream& in, LongNumber& a) {


    std::string new_str = "";
    in >> new_str;
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
        if (new_str[i] == '.') {
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

    //std::cout << "&&  " << fractional_part.size() << std::endl;
    //std::cout << "&&  " << whole_part.size() << std::endl;

    a.MyVector.clear();

    for (char x : fractional_part) { // перебрать все символы в fractional_part
        a.MyVector.push_back(x - '0');
    }
    for (char x : whole_part) { // перебрать все символы в whole_part
        a.MyVector.push_back(x - '0');
    }

    std::cout << whole_part << "." << fractional_part << std::endl;

    //std::cout << a.MyVector.size() << std::endl;

    return in;

}

std::ostream& operator << (std::ostream& out, LongNumber& a) {

    std::string new_str = "";
    std::string whole_part = ""; // целая часть
    std::string fractional_part = ""; // дробная часть

    for (int i = 0; i < a.MyVector.size(); i++) {
        if (i < 200) {
            fractional_part.push_back(a.MyVector[i] + '0');

        }
        else {
            whole_part.push_back(a.MyVector[i] + '0');
        }
        //std::cout << a.MyVector[i];
    }


    reverse(fractional_part.begin(), fractional_part.end());
    reverse(whole_part.begin(), whole_part.end());

    //std::cout << whole_part << '.' << fractional_part << std::endl;

    whole_part = BinaryToDivision_whole(whole_part);
    fractional_part = BinaryToDivision_fractional(fractional_part);

    if (a.sign == 1) {
        out << whole_part << '.' << fractional_part;
    }
    else if (a.sign == -1) {
        out << "-" << whole_part << '.' << fractional_part;
    }

    return out;
}


LongNumber operator + (LongNumber& a, LongNumber& b) {

    LongNumber c;
    c.MyVector.clear();

    int q = 0;
    int w = 0;
    int r = 0;
    int k = 1;


    int flag = 0;

    if (a.sign == 1 && b.sign == -1) {
        flag = 1;
        std::swap(a, b);
    }
    //std::cout << a.sign << b.sign << std::endl;

    LongNumber d;
    LongNumber m;
 

    d = a;
    m = b;

    d.sign = 1;
    m.sign = 1;

    

    if (a.sign == b.sign) {
        if (a.MyVector.size() == b.MyVector.size()) {
            for (int i = 0; i < a.MyVector.size(); i++) {
                //std::cout << "(((( " << a.MyVector[i] << std::endl;

                if ((a.MyVector[i] + b.MyVector[i] + q) > 2) {
                    k = 1;
                    int transfer = (a.MyVector[i] + b.MyVector[i] + q) % 2;
                    c.MyVector.push_back(transfer);
                }
                else if ((a.MyVector[i] + b.MyVector[i] + q) == 2) {
                    k = 1;
                    int transfer = (a.MyVector[i] + b.MyVector[i] + q) % 2;
                    c.MyVector.push_back(transfer);
                }
                else if ((a.MyVector[i] + b.MyVector[i] + q) < 2) {
                    k = 0;
                    int transfer = (a.MyVector[i] + b.MyVector[i] + q) % 2;
                    c.MyVector.push_back(transfer);
                }

                q = k;
                k = 0;
            }
            if (q == 1) {
                c.MyVector.push_back(1);
            }

            /* std::cout << std::endl;
            for (int i = 0; i < c.MyVector.size(); i++) {
                std::cout << c.MyVector[i];
            }*/
        }
        else if (a.MyVector.size() != b.MyVector.size()) {

            int difference_in_a = a.MyVector.size() - 200;
            int difference_in_b = b.MyVector.size() - 200;




            if (a.MyVector.size() > b.MyVector.size()) {
                int result_to_push = (difference_in_a - difference_in_b);

                // ?? 
                auto iter1 = b.MyVector.cbegin(); // константный итератор указывает на первый элемент

                // ??

                b.MyVector.insert(b.MyVector.end(), result_to_push, 0);

                for (int i = 0; i < a.MyVector.size(); i++) {

                    if ((a.MyVector[i] + b.MyVector[i] + q) >= 2) {
                        k = 1;
                        int transfer = (a.MyVector[i] + b.MyVector[i] + q) % 2;
                        c.MyVector.push_back(transfer);
                    }
                    else if ((a.MyVector[i] + b.MyVector[i] + q) < 2) {
                        k = 0;
                        int transfer = (a.MyVector[i] + b.MyVector[i] + q) % 2;
                        c.MyVector.push_back(transfer);
                    }

                    q = k;
                    k = 0;
                }
                if (q == 1) {
                    c.MyVector.push_back(1);
                }
            }
            if (a.MyVector.size() < b.MyVector.size()) {
                int result_to_push = (difference_in_b - difference_in_a);

                // ?? 
                auto iter1 = a.MyVector.cbegin(); // константный итератор указывает на первый элемент

                // ??

                a.MyVector.insert(a.MyVector.end(), result_to_push, 0);

                for (int i = 0; i < b.MyVector.size(); i++) {

                    if ((a.MyVector[i] + b.MyVector[i] + q) >= 2) {
                        k = 1;
                        int transfer = (a.MyVector[i] + b.MyVector[i] + q) % 2;
                        c.MyVector.push_back(transfer);
                    }
                    else if ((a.MyVector[i] + b.MyVector[i] + q) < 2) {
                        k = 0;
                        int transfer = (a.MyVector[i] + b.MyVector[i] + q) % 2;
                        c.MyVector.push_back(transfer);
                    }

                    q = k;
                    k = 0;
                }
                if (q == 1) {
                    c.MyVector.push_back(1);
                }
            }

        }
    }
    else if (a.sign == -1 && b.sign == 1) {


        if (d < m) {

            if (a.MyVector.size() != b.MyVector.size()) {

                int difference_in_a = a.MyVector.size() - 200;
                int difference_in_b = b.MyVector.size() - 200;



                int result_to_push = (difference_in_b - difference_in_a);

                // ?? 
                auto iter1 = a.MyVector.cbegin(); // константный итератор указывает на первый элемент

                // ??

                a.MyVector.insert(a.MyVector.end(), result_to_push, 0);
            }

            
            for (int i = 0; i < a.MyVector.size(); i++) {

                if (((b.MyVector[i] - a.MyVector[i]) - r) >= 0) {
                    int transfer = (b.MyVector[i] - a.MyVector[i] - r) % 2;
                    c.MyVector.push_back(transfer);
                    w = 0;

                }
                else {
                    q = 2;
                    int transfer = (b.MyVector[i] - a.MyVector[i] + q - r) % 2;
                    c.MyVector.push_back(transfer);
                    w = 1;
                }
                r = w;
                w = 0;
            }
        }

        else {
            if (a.MyVector.size() != b.MyVector.size()) {

                int difference_in_a = a.MyVector.size() - 200;
                int difference_in_b = b.MyVector.size() - 200;



                int result_to_push = (difference_in_a - difference_in_b);


                b.MyVector.insert(b.MyVector.end(), result_to_push, 0);
            }


            for (int i = 0; i < a.MyVector.size(); i++) {

                if (((a.MyVector[i] - b.MyVector[i]) - r) >= 0) {
                    int transfer = (a.MyVector[i] - b.MyVector[i] - r) % 2;
                    c.MyVector.push_back(transfer);
                    w = 0;

                }
                else {
                    q = 2;
                    int transfer = (a.MyVector[i] - b.MyVector[i] + q - r) % 2;
                    c.MyVector.push_back(transfer);
                    w = 1;
                }
                r = w;
                w = 0;
            }
        }
    }

    while (c.MyVector.size() > 201 && c.MyVector.back() == 0) {
        c.MyVector.pop_back();
    }

    
    if (flag == 1) {
        std::swap(a, b);
    }

    
    if (a.sign == 1 && b.sign == 1) {
        c.sign = 1;
        // std::cout << c.sign << std::endl;
    }
    else if (a.sign == -1 && b.sign == -1) {
        c.sign = -1;
        // std::cout << c.sign << std::endl;
    }

    else if (a.sign == -1 && b.sign == 1) {
        a.sign = 1;
        if (a < b) {
            c.sign = 1;
        }
        else {
            c.sign = -1;
        }

        a.sign = -1;

    }
    else if (a.sign == 1 && b.sign == -1) {
        b.sign = 1;
        if (a > b) {
            c.sign = 1;
        }
        else {
            c.sign = -1;
        }

        b.sign = -1;

    }
    if (c.MyVector.size() == 201 && c.MyVector.back() == 0) {
        c.sign = 1;
    }

    return c;
}


LongNumber operator - (LongNumber& a, LongNumber& b) {
    b.sign *= -1;
    
    LongNumber c;

    c = a + b;
    b.sign *= -1;

    return c;

}





LongNumber operator * (LongNumber& a, LongNumber& b) {

    LongNumber c;
    c.MyVector.clear();

    std::unordered_map <int, int> Polynom;
    int max_number = 0;

    //std::cout << a.MyVector.size() << std::endl;
    //std::cout << b.MyVector.size() << std::endl;

    for (int i = 0; i < a.MyVector.size(); i++) {
        for (int j = 0; j < b.MyVector.size(); j++) {

            Polynom[i + j - 400] += a.MyVector[i] * b.MyVector[j];
            max_number = std::max(max_number, i + j - 400);

        }
    }

    //std::cout << "####    " << max_number << std::endl;
    

    for (int i = -400; i <= max_number; i++) {

        Polynom[i + 1] += Polynom[i] / 2;
        Polynom[i] %= 2;

    }

    for (int i = -200; i <= max_number; i++) {
        c.MyVector.push_back(Polynom[i]);
    }


    while (c.MyVector.size() > 201 && c.MyVector.back() == 0) {
        c.MyVector.pop_back();
    }


    for (int i = 0; i < c.MyVector.size(); i++) {
        std::cout << c.MyVector[i];
    }


    if (a.sign == b.sign) {
        c.sign = 1;
    }
    else {
        c.sign = -1;
    }
    return c;

}

LongNumber operator / (LongNumber& a, LongNumber& b) {

    LongNumber c;
    c.MyVector.pop_back();

    LongNumber d;
    d.MyVector.clear();

    LongNumber e;
    e = b;

    for (int i = 0; i < 200; i++) {
        e.MyVector.insert(e.MyVector.begin(), 0); // передвигаем позицию точки
    }
    
    for (int i = a.MyVector.size() - 1; i >= -200; i--) {
        if (i >= 0) {
            c.MyVector.insert(c.MyVector.begin() + 200, a.MyVector[i]); // снос числа на первое место целой части
        }
        else {
            c.MyVector.insert(c.MyVector.begin() + 200, 0);
        }
        
        if (c > e || c == e) {
            c = c - e;
            d.MyVector.push_back(1);
        }
        else {
            d.MyVector.push_back(0);
        }
    }

    

    reverse(d.MyVector.begin(), d.MyVector.end());
    while (d.MyVector.size() > 201 && d.MyVector.back() == 0) {
        d.MyVector.pop_back();
    }

    if (a.sign == b.sign) {
        d.sign = 1;
        return d;
    }
    else {

        d.sign = -1;
        return d;
    }
    
}