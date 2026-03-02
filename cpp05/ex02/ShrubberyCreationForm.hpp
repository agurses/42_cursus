#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
	private:
		std::string title;
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(std::string str);
		ShrubberyCreationForm(const ShrubberyCreationForm &str);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &str);
		~ShrubberyCreationForm();

		void execute(Bureaucrat const &executor) const;
};

#endif