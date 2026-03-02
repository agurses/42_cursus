#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : name("Default Form"), isSigned(false), signGrade(150), execGrade(150)
{
    
}
Form::Form(std::string title, int a, int b) : name(title), signGrade(a), execGrade(b)
{
	isSigned = false;
	if (title.empty())
		std::cout << "Attation Please. Name is Empty" << std::endl;

	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &a) : name(a.name), signGrade(a.signGrade), execGrade(a.execGrade)
{
	isSigned = a.isSigned;
}

Form &Form::operator=(const Form &a)
{
	if (this != &a)
		isSigned = a.isSigned;
	return *this;
}

Form::~Form()
{

}

std::string Form::getName() const
{
	return name;
}

bool Form::getIsSigned() const
{
	return isSigned;
}

int Form::getSignGrade() const
{
	return signGrade;
}

int Form::getExecGrade() const
{
	return execGrade;
}

void Form::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > signGrade)
		throw GradeTooLowException();
	isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";;
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}

std::ostream &operator<<(std::ostream &os, const Form &b)
{
	os << "Form name: " << b.getName()
	<< ", is signed: " << (b.getIsSigned() ? "yes" : "no")
	<< ", sign grade: " << b.getSignGrade()
	<< ", exec sign: " << b.getExecGrade();
	return os;
}
