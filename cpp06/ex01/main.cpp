#include "Serializer.hpp"

int main()
{
    Data d;
    d.name = "cem";
    //----------------//
    d.self = &d;
    //----------------//

    std::cout << "Main adress: " << d.self << std::endl;
    uintptr_t str = Serializer::serialize(&d);
    std::cout << "Serialized address:: " << str << std::endl;

    Data *ptr = Serializer::deserialize(str);
    std::cout << "Deserialized name: " << ptr->name << std::endl;
    std::cout << "Deserialized address:: " << ptr->self << std::endl;

    if (ptr == &d)
        std::cout << "Correct address! " << std::endl;
    else
        std::cerr << "Wrong address!" << std::endl;
    
    return 0;
}