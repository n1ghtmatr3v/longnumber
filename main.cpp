

#include "decimals.hpp"
#include "LongNumber.hpp"



int main(void) {
    setlocale(LC_ALL, "RU");


    


    SetPrecision(200);
    

    LongNumber a;
    LongNumber b;
    std::cin >> a >> b;

    LongNumber c = a / b;
    std::cout << c << std::endl;



    return 0;
}






