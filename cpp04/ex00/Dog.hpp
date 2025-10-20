#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal{
	public:
		Dog();
		Dog( const std::string& input );
		Dog( const Dog& input );
		Dog& operator=( const Dog& input );
		~Dog();

		void makeSound() const;
};


#endif