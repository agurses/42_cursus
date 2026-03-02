#ifndef AFORM_HPP
# define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class AForm
{
	//Pure Virtual Function
	private:
		const std::string name;
		bool isSigned;
		const int signGrade;
		const int execGrade;
	public:
		AForm();
		AForm(std::string title, int a, int b);
		AForm(const AForm &a);
		AForm &operator=(const AForm &a);
		virtual ~AForm();
		
		//////////////////////
		virtual void execute(Bureaucrat const &executor) const = 0;
		//////////////////////

		std::string getName() const;
		bool getIsSigned() const;
		int getSignGrade() const;
		int getExecGrade() const;

		void beSigned(const Bureaucrat &b);

		class GradeTooHighException: public std::exception{
			public:
				const char* what() const throw();
		};

		class GradeTooLowException : public std::exception{
			public:
				const char* what() const throw();
		};
		
		class FormNotSignedException : public std::exception{
			public:
				const char* what() const throw();
		};
};

std::ostream &operator<<(std::ostream &os, const AForm &b);

#endif