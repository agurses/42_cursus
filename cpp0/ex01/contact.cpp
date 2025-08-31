#include "contact.hpp"

void Contact::setFirstName(std::string &str)
{
	firstName = str;
}

void Contact::setLastName(std::string &str)
{
	lastName = str;
}

void Contact::setNickName(std::string &str)
{
	nickName = str;
}

void Contact::setPhoneNumber(std::string &str)
{
	phoneNumber = str;
}

void Contact::setDarkestSecret(std::string &str)
{
	darkSecret = str;
}

std::string Contact::getFirstName()
{
	return (firstName);
}
std::string Contact::getLastName()
{
	return (lastName);
}
std::string Contact::getNickName()
{
	return (nickName);
}
std::string Contact::getPhoneNumber()
{
	return (phoneNumber);
}
std::string Contact::getDarkestSecret()
{
	return (darkSecret);
}
