#ifndef INTERN_HPP
# define INTERN_HPP

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern
{
	public:
		Intern();
		Intern(const Intern &str);
		Intern &operator=(const Intern &str);
		~Intern();

		AForm *makeForm(std::string s1, std::string s2);
};

#endif