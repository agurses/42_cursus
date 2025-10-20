#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal{
	private:
		Brain* brain;
	public:
		Dog();
		Dog( const std::string& input );
		Dog( const Dog& input );
		Dog& operator=( const Dog& input );
		~Dog();

		void makeSound() const;
		Brain& getBrain();
		void setBrain( const Brain& input );
};


#endif