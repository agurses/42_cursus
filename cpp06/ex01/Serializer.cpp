#include "Serializer.hpp"

Serializer::Serializer()
{

}

Serializer::Serializer(const Serializer &str)
{
    (void)str;
}

Serializer &Serializer::operator=(const Serializer &str)
{
    (void)str;
    return *this;
}

Serializer::~Serializer()
{

}

uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t str)
{
    return reinterpret_cast<Data*>(str);
}
