#include "Cat.hpp"

Cat::Cat()
	: Animal()
{
	type = "Cat";
	std::cout << "Cat constructed!" << std::endl;
}

Cat::Cat( const std::string& input )
	: Animal(input)
{
	std::cout << "Cat constructed with input!" << std::endl;
	type = "Cat";
}

Cat::Cat( const Cat& input )
	: Animal(input)
{
	type = "Cat";
	std::cout << "Cat copy constructed!" << std::endl;
}

Cat& Cat::operator=( const Cat& input )
{
	if (this != &input)
	{
		Animal::operator=( input );
		type = "Cat";
	}
	std::cout << "Cat assigned!" << std::endl;
	return ( *this );
}

Cat::~Cat()
{
	std::cout << "Cat deconstructed!" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Meow!" << std::endl;
}

