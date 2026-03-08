#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>
#include <iostream>

class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &input);
		ScalarConverter &operator=(const ScalarConverter &input);
		~ScalarConverter();
	public:
		static void convert(const std::string &str);
};

#endif