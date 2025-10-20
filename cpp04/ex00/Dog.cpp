#include "Dog.hpp"

Dog::Dog()
	: Animal()
{
	type = "Dog";
	std::cout << "Dog constructed!" << std::endl;
}

Dog::Dog( const std::string& input )
	: Animal(input)
{
	std::cout << "Dog constructed with input!" << std::endl;
	type = "Dog";
}

Dog::Dog( const Dog& input )
	: Animal(input)
{
	type = "Dog";
	std::cout << "Dog copy constructed!" << std::endl;
}

Dog& Dog::operator=( const Dog& input )
{
	if (this != &input)
	{
		Animal::operator=( input );
		type = "Dog";
	}
	std::cout << "Dog assigned!" << std::endl;
	return ( *this );
}

Dog::~Dog()
{
	std::cout << "Dog deconstructed!" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Bark!" << std::endl;
}

