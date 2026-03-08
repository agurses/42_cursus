#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{

}

ScalarConverter::ScalarConverter(const ScalarConverter &input)
{
	(void)input;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &input)
{
	(void)input;
	return *this;
}

ScalarConverter::~ScalarConverter()
{

}

void printChar(double value)
{
	if (std::isnan(value) || std::isinf(value) || value < 0 || value > 127)
		std::cerr << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(value)))
		std::cerr << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
}

void printInt(double value)
{
	if (std::isnan(value) || std::isinf(value)
		|| value > static_cast<double>(INT_MAX)
		|| value < static_cast<double>(INT_MIN))
		std::cerr << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;
}

void printFloat(double value)
{
	float f = static_cast<float>(value);
	if (f == static_cast<int>(f) && !std::isinf(f) && !std::isnan(f)
		&& f >= static_cast<float>(INT_MIN) && f <= static_cast<float>(INT_MAX))
		std::cout << "float: " << f << ".0f" << std::endl;
	else
		std::cout << "float: " << f << "f" << std::endl;
}

void printDouble(double value)
{
	if (value == static_cast<int>(value) && !std::isinf(value) && !std::isnan(value)
		&& value >= static_cast<double>(INT_MIN) && value <= static_cast<double>(INT_MAX))
		std::cout << "double: " << value << ".0" << std::endl;
	else
		std::cout << "double: " << value << std::endl;
}

bool isPseudoLiteral(const std::string &str)
{
	return (str == "nan" || str == "nanf"
		 || str == "+inf" || str == "-inf"
		 || str == "+inff" || str == "-inff");
}

bool isFloat(const std::string &str)
{
	int i = 0;
	bool Dot = false;

	if (str[0] == '\0')
		return false;    
	if (str[str.length() - 1] != 'f')
		return false;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i] && str[i] != 'f')
	{
		if (str[i] == '.')
		{
			if (Dot == true)
				return false;
			Dot = true;
		}
		else if(!isdigit(str[i]))
			return false;
		i++;
	}
	return Dot;
}

bool isChar(const std::string &str)
{
	if (str.length() == 1 && !isdigit(str[0]))
		return true;
	else
		return false;
}

bool isInt(const std::string &str)
{
	int i = 0;

	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return false;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return false;
		i++;
	}
	return true;
}

bool isDouble(const std::string &str)
{
	bool Dot = false;
	int i = 0;
	
	if (str[i] == '\0')
		return false;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (Dot == true)
				return false;
			Dot = true;
		}
		else if (!isdigit(str[i]))
			return false;
		i++;
	}
	return Dot;
}

void ScalarConverter::convert(const std::string &str)
{
	double value;

	if (str.empty())
	{
		std::cerr << "Error: input empty" << std::endl;
		return;
	}
	if (isPseudoLiteral(str))
	{
		if (str == "nanf" || str == "+inff" || str == "-inff")
			value = std::strtod(str.substr(0, str.length() - 1).c_str(), NULL);
		else
			value = std::strtod(str.substr(0, str.length()).c_str(), NULL);
	}
	else if(isChar(str))
	{
		value = static_cast<double>(str[0]);
	}
	else if (isInt(str))
	{
		long x = strtol(str.c_str(), NULL, 10);
		if (x > INT_MAX || x < INT_MIN)
		{
			std::cerr << "Error: Int overflow! " << std::endl;
			return;
		}
		value = static_cast<double>(x);
	}
	else if (isFloat(str))
	{
		value = std::strtod(str.c_str(), NULL);
	}
	else if (isDouble(str))
	{
	   value = std::strtod(str.c_str(), NULL);
	}
	else
	{
		std::cerr << "Error: invalid input!" << std::endl;
		return;
	}
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
