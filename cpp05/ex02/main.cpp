#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <ctime>
#include <cstdlib>

int main()
{
	Bureaucrat a;
	Bureaucrat b("Janet", 3), c(b), d("Antony", 4);
	Bureaucrat e("Merrick", 1);
	Bureaucrat f;

	srand(time(0));

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;
	std::cout << f << std::endl << std::endl;

//-----------------------------------------------------------------//

	ShrubberyCreationForm f1;
	ShrubberyCreationForm f2("Offical");

	std::cout << f1 << std::endl;
	try
	{
		f1.beSigned(a);

		std::cout << f1 << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		f1.beSigned(b);
		f1.execute(b);
		std::cout << "Form Created. Tree" << std::endl;
	}
	catch(const std::exception& er)
	{
		std::cerr << er.what() << std::endl;
	}

		try
	{
		f2.beSigned(c);
		f2.execute(c);
		std::cout << "Form Created. Tree" << std::endl;
	}
	catch(const std::exception& er)
	{
		std::cerr << er.what() << std::endl;
	}

	std::cout << std::endl;
//-----------------------------------------------------------------//

	RobotomyRequestForm r1;

	try
	{
		r1.beSigned(a);

		std::cout << "Form Created. Robo " << std::endl;
	}
	catch(const std::exception& er)
	{
		std::cerr << er.what() << std::endl;
	}
		try
	{
		r1.beSigned(b);
		r1.execute(b);

		std::cout << "Form Created. Robo " << std::endl;
	}
	catch(const std::exception& er)
	{
		std::cerr << er.what() << std::endl;
	}

	std::cout << std::endl;
//-----------------------------------------------------------------//
	PresidentialPardonForm p1;

		try
	{
		p1.beSigned(a);

		std::cout << "Form Created. Robo " << std::endl;
	}
	catch(const std::exception& er)
	{
		std::cerr << er.what() << std::endl;
	}
		try
	{
		p1.beSigned(b);
		p1.execute(b);

		std::cout << "Form Created. Robo " << std::endl;
	}
	catch(const std::exception& er)
	{
		std::cerr << er.what() << std::endl;
	}

	std::cout << std::endl;

//-----------------------------------------------------------------//

	// Pointer ile form oluşturma
	AForm* tree = new ShrubberyCreationForm("Garden");
	AForm* robot = new RobotomyRequestForm("Bender");
	AForm* pardon = new PresidentialPardonForm("Arthur Dent");

	// Düşük yetkili bürokrat executeForm denemesi (imzasız form)
	a.executeForm(*tree);

	std::cout << std::endl;

	// Yüksek yetkili bürokrat imzalaması
	b.signForm(*tree);
	b.signForm(*robot);
	e.signForm(*pardon);

	std::cout << std::endl;

	// Düşük yetkili bürokrat execute denemesi (imzalı ama yetkisiz)
	a.executeForm(*tree);
	a.executeForm(*robot);
	a.executeForm(*pardon);

	std::cout << std::endl;

	// Yüksek yetkili bürokrat execute denemesi (başarılı)
	b.executeForm(*tree);
	b.executeForm(*robot);
	e.executeForm(*pardon);

	std::cout << std::endl;

	delete tree;
	delete robot;
	delete pardon;

	PresidentialPardonForm q1;
	b.signForm(q1);
	b.executeForm(q1);
	return 0;
}
