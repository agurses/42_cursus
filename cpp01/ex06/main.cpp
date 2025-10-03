#include "Harl.hpp"

int main(int ac, char **av)
{
	Harl x;

	if (ac != 2)
	{
		std::cerr << "Wrong Number Argument" << std::endl;
		return (1);
	}

	int lvl = 4;
	if (std::string(av[1]) == "DEBUG")
		lvl = 0;
	else if (std::string(av[1]) == "INFO")
		lvl = 1;
	else if (std::string(av[1]) == "WARNING")
		lvl = 2;
	else if (std::string(av[1]) == "ERROR")
		lvl = 3;

	switch (lvl)
	{
		case 0:
			x.complain(0);
			break ;
		case 1:
			x.complain(1);
			break ;
		case 2:
			x.complain(2);
			break ;
		case 3:
			x.complain(3);
			break ;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			break ;
	}
}
