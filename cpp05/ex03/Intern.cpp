#include "Intern.hpp"

Intern::Intern()
{

}

Intern::Intern(const Intern &str)
{
    (void)str;
}

Intern &Intern::operator=(const Intern &str)
{
    (void)str;
    return *this;
}

Intern::~Intern()
{

}


//--------------------------------------------------------//

typedef struct s_formType
{
	std::string name;
	AForm* (*fonc)(std::string);
}	t_formType;

AForm *shrubberycreate(std::string input)
{
    return new ShrubberyCreationForm(input);
}

AForm* Robotomycreate(std::string input)
{
    return new RobotomyRequestForm(input);
}

AForm* Presidentialcreate(std::string input)
{
    return new PresidentialPardonForm(input);
}

AForm *Intern::makeForm(std::string s1, std::string s2)
{
    t_formType forms[3] = {
        {"shrubbery creation", shrubberycreate},
        {"robotomy request", Robotomycreate},
        {"presidential pardon", Presidentialcreate}
    };

    for (int i = 0; i < 3; i++)
    {
        if (s1 == forms[i].name)
        {
            std::cout << "Intern creates " << s1 << std::endl;
            return forms[i].fonc(s2);
        }
    }
    std::cout << "Error: " << s1 << " is not a valid form name." << std::endl;
    return NULL;
}