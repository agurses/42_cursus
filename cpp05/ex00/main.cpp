#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat a;
	Bureaucrat b("Janet", 3), c(b), d("Antony", 4);
	Bureaucrat e("Merrick", 1);
	Bureaucrat f;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl << std::endl;

	a = d;
	c.incrementGrade();
	std::cout << a << std::endl;
	std::cout << c << std::endl << std::endl;

	try {
	e.incrementGrade();
	f.decrementGrade();
	}
	catch (std::exception &error)
	{
		std::cout << "Error caught: e :" << error.what() << std::endl;

	}
	try {
		f.decrementGrade();
	}
	catch (std::exception &f)
	{
		std::cerr << "Error caught: f :" << f.what() << std::endl;
	}
	std::cout << e << std::endl;
	std::cout << f << std::endl;

	return 0;
}
