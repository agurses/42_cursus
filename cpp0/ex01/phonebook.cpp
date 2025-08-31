#include "phonebook.hpp"

PhoneBook::PhoneBook()
{
	count = 0;
}

void	PhoneBook::search()
{
	int max;

	std::cout << std::right << std::setw(10) << "Index" << "|"
              << std::right << std::setw(10) << "FirstName" << "|"
              << std::right << std::setw(10) << "LastName" << "|"
              << std::right << std::setw(10) << "NickName" << std::endl;
	
	if (count < 8)
		max = count;
	else
		max = 8;
	if (max == 0)
	{
		std::cout << "Empty Book" << std::endl;
	}
	for (int i = 0; i < max; i++)
	{
		// Index
		std::cout << std::setw(10) << i << "|";
		//___________________________________________________

		// FirstName
		if (contact[i].getFirstName().length() > 10)
		{
			std::cout << std::setw(10) << contact[i].getFirstName().substr(0, 9) + "." << "|";
		}
		else
			std::cout << std::setw(10) << contact[i].getFirstName() << "|";
		//___________________________________________________

		// LastName
		if (contact[i].getLastName().length() > 10)
		{
			std::cout << std::setw(10) << contact[i].getLastName().substr(0, 9) + "." << "|";
		}
		else
			std::cout << std::setw(10) << contact[i].getLastName() << "|";
		//___________________________________________________

		//NickName
		if (contact[i].getNickName().length() > 10)
		{
			std::cout << std::setw(10) << contact[i].getNickName().substr(0, 9) + "." << "|";
		}
		else
			std::cout << std::setw(10) << contact[i].getNickName() << "|";
		//___________________________________________________

		std::cout << std::endl;
	}

	int	x;
	std::cout << "Enter Index" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	if (input.length() != 1 || !isdigit(input[0]))
	{
		std::cout << "Invalid Index" << std::endl;
		return ;
	}
	else
		x = input[0] - '0';
	
	if (x < 0 || x >= max)
	{
		std::cout << "Invalid Index" << std::endl;
		return ;
	}
	std::cout << "First Name: " << contact[x].getFirstName() << std::endl;
	std::cout << "Last Name: " << contact[x].getLastName() << std::endl;
	std::cout << "Nick Name: " << contact[x].getNickName() << std::endl;
	std::cout << "Phone Number: " << contact[x].getPhoneNumber() << std::endl;
	std::cout << "Dark Secret: " << contact[x].getDarkestSecret() << std::endl;
}

void	PhoneBook::add_contact()
{
	Contact member;
	std::string input;

	input.clear();
	while (input.empty())
	{
		std::cout << "First Name : ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(0);
		if (input.empty())
			std::cout << "Please give me input" << std::endl;

	}
	member.setFirstName(input);
	
	input.clear();
	while (input.empty())
	{
		std::cout << "Last Name : ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(0);
		if (input.empty())
			std::cout << "Please give me input" << std::endl;
	}
	member.setLastName(input);
	
	input.clear();
	while (input.empty())
	{
		std::cout << "Nick Name : ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(0);
		if (input.empty())
			std::cout << "Please give me input" << std::endl;
	}
	member.setNickName(input);

	input.clear();
	while (input.empty())
	{
		std::cout << "Phone Number : ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(0);
		if (input.empty())
			std::cout << "Please give me input" << std::endl;
	}
	member.setPhoneNumber(input);

	input.clear();
	while (input.empty())
	{
		std::cout << "Dark Secret : ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(0);
		if (input.empty())
			std::cout << "Please give me input" << std::endl;
	}
	member.setDarkestSecret(input);

	std::cout << "Added..." << std::endl;

	contact[count % 8] = member;
	count++;
}

void	read_input(std::string input, PhoneBook &phoneBook)
{
	if (input == "ADD")
	{
		phoneBook.add_contact();
	}
	else if (input == "SEARCH")
	{
		phoneBook.search();
	}
	else if (input == "EXIT")
	{
		exit (0);
	}
}

int main()
{
	PhoneBook phoneBook;
	std::string	input;

	while (1)
	{
		std::cout << "Write A Valid Command" << std::endl;
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(0);
		read_input(input, phoneBook);
	}
}
