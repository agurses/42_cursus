#include "Span.hpp"

Span::Span(unsigned int N)
{
	this->N = N;
}

Span::Span(const Span &number) : N(number.N), _numbers(number._numbers)
{

}

Span &Span::operator=(const Span &number)
{
    if (this != &number)
    {
        N = number.N;
        _numbers = number._numbers;
    }
    return *this;
}

Span::~Span()
{

}

void Span::addNumber(int i)
{
    if (_numbers.size() >= N)
        throw std::out_of_range("Span is full");

    _numbers.push_back(i);
}

int Span::shortestSpan()
{
    if (_numbers.size() < 2)
        throw std::out_of_range("Not enough numbers");

	std::sort(_numbers.begin(), _numbers.end());

	int shortest = _numbers[1] - _numbers[0];

	for (std::vector<int>::size_type i = 1;
		i + 1 < _numbers.size();
		++i)
	{
		int current = _numbers[i + 1] - _numbers[i];

		if (current < shortest)
			shortest = current;
	}
	
	return shortest;
}

int Span::longestSpan()
{
    if (_numbers.size() < 2)
        throw std::out_of_range("Not enough numbers");

	int smallestElement = *std::min_element(_numbers.begin(), _numbers.end());
	int biggestElement = *std::max_element(_numbers.begin(), _numbers.end());

	int result = biggestElement - smallestElement;

	return result;
}
