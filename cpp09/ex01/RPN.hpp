#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <climits>
#include <list>

class RPN
{
    private:
        std::stack<int, std::list<int> > numbers;
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();

        int calculate(const std::string &expression);
};

#endif