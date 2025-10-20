#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	type = "WrongAnimal";
	std::cout << "Default WrongAnimal constructed!" << std::endl;
}

WrongAnimal::WrongAnimal( const std::string& input )
{
	std::cout << "WrongAnimal constructed with input called!" << std::endl;
	type = input;
}

WrongAnimal::WrongAnimal( const WrongAnimal& other )
{
	std::cout << "WrongAnimal copy constructed called!" << std::endl;
	type = other.type;
}

WrongAnimal& WrongAnimal::operator=( const WrongAnimal& input )
{
	std::cout << "WrongAnimal assignment operator called!" << std::endl;
	if (this != &input)
		type = input.type;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal deconstructed!" << std::endl;
}

void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal makes a sound!" << std::endl;
}

std::string WrongAnimal::getType() const
{
	return (type);
}
