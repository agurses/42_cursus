#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(const RPN &other)
{
	numbers = other.numbers;
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		numbers = other.numbers;
	}
	return *this;
}

RPN::~RPN()
{

}

int RPN::calculate(const std::string &expression)
{
	
	std::stringstream tokens(expression);
	std::string token;

	while (tokens >> token)
	{
		if (token.length() == 1 && (token[0] >= '0' && token[0] <= '9'))
			numbers.push(token[0] - '0');
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (numbers.size() < 2)
				throw std::runtime_error("Invalid expression");
			
			int right = numbers.top();
			numbers.pop();
			int left = numbers.top();
			numbers.pop();

			if (token == "+")
			{
				if ((right > 0 && left > INT_MAX - right)
					|| (right < 0 && left < INT_MIN - right))
					throw std::runtime_error("Integer overflow");
			
				numbers.push(left + right);
			}
			else if (token == "-")
			{
				if ((right > 0 && left < INT_MIN + right)
					|| (right < 0 && left > INT_MAX + right))
					throw std::runtime_error("Integer overflow");
			
				numbers.push(left - right);
			}
			else if (token == "*")
			{
				if ((left > 0 && right > 0 && left > INT_MAX / right)
					|| (left > 0 && right < 0 && right < INT_MIN / left)
					|| (left < 0 && right > 0 && left < INT_MIN / right)
					|| (left < 0 && right < 0 && left < INT_MAX / right))
					throw std::runtime_error("Integer overflow");
			
				numbers.push(left * right);
			}
			else if (token == "/")
			{
				if (right == 0)
					throw std::runtime_error("Division by zero");
			
				if (left == INT_MIN && right == -1)
					throw std::runtime_error("Integer overflow");
			
				numbers.push(left / right);
			}
		}
		else
			throw std::runtime_error("Invalid token");
	}

	if (numbers.size() != 1)
		throw std::runtime_error("Invalid expression");

	return numbers.top();
}
