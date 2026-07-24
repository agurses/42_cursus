#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

template <typename container>
typename container::iterator easyfind(container &cont, int i)
{
    typename container::iterator result;

    result = std::find(cont.begin(), cont.end(), i);

    if (result != cont.end())
        return result;

    return cont.end();
}

#endif