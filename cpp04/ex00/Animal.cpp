#include "Animal.hpp"

Animal::Animal()
{
	this->type = "DefaultAnimal";
	std::cout << "Animal constructed!" << std::endl;
}

Animal::Animal( const std::string& input )
{
	std::cout << "Animal constructed with input called!" << std::endl;
	this->type = input;
}

Animal::Animal( const Animal& other )
{
	std::cout << "Copy constructor called" << std::endl;
	type = other.type;
}

Animal& Animal::operator=( const Animal& input )
{
	std::cout << "Animal assigmanet operator called!" << std::endl;
	if (this != &input)
		type = input.type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal destructed!" << std::endl;
}
		

void Animal::makeSound() const
{
	std::cout << "Animal makes a sound." << std::endl;
}

std::string Animal::getType() const
{
	return (type);
}
