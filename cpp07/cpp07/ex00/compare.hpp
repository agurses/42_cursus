#ifndef COMPARE_HPP
# define COMPARE_HPP

template <typename Datatype>
void swap(Datatype& a, Datatype& b)
{
    Datatype temp = a;
    a = b;
    b = temp;
}

template <typename Datatype>
const Datatype& min(const Datatype& a, const Datatype& b)
{
    return (a < b) ? a : b;
}

template <typename Datatype>
const Datatype& max(const Datatype& a, const Datatype& b)
{
    return (a > b) ? a : b;
}

#endif
