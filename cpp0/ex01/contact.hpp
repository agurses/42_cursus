#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>

class Contact{

	private:

		std::string firstName;
		std::string lastName;
		std::string nickName;
		std::string phoneNumber;
		std::string darkSecret;

	public:

		void setFirstName(std::string &str);
		void setLastName(std::string &str);
		void setNickName(std::string &str);
		void setPhoneNumber(std::string &str);
		void setDarkestSecret(std::string &str);

		std::string getFirstName();
		std::string getLastName();
		std::string getNickName();
		std::string getPhoneNumber();
		std::string getDarkestSecret();

};

#endif