#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5)
{
    target = "DefaultTarget";
}

PresidentialPardonForm::PresidentialPardonForm(std::string str) : AForm("PresidentialPardonForm", 25, 5)
{
    target = str;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &src) : AForm(src)
{
    target = src.target;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &src)
{
    if (this != &src)
        target = src.target;
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getExecGrade())
        throw GradeTooLowException();

    std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}