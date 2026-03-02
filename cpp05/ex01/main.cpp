#include "Bureaucrat.hpp"
#include "Form.hpp"

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

	Form f1;
	Form f2("Residence Permit", 50, 150);

	std::cout << f1 << std::endl;
	std::cout << f2 << std::endl;

	try
	{
		a.signForm(f1);
	}
	catch (std::exception &er)
	{
		std::cerr << "Error caught: " << er.what() << std::endl;
	}
		try
	{
		a.signForm(f2);
	}
	catch (std::exception &er)
	{
		std::cerr << "Error caught: :" << er.what() << std::endl;
	}
	
	std::cout << std::endl;

	try
	{
		Form f3("Presidential Pardon", 0, 0);

		std::cout << "f3 created." << std::endl;
	}
	catch (std::exception &er)
	{
		std::cerr << "Error caught: " << er.what() << std::endl;
	}

		try
	{
		Form f4("Presidential Pardon", 151, 151);

		std::cout << "f4 created." << std::endl;
	}
	catch (std::exception &er)
	{
		std::cerr << "Error caught: " << er.what() << std::endl;
	}

	return 0;
}
