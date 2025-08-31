#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>
#include "contact.hpp"

class PhoneBook{
	private:
		Contact contact[8];
		int		count;
	
	public:
		PhoneBook();
		void	add_contact();
		void	search();

};

#endif