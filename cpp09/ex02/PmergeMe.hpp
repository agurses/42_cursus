#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <climits>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <ctime>

class PmergeMe
{
    private:
        std::vector<int> vectorData;
        std::deque<int> dequeData;
        void sortVectorPairs(std::vector<std::pair<int, int> > &pairs);
        void sortDequePairs(std::deque<std::pair<int, int> > &pairs);
    public:
    	PmergeMe();
    	PmergeMe(const PmergeMe &other);
    	PmergeMe &operator=(const PmergeMe &other);
    	~PmergeMe();

        void parseInput(int ac, char **av, bool useVector);
        void sortVector();
        void sortDeque();

        void printVector() const;
};

#endif