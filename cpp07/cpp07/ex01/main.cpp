#include "iter.hpp"

template <typename T>
void printValue(const T& value)
{
    std::cout << value << " ";
}

void increment(int& value)
{
    value++;
}

int main(void)
{
    int numbers[] = {1, 2, 3};
    const int constants[] = {4, 5, 6};
    std::string words[] = {"one", "two", "three"};

    std::cout << "numbers: ";
    iter(numbers, 3, printValue<int>);
    std::cout << std::endl;

    iter(numbers, 3, increment);
    std::cout << "incremented: ";
    iter(numbers, 3, printValue<int>);
    std::cout << std::endl;

    std::cout << "const numbers: ";
    iter(constants, 3, printValue<int>);
    std::cout << std::endl;

    std::cout << "words: ";
    iter(words, 3, printValue<std::string>);
    std::cout << std::endl;


    char str[] = {'1', '2', '3'};
    iter(str, 3, printValue<char>);

    return (numbers[0] == 2 && numbers[1] == 3 && numbers[2] == 4) ? 0 : 1;
}
