#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() :_data_in_csv()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) :
	_data_in_csv(other._data_in_csv)
{

}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		this->_data_in_csv = other._data_in_csv;

	return *this;
}

BitcoinExchange::~BitcoinExchange()
{

}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
	{
		throw std::runtime_error("Error: could not open file.");
	}

	std::string line;

	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream currentRow(line);
		std::string date;
		std::string valueString;
		double value;

		if (!std::getline(currentRow, date, ','))
			continue;
		if (!std::getline(currentRow, valueString))
			continue;
		
		std::stringstream valueStream(valueString);

		if (!(valueStream >> value))
			continue;
		
		_data_in_csv[date] = value;
	}
	file.close();
}

void BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");

	std::string line;

	if (!std::getline(file, line))
		throw std::runtime_error("Error: empty input file.");

	if (line != "date | value")
		throw std::runtime_error("Error: invalid header.");

	while (std::getline(file, line))
	{
		std::stringstream currentRow(line);
		std::string date;
		std::string valueText;
		double value;

		if (!std::getline(currentRow, date, '|'))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::stringstream dateStream(date);
		std::string extraDate;
		if (!(dateStream >> date) || (dateStream >> extraDate))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (!std::getline(currentRow, valueText))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		
		std::stringstream valueStream(valueText);

		if (!(valueStream >> value))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string extra;
		if (valueStream >> extra)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		bool validDate = date.length() == 10
			&& date[4] == '-'
			&& date[7] == '-';
		for (std::string::size_type i = 0; validDate && i < date.length(); ++i)
		{
			if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9'))
				validDate = false;
		}

		int year = 0;
		int month = 0;
		int day = 0;
		if (validDate)
		{
			std::stringstream yearStream(date.substr(0, 4));
			std::stringstream monthStream(date.substr(5, 2));
			std::stringstream dayStream(date.substr(8, 2));
			yearStream >> year;
			monthStream >> month;
			dayStream >> day;

			const int daysInMonth[13] =
				{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			int maxDay = month >= 1 && month <= 12
				? daysInMonth[month] : 0;
			bool leapYear = year % 4 == 0
				&& (year % 100 != 0 || year % 400 == 0);
			if (month == 2 && leapYear)
				maxDay = 29;
			if (month < 1 || month > 12 || day < 1 || day > maxDay)
				validDate = false;
		}

		if (!validDate)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		std::map<std::string , double>::const_iterator it;
		it = _data_in_csv.lower_bound(date);

		if (it == _data_in_csv.end() || it->first != date)
		{
			if (it == _data_in_csv.begin())
			{
				std::cout << "Error: no lower date found." << std::endl;
				continue;
			}
			--it;
		}

		double rate = it->second;
		double result = rate * value;

		std::cout.precision(10);
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
	
}
