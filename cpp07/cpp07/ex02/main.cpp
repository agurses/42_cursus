#include <exception>
#include <iostream>
#include <string>
#include "Array.hpp"

int main(void)
{
    Array<int> empty;
    if (empty.size() != 0)
        return 1;

    Array<int> numbers(3);
    if (numbers.size() != 3 || numbers[0] != 0 || numbers[1] != 0 || numbers[2] != 0)
        return 1;

    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;

    const Array<int> constNumbers(numbers);
    if (constNumbers[0] != 10)
        return 1;

    Array<int> copied(numbers);
    copied[0] = 99;
    if (numbers[0] == 99)
        return 1;

    Array<int> assigned(1);
    assigned = numbers;
    assigned[1] = 88;
    if (assigned.size() != numbers.size() || numbers[1] == 88)
        return 1;

    bool caught = false;
    try
    {
        numbers[3] = 0;
    }
    catch (const std::exception& e)
    {
        (void)e;
        caught = true;
    }
    if (!caught)
        return 1;

    caught = false;
    try
    {
        numbers[static_cast<unsigned int>(-1)] = 0;
    }
    catch (const std::exception& e)
    {
        (void)e;
        caught = true;
    }
    if (!caught)
        return 1;

    Array<std::string> words(2);
    words[0] = "one";
    words[1] = "two";
    if (words[0] != "one" || words[1] != "two")
        return 1;

    std::cout << "All Array tests passed" << std::endl;
    return 0;
}
