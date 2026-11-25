#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Wrong number of Argüman." << std::endl;
		return 1;
	}

	RPN object;
	int result;

	try
	{
		result = object.calculate(av[1]);
		std::cout << result << std::endl;
	}
	catch (const std::exception &)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	return 0;
}