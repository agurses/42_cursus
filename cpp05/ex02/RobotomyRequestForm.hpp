#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include "Bureaucrat.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		std::string title;
	public:
		RobotomyRequestForm();
		RobotomyRequestForm(std::string str);
		RobotomyRequestForm(const RobotomyRequestForm &str);
		RobotomyRequestForm &operator=(const RobotomyRequestForm &str);
		~RobotomyRequestForm();

		void execute(Bureaucrat const &executor) const;
};

#endif