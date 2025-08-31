#include <iostream>

int main(int ac, char **av)
{
	if (ac >= 2)
	{
		for (int i = 1; av[i]; i++)
		{
			for (int y = 0; av[i][y]; y++)
			{
				std::cout << (char)std::toupper(av[i][y]);
			}
		}
		std::cout << std::endl;
		return (0);
	}
	else
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (1);
	}
}
