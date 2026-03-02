#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>


class Form;

class Bureaucrat{
	private:
		const std::string name;
		int grade;
	public:
		Bureaucrat();
		Bureaucrat(std::string input, int value);
		Bureaucrat(const Bureaucrat &input);
		Bureaucrat& operator=(const Bureaucrat &input);
		~Bureaucrat();

		void incrementGrade();
		void decrementGrade();
		std::string getName() const;
		int getGrade() const;

		void signForm(Form &form);

	class GradeTooHighException : public std::exception {
		public:
			const char* what() const throw();
	};
	class GradeTooLowException : public  std::exception {
		public:
			const char* what() const throw();
	};
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &input);

#endif