#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137)
{
	title = "DefaultShrubberyCreationForm";

}

ShrubberyCreationForm::ShrubberyCreationForm(std::string str) : AForm("ShrubberyCreationForm", 145, 137)
{
	title = str;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &str) : AForm(str)
{
	title = str.title;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &str)
{
	if (this != &str)
		title = str.title;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{

}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (!getIsSigned())
		throw FormNotSignedException();
	if (executor.getGrade() > getExecGrade())
		throw GradeTooLowException();

	std::string filename = title + "_shrubbery";
	std::ofstream report(filename.c_str());

	if (!report.is_open())
	{
		std::cerr << "Error: file couldn't open." << std::endl;
		return;
	}

	report << "           // |    |/.         " << std::endl;
	report << "        // / /||/  /_/___/_.   " << std::endl;
	report << "         //   |/ //            " << std::endl;
	report << "    _/__/_/   |  /_____/_      " << std::endl;
	report << "           /  | /          /.  " << std::endl;
	report << "  __ _-----`  |{,-----------~. " << std::endl;
	report << "            / }{.              " << std::endl;
	report << "             }{{.              " << std::endl;
	report << "             }}{               " << std::endl;
	report << "             {{}               " << std::endl;
	report << "       , -=-~{ .-^- _          " << std::endl;

	report.close();
}
