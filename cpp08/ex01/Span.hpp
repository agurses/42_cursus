#ifndef SPAN_HPP
# define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <exception>
#include <iostream>

class Span
{
	private:
		unsigned int N;
		std::vector<int> _numbers;
		
	public:
		Span(unsigned int N);
		Span(const Span &number);
		Span &operator=(const Span &number);
		~Span();

		void addNumber(int i);
		int shortestSpan();
		int longestSpan();

		template<typename Iterator>
		void addNumber(Iterator begin, Iterator end)
		{
			Iterator _add = begin;
		
			while (_add != end)
			{
				if (_numbers.size() >= N)
					throw std::out_of_range("Span is full");

				_numbers.push_back(*_add);
				++_add;
			}

		}
};


#endif