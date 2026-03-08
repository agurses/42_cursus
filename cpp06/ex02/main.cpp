#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main()
{
    std::srand(std::time(0));

//        Base *str = NULL;
//    
//        std::cout << str << std::endl;
//        std::cout << "Pointer ile tip: ";
//        identify(str);
//    
//        std::cout << "Referans ile tip: ";
//        identify(*str);
//
//-----------------------------------------//

    Base *tr = generate();

    std::cout << "Pointer ile tip: ";
    identify(tr);

    std::cout << "Referans ile tip: ";
    identify(*tr);
    
}
