#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : name("Default Form"), isSigned(false), signGrade(150), execGrade(150)
{
    
}
AForm::AForm(std::string title, int a, int b) : name(title), signGrade(a), execGrade(b)
{
	isSigned = false;
	if (title.empty())
		std::cout << "Attation Please. Name is Empty" << std::endl;

	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &a) : name(a.name), signGrade(a.signGrade), execGrade(a.execGrade)
{
	isSigned = a.isSigned;
}

AForm &AForm::operator=(const AForm &a)
{
	if (this != &a)
		isSigned = a.isSigned;
	return *this;
}

AForm::~AForm()
{

}

std::string AForm::getName() const
{
	return name;
}

bool AForm::getIsSigned() const
{
	return isSigned;
}

int AForm::getSignGrade() const
{
	return signGrade;
}

int AForm::getExecGrade() const
{
	return execGrade;
}

void AForm::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > signGrade)
		throw GradeTooLowException();
	isSigned = true;
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return "Form not signed!";
}

std::ostream &operator<<(std::ostream &os, const AForm &b)
{
	os << "Form name: " << b.getName()
	<< ", is signed: " << (b.getIsSigned() ? "yes" : "no")
	<< ", sign grade: " << b.getSignGrade()
	<< ", exec sign: " << b.getExecGrade();
	return os;
}
