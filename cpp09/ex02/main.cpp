#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe sorter;

    try
    {
        std::clock_t start = std::clock();
    	sorter.parseInput(ac, av, true);
        std::clock_t vectorTime = std::clock() - start;

    	std::cout << "Before: ";
    	sorter.printVector();
    
        start = std::clock();
    	sorter.sortVector();
        vectorTime += std::clock() - start;

        start = std::clock();
        sorter.parseInput(ac, av, false);
        sorter.sortDeque();
        std::clock_t dequeTime = std::clock() - start;

    	std::cout << "After: ";
    	sorter.printVector();

        double vectorUs = 1000000.0 * vectorTime / CLOCKS_PER_SEC;
        double dequeUs = 1000000.0 * dequeTime / CLOCKS_PER_SEC;

        std::cout << "Time to process a range of " << ac - 1
                  << " elements with std::vector : " << vectorUs << " us\n";
        std::cout << "Time to process a range of " << ac - 1
                  << " elements with std::deque : " << dequeUs << " us\n";
    }
    catch(const std::exception &)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    return 0;
}