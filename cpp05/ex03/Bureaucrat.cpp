#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat() : name("newBureucrat")
{
	grade = 150;
}

Bureaucrat::Bureaucrat(std::string input, int value) : name(input)
{
	if (input.empty())
	{
		std::cout << "Be careful. Name is empty." << std::endl;
	}

	if (value >= 1 && value <= 150)
		grade = value;
	else
		if (value < 1)
			throw Bureaucrat::GradeTooHighException();
		else
			throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &input) : name(input.name)
{
	grade = input.grade;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &input)
{
	if (this != &input)
		grade = input.grade;
	return *this;
}

Bureaucrat::~Bureaucrat()
{

}

void Bureaucrat::incrementGrade()
{
	if (grade > 1)
		grade -= 1;
	else
		throw Bureaucrat::GradeTooHighException();
}

void Bureaucrat::decrementGrade()
{
	if (grade < 150)
		grade += 1;
	else
		throw Bureaucrat::GradeTooLowException();
}

void Bureaucrat::signForm(AForm &form)
{
	try {
		form.beSigned(*this);

		std::cout << name << " signed " << form.getName() << std::endl;
	}
	catch (std::exception &a)
	{
		std::cout << name << " couldn't sign " << form.getName() << " because " << a.what() << std::endl;
	}
}

std::string Bureaucrat::getName() const
{
	return name;
}

int Bureaucrat::getGrade() const
{
	return grade;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &input)
{
	os << input.getName() << ", bureaucrat grade " <<  input.getGrade() << ".";
	return os;
}

void Bureaucrat::executeForm(AForm const &form) const
{
    try {
        form.execute(*this);
        std::cout << name << " executed " << form.getName() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << name << " couldn't execute " << form.getName() << " because " << e.what() << std::endl;
    }
}