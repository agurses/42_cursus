#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>
#include <string>
#include <cstddef>

template <typename Array, typename Func>
void iter(Array* array, const std::size_t a, Func func)
{
    std::size_t i = 0;

    while (i < a)
    {
        func(array[i]);
        i++;
    }
}

#endif