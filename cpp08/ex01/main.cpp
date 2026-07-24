#include "Span.hpp"

int main(void)
{
	int failures = 0;

	std::cout << "Subject example" << std::endl;
	try
	{
		Span span(5);
		span.addNumber(6);
		span.addNumber(3);
		span.addNumber(17);
		span.addNumber(9);
		span.addNumber(11);

		if (span.shortestSpan() == 2 && span.longestSpan() == 14)
			std::cout << "  passed" << std::endl;
		else
		{
			std::cout << "  failed" << std::endl;
			++failures;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "  unexpected exception: " << e.what() << std::endl;
		++failures;
	}

	std::cout << "Capacity exception" << std::endl;
	try
	{
		Span span(2);
		span.addNumber(1);
		span.addNumber(2);
		span.addNumber(3);
		std::cout << "  failed" << std::endl;
		++failures;
	}
	catch (const std::exception &e)
	{
		std::cout << "  passed: " << e.what() << std::endl;
	}

	std::cout << "Not enough numbers" << std::endl;
	Span empty(5);
	try
	{
		empty.shortestSpan();
		std::cout << "  empty shortestSpan failed" << std::endl;
		++failures;
	}
	catch (const std::exception &e)
	{
		std::cout << "  empty shortestSpan passed: " << e.what() << std::endl;
	}

	try
	{
		empty.longestSpan();
		std::cout << "  empty longestSpan failed" << std::endl;
		++failures;
	}
	catch (const std::exception &e)
	{
		std::cout << "  empty longestSpan passed: " << e.what() << std::endl;
	}

	Span one(5);
	one.addNumber(10);
	try
	{
		one.shortestSpan();
		std::cout << "  one-number shortestSpan failed" << std::endl;
		++failures;
	}
	catch (const std::exception &e)
	{
		std::cout << "  one-number shortestSpan passed: " << e.what() << std::endl;
	}

	try
	{
		one.longestSpan();
		std::cout << "  one-number longestSpan failed" << std::endl;
		++failures;
	}
	catch (const std::exception &e)
	{
		std::cout << "  one-number longestSpan passed: " << e.what() << std::endl;
	}

	std::cout << "Duplicate and negative values" << std::endl;
	try
	{
		Span span(3);
		span.addNumber(5);
		span.addNumber(5);
		span.addNumber(-10);

		if (span.shortestSpan() == 0 && span.longestSpan() == 15)
			std::cout << "  passed" << std::endl;
		else
		{
			std::cout << "  failed" << std::endl;
			++failures;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "  unexpected exception: " << e.what() << std::endl;
		++failures;
	}

	std::cout << "Iterator range and 10000 numbers" << std::endl;
	try
	{
		std::vector<int> values;
		for (int i = 0; i < 10000; ++i)
			values.push_back(i);

		Span span(10000);
		span.addNumber(values.begin(), values.end());

		if (span.shortestSpan() == 1 && span.longestSpan() == 9999)
			std::cout << "  passed" << std::endl;
		else
		{
			std::cout << "  failed" << std::endl;
			++failures;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "  unexpected exception: " << e.what() << std::endl;
		++failures;
	}

	std::cout << "Copy constructor and assignment" << std::endl;
	try
	{
		Span original(3);
		original.addNumber(1);
		original.addNumber(4);

		Span copy(original);
		Span assigned(1);
		assigned = original;

		if (copy.shortestSpan() == 3 && copy.longestSpan() == 3
			&& assigned.shortestSpan() == 3 && assigned.longestSpan() == 3)
			std::cout << "  passed" << std::endl;
		else
		{
			std::cout << "  failed" << std::endl;
			++failures;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "  unexpected exception: " << e.what() << std::endl;
		++failures;
	}

	if (failures == 0)
		std::cout << "All tests passed" << std::endl;
	else
		std::cout << failures << " test(s) failed" << std::endl;

	return failures;
}
