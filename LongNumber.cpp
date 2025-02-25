
#include "decimals.hpp"
#include "LongNumber.hpp"














LongNumber LongNumber::abs() const {

    LongNumber result = *this;
    result.sign = 1;
    return result;

}


LongNumber::LongNumber(const LongNumber& other) {
    sign = other.sign;
    MyVector = other.MyVector;
}

LongNumber::~LongNumber () {
    MyVector.clear();
}

LongNumber::LongNumber() {
    sign = 1;
    MyVector.assign((super_new_binary_precision + 1), 0);
}

LongNumber& LongNumber:: operator = (const LongNumber& other) {
        
    if (this != &other) {
        sign = other.sign;
        MyVector = other.MyVector;
    }
    return *this;
}

LongNumber::LongNumber(int value) {

    std::string new_str = "";

    new_str = std::to_string(value);

    if (new_str[0] == '-') {
        sign = -1;
        new_str = new_str.substr(1, new_str.size());
    }
    else {
        sign = 1;
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

    //std::cout << "@@@  " << whole_part << '.' << fractional_part << std::endl; 



    whole_part = decimalToBinary(whole_part);
    fractional_part = decimal_2(fractional_part, super_new_binary_precision);






    while (fractional_part.size() < super_new_binary_precision) {
        fractional_part.push_back('0');
    }



    reverse(whole_part.begin(), whole_part.end());
    reverse(fractional_part.begin(), fractional_part.end());

    //std::cout << "@@@  " << whole_part << '.' << fractional_part << std::endl; 


    MyVector.clear();

    //std::cout << "@@@  " << whole_part << '.' << fractional_part << std::endl; 

    for (char x : fractional_part) { // перебрать все символы в fractional_part
        MyVector.push_back(x - '0');
    }
    for (char x : whole_part) { // перебрать все символы в whole_part
        MyVector.push_back(x - '0');
    }

 
}






bool LongNumber::operator == (const LongNumber& other) {
    if (sign != other.sign) {
        return false;
    }
    else {

        if (MyVector.size() > other.MyVector.size() || MyVector.size() < other.MyVector.size()) {
            return false;
        }
        else {
            int flag = 0;
            for (int i = 0; i < MyVector.size(); i++) {
                if (MyVector[i] == other.MyVector[i]) {
                    flag = 1;
                }
                else {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

bool LongNumber::operator != (const LongNumber& other) {
    return !(*this == other);
}



bool LongNumber::operator > (const LongNumber& other) {
    if (sign != other.sign) {
        return sign > other.sign;
    }

    if (sign == 1) {
        if (MyVector.size() > other.MyVector.size()) {
            return true;
        }
        if (MyVector.size() < other.MyVector.size()) {
            return false;
        }
        for (int i = MyVector.size() - 1; i >= 0; i--) {
            if (MyVector[i] > other.MyVector[i]) {
                return true;
            }
            else if (MyVector[i] < other.MyVector[i]) {
                return false;
            }
        }
        return false;
    }

    if (sign == -1) {
        if (MyVector.size() > other.MyVector.size()) {
            return false;
        }
        if (MyVector.size() < other.MyVector.size()) {
            return true;
        }
        for (int i = MyVector.size() - 1; i >= 0; i--) {
            if (MyVector[i] > other.MyVector[i]) {
                return false;
            }
            else if (MyVector[i] < other.MyVector[i]) {
                return true;
            }
        }
        return false;
    }
}



bool LongNumber::operator < (const LongNumber& other) {
    return !(*this > other) && (*this != other); 
}


std::istream& operator >> (std::istream& in, LongNumber& other) {


    std::string new_str = "";
    in >> new_str;
    if (new_str[0] == '-') {
        other.sign = -1; 
        new_str = new_str.substr(1, new_str.size());
    }
    else {
        other.sign = 1;
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
    fractional_part = decimal_2(fractional_part, super_new_binary_precision);




    while (fractional_part.size() < super_new_binary_precision) {
        fractional_part.push_back('0');
    }

    //std::cout << "!!!!!  " << whole_part << '.' << fractional_part << std::endl;


    if (fractional_part != "0") {

        std::string string_for_new_str = "";

        string_for_new_str += whole_part;
        string_for_new_str += '.';
        string_for_new_str += fractional_part; 

        //std::cout << "****   " << string_for_new_str << std::endl;

        int pozition = -1;

        for (int i = 0; i < string_for_new_str.size(); i++) {
            if (pozition == '.') {
                pozition = i;
                break;
            }
        }

        fractional_part = fractional_part.substr(pozition + 1, binary_precision + 1); 

        //std::cout << "!@#  " << fractional_part << std::endl; 

        
        int last_number_in_fractional = (fractional_part[fractional_part.size() - 1] - '0');

        if (binary_precision == 0) {

            //std::cout << "НЕ ТУДА" << std::endl; 

            int s = 0;
            int r = 1;

            if (last_number_in_fractional == 1) {
                if (whole_part[whole_part.size() - 1] != 1) {
                    whole_part[whole_part.size() - 1] = (((whole_part[whole_part.size() - 1] - '0') + 1) + '0');
                }
                else {
                    whole_part[whole_part.size() - 1] = (((whole_part[whole_part.size() - 1] - '0') + 1) + '0');
                    s = 1;
                    for (int i = whole_part.size() - 2; i >= 0; i--) {
                        if (((whole_part[i] - '0') + r) > 1) {
                            s = 1;
                            whole_part[i] = '0';
                        }
                        else if (((whole_part[i] - '0') + r) == 1) {
                            s = 1;
                            whole_part[i] = '1';
                        }
                        else {
                            s = 0;
                            whole_part[whole_part.size() - 1] = (((whole_part[whole_part.size() - 1] - '0') + r) + '0');
                        }
                        r = s;
                        s = 0;
                    }
                    if (r == 1) {
                        whole_part.insert(whole_part.begin(), 1, '0');
                        whole_part[0] = '1';
                    }
                }
            }
        }

        else {
            int pred_last_number_in_fractional = (fractional_part[fractional_part.size() - 2] - '0');
            //std::cout << "%%%  " << last_number_in_fractional << std::endl;
            //std::cout << "%%_  " << pred_last_number_in_fractional << std::endl;

            int k = 0;
            int q = 1;

            int m = 0;
            int d = 1;



            if (last_number_in_fractional == 1) {
                if (pred_last_number_in_fractional != 1) {
                    fractional_part[fractional_part.size() - 2] = (((fractional_part[fractional_part.size() - 2] - '0') + 1) + '0');
                }
                else { // pred_last_.. == 1
                    //std::cout << "Зашел куда надо! " << std::endl;  
                    k = 1;
                    for (int i = fractional_part.size() - 2; i >= 0; i--) {

                        if (((fractional_part[i] - '0') + q) > 1) {
                            k = 1;
                            fractional_part[i] = '0';
                        }
                        else if (((fractional_part[i] - '0') + q) == 1) {
                            k = 0;
                            fractional_part[i] = '1';
                        }
                        else {
                            k = 0;
                            fractional_part[i] = (((fractional_part[i] - '0') + q) + '0');
                        }
                        q = k;
                        k = 0;
                    }

                    if (q == 1) {
                        if (whole_part[whole_part.size() - 1] != '1') {
                            whole_part[whole_part.size() - 1] = (((whole_part[whole_part.size() - 1] - '0') + q) + '0');
                        }
                        else { // whole_part_last == 1 { ... }
                            whole_part[whole_part.size() - 1] = '0';
                            m = 1;
                            whole_part.insert(whole_part.begin(), 1, '0');
                            for (int i = whole_part.size() - 2; i >= 0; i--) {
                                if (((whole_part[i] - '0') + d) > 1) {
                                    m = 1;
                                    whole_part[i] = '0';
                                }
                                else if (((whole_part[i] - '0') + d) == 1) {
                                    m = 1;
                                    whole_part[i] = '1';
                                }
                                else {
                                    m = 0;
                                    whole_part[i] = (((whole_part[i] - '0') + d) + '0');
                                }
                                d = m;
                                m = 0;
                            }
                            if (whole_part[0] == '0') {
                                whole_part.erase(whole_part.begin());
                            }
                        }
                    }
                }
            }
        }

        //std::cout << "((((   " << whole_part << '.' << fractional_part << std::endl;

        fractional_part = fractional_part.substr(0, fractional_part.size() - 1);

        if (fractional_part.size() < super_new_binary_precision) {

            int difference = super_new_binary_precision - fractional_part.size();

            for (int i = 0; i < difference ; i++) {
                fractional_part.push_back('0');
            }

        }


        //std::cout << "#####   " << whole_part << '.' << fractional_part << std::endl;


    }

    

    reverse(whole_part.begin(), whole_part.end());
    reverse(fractional_part.begin(), fractional_part.end());

    //std::cout << "&&  " << fractional_part.size() << std::endl;
    //std::cout << "&&  " << whole_part.size() << std::endl;

    other.MyVector.clear();  

    for (char x : fractional_part) { // перебрать все символы в fractional_part
        other.MyVector.push_back(x - '0'); 
    }
    for (char x : whole_part) { // перебрать все символы в whole_part
        other.MyVector.push_back(x - '0'); 
    }

    //std::cout << whole_part << "." << fractional_part << std::endl;

    //std::cout << a.MyVector.size() << std::endl; 

    return in;

}


LongNumber LongNumber:: operator / (const LongNumber& other) {

    LongNumber c;
    c.MyVector.pop_back();

    LongNumber d;
    d.MyVector.clear();


    LongNumber e;
    e = other;

    int flag_1 = 0;

    for (int i : MyVector) {
        if (i != 0) {
            flag_1 = 1;
            break;
        }
    }
    for (int i : other.MyVector) {
        if (i != 0) {
            flag_division = 1;
            break;
        }
    }
    if (flag_division == -1) {
        flag_division = 0;
    }


    if (flag_1 == 0) {
        d.MyVector.assign(super_new_binary_precision + 1, 0);
        d.sign = 1;
        return d;
    }


    for (int i = 0; i < super_new_binary_precision; i++) {
        e.MyVector.insert(e.MyVector.begin(), 0); // передвигаем позицию точки
    }

    for (int i = MyVector.size() - 1; i >= -super_new_binary_precision; i--) {
        if (i >= 0) {
            c.MyVector.insert(c.MyVector.begin() + super_new_binary_precision, MyVector[i]); // снос числа на первое место целой части
        }
        else {
            c.MyVector.insert(c.MyVector.begin() + super_new_binary_precision, 0);
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
    while (d.MyVector.size() > (super_new_binary_precision + 1) && d.MyVector.back() == 0) {
        d.MyVector.pop_back();
    }



    if (sign == other.sign) {
        d.sign = 1;
        return d;
    }
    else {

        d.sign = -1;
        return d;
    }
}






std::ostream& operator << (std::ostream& out, LongNumber& other) {

    std::string new_str = "";
    std::string whole_part = ""; // целая часть
    std::string fractional_part = ""; // дробная часть

    for (int i = 0; i < other.MyVector.size(); i++) {
        if (i < super_new_binary_precision) {
            fractional_part.push_back(other.MyVector[i] + '0');

        }
        else {
            whole_part.push_back(other.MyVector[i] + '0');
        }
        //std::cout << a.MyVector[i];
    }

    //std::cout << fractional_part.size() << std::endl; 


    reverse(fractional_part.begin(), fractional_part.end());
    reverse(whole_part.begin(), whole_part.end());

    //std::cout << whole_part << '.' << fractional_part << std::endl;


    whole_part = BinaryToDivision_whole(whole_part);
    fractional_part = BinaryToDivision_fractional(fractional_part);

    

      

    if (flag_division == 0) { 
        whole_part = "";
        fractional_part = "";
    }

    if (other.sign == 1) {
        
        if (binary_precision == 0) {
            out << whole_part;
        }
        else {
            if (flag_division == 0) {
                out << whole_part << fractional_part;
            }
            else {
                out << whole_part << '.' << fractional_part; 
            }
            
        }
        
    }
    else if (other.sign == -1) {
       
        if (binary_precision == 0) {
            out << "-" << whole_part;
        }
        else {
            if (flag_division == 0) {
                out << whole_part << fractional_part;
            }
            else {
                out << "-" << whole_part << '.' << fractional_part; 
            }
        }
        
    } 

    //std::cout << a << std::endl;
    
    

    return out;
}




LongNumber LongNumber:: operator + (LongNumber& other) {

    LongNumber c;
    c.MyVector.clear();

    int q = 0;
    int w = 0;
    int r = 0;
    int k = 1;


    int flag = 0;

    if (sign == 1 && other.sign == -1) {
        flag = 1;
        std::swap(*this, other);
    }
    //std::cout << a.sign << b.sign << std::endl;

    LongNumber d;
    LongNumber m;
 

    d = *this;
    m = other;

    d.sign = 1;
    m.sign = 1;

    

    if (sign == other.sign) {
        if (MyVector.size() == other.MyVector.size()) {
            for (int i = 0; i < MyVector.size(); i++) {
                //std::cout << "(((( " << a.MyVector[i] << std::endl;

                if ((MyVector[i] + other.MyVector[i] + q) > 2) {
                    k = 1;
                    int transfer = (MyVector[i] + other.MyVector[i] + q) % 2;
                    c.MyVector.push_back(transfer);
                }
                else if ((MyVector[i] + other.MyVector[i] + q) == 2) {
                    k = 1;
                    int transfer = (MyVector[i] + other.MyVector[i] + q) % 2;
                    c.MyVector.push_back(transfer);
                }
                else if ((MyVector[i] + other.MyVector[i] + q) < 2) {
                    k = 0;
                    int transfer = (MyVector[i] + other.MyVector[i] + q) % 2;
                    c.MyVector.push_back(transfer);
                }

                q = k;
                k = 0;
            }
            if (q == 1) {
                c.MyVector.push_back(1);
            }

  
        }
        else if (MyVector.size() != other.MyVector.size()) {

            int difference_in_a = MyVector.size() - super_new_binary_precision;
            int difference_in_b = other.MyVector.size() - super_new_binary_precision;




            if (MyVector.size() > other.MyVector.size()) {
                int result_to_push = (difference_in_a - difference_in_b);

                // ?? 
                auto iter1 = other.MyVector.cbegin(); // константный итератор указывает на первый элемент

                // ??

                other.MyVector.insert(other.MyVector.end(), result_to_push, 0);

                for (int i = 0; i < MyVector.size(); i++) {

                    if ((MyVector[i] + other.MyVector[i] + q) >= 2) {
                        k = 1;
                        int transfer = (MyVector[i] + other.MyVector[i] + q) % 2;
                        c.MyVector.push_back(transfer);
                    }
                    else if ((MyVector[i] + other.MyVector[i] + q) < 2) {
                        k = 0;
                        int transfer = (MyVector[i] + other.MyVector[i] + q) % 2;
                        c.MyVector.push_back(transfer);
                    }

                    q = k;
                    k = 0;
                }
                if (q == 1) {
                    c.MyVector.push_back(1);
                }
            }
            if (MyVector.size() < other.MyVector.size()) {
                int result_to_push = (difference_in_b - difference_in_a);

                // ?? 
                auto iter1 = MyVector.cbegin(); // константный итератор указывает на первый элемент

                // ??

                MyVector.insert(MyVector.end(), result_to_push, 0);

                for (int i = 0; i < other.MyVector.size(); i++) {

                    if ((MyVector[i] + other.MyVector[i] + q) >= 2) {
                        k = 1;
                        int transfer = (MyVector[i] + other.MyVector[i] + q) % 2;
                        c.MyVector.push_back(transfer);
                    }
                    else if ((MyVector[i] + other.MyVector[i] + q) < 2) {
                        k = 0;
                        int transfer = (MyVector[i] + other.MyVector[i] + q) % 2;
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
    else if (sign == -1 && other.sign == 1) {


        if (d < m) {

            if (MyVector.size() != other.MyVector.size()) {

                int difference_in_a = MyVector.size() - super_new_binary_precision;
                int difference_in_b = other.MyVector.size() - super_new_binary_precision;



                int result_to_push = (difference_in_b - difference_in_a);

                // ?? 
                auto iter1 = MyVector.cbegin(); // константный итератор указывает на первый элемент

                // ??

                MyVector.insert(MyVector.end(), result_to_push, 0);
            }

            
            for (int i = 0; i < MyVector.size(); i++) {

                if (((other.MyVector[i] - MyVector[i]) - r) >= 0) {
                    int transfer = (other.MyVector[i] - MyVector[i] - r) % 2;
                    c.MyVector.push_back(transfer);
                    w = 0;

                }
                else {
                    q = 2;
                    int transfer = (other.MyVector[i] - MyVector[i] + q - r) % 2;
                    c.MyVector.push_back(transfer);
                    w = 1;
                }
                r = w;
                w = 0;
            }
        }

        else {
            if (MyVector.size() != other.MyVector.size()) {

                int difference_in_a = MyVector.size() - super_new_binary_precision;
                int difference_in_b = other.MyVector.size() - super_new_binary_precision;



                int result_to_push = (difference_in_a - difference_in_b);


                other.MyVector.insert(other.MyVector.end(), result_to_push, 0);
            }


            for (int i = 0; i < MyVector.size(); i++) {

                if (((MyVector[i] - other.MyVector[i]) - r) >= 0) {
                    int transfer = (MyVector[i] - other.MyVector[i] - r) % 2;
                    c.MyVector.push_back(transfer);
                    w = 0;

                }
                else {
                    q = 2;
                    int transfer = (MyVector[i] - other.MyVector[i] + q - r) % 2;
                    c.MyVector.push_back(transfer);
                    w = 1;
                }
                r = w;
                w = 0;
            }
        }
    }

    while (c.MyVector.size() > (super_new_binary_precision + 1) && c.MyVector.back() == 0) {
        c.MyVector.pop_back();
    }

    
    if (flag == 1) {
        std::swap(*this, other);
    }

    
    if (sign == 1 && other.sign == 1) {
        c.sign = 1;
        // std::cout << c.sign << std::endl;
    }
    else if (sign == -1 && other.sign == -1) {
        c.sign = -1;
        // std::cout << c.sign << std::endl;
    }

    else if (sign == -1 && other.sign == 1) {
        sign = 1;
        if (*this < other) {
            c.sign = 1;
        }
        else {
            c.sign = -1;
        }

        sign = -1;

    }
    else if (sign == 1 && other.sign == -1) {
        other.sign = 1;
        if (*this > other) {
            c.sign = 1;
        }
        else {
            c.sign = -1;
        }

        other.sign = -1;

    }
    if (c.MyVector.size() == (super_new_binary_precision + 1) && c.MyVector.back() == 0) {
        c.sign = 1;
    }

    return c;
}








LongNumber LongNumber:: operator - (LongNumber& other) {
    other.sign *= -1;
    
    LongNumber c;

    c = *this + other;
    other.sign *= -1;

    return c;

}



LongNumber LongNumber:: operator * (const LongNumber& other) {

    LongNumber c;
    c.MyVector.clear();

    std::unordered_map<int, int> Polynom;
    int max_index = -2 * super_new_binary_precision;


    for (int i = 0; i < MyVector.size(); i++) {
        for (int j = 0; j < other.MyVector.size(); j++) {
            int idx = (i - super_new_binary_precision) + (j - super_new_binary_precision) + super_new_binary_precision;
            Polynom[idx] += MyVector[i] * other.MyVector[j];
            max_index = std::max(max_index, idx);
        }
    }


    for (int i = -2 * super_new_binary_precision; i <= max_index + 1; i++) {
        if (Polynom[i] >= 2) {
            Polynom[i + 1] += Polynom[i] / 2;
            Polynom[i] %= 2;
        }
    }


    for (int i = -super_new_binary_precision; i <= max_index; i++) {
        c.MyVector.push_back(Polynom[i + super_new_binary_precision]);
    }


    while (c.MyVector.size() > (super_new_binary_precision + 1) && c.MyVector.back() == 0) {
        c.MyVector.pop_back();
    }


    if (sign == other.sign) {
        c.sign = 1;
    }
    else {
        c.sign = -1;
    }

    return c;

}







