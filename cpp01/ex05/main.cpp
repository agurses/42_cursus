#include "Harl.hpp"

int main(int ac, char **av)
{
	Harl x;
	if (ac != 2)
	{
		std::cerr << "Wrong Arguman Number" << std::endl;
		return (1);
	}
	if (std::string(av[1]) != "debug" &&
		std::string(av[1]) != "info" &&
		std::string(av[1]) != "warning" &&
		std::string(av[1]) != "error")
	{
		std::cerr << "Wrong Input" << std::endl;
		return (1);
	}
	x.complain(av[1]);
}
