#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45)
{
	title = "DefaultRobotomyRequestForm";

}

RobotomyRequestForm::RobotomyRequestForm(std::string str) : AForm("RobotomyRequestForm", 72, 45)
{
	title = str;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &str) : AForm(str)
{
	title = str.title;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &str)
{
	if (this != &str)
		title = str.title;
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{

}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if (!getIsSigned())
		throw FormNotSignedException();
	if (executor.getGrade() > getExecGrade())
		throw GradeTooLowException();

	std::cout << "* DRILLING NOISES * Bzzzzz..." << std::endl;

	if (rand() % 2 == 0)
		std::cout << title << " has been robotomized successfully!" << std::endl;
	else
		std::cout << title << " robotomy failed!" << std::endl;
}    
