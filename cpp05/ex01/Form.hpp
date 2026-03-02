#ifndef FORM_HPP
# define FORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;

class Form
{
	private:
		const std::string name;
		bool isSigned;
		const int signGrade;
		const int execGrade;
	public:
		Form();
		Form(std::string title, int a, int b);
		Form(const Form &a);
		Form &operator=(const Form &a);
		~Form();

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
};

std::ostream &operator<<(std::ostream &os, const Form &b);

#endif