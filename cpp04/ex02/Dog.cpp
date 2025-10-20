#include "Dog.hpp"

Dog::Dog()
	: Animal()
{
	type = "Dog";
	brain = new Brain();
	std::cout << "Dog constructed!" << std::endl;
}

Dog::Dog( const std::string& input )
	: Animal(input)
{
	std::cout << "Dog constructed with input!" << std::endl;
	type = "Dog";
	brain = new Brain;
}

Dog::Dog( const Dog& input )
	: Animal(input)
{
	type = "Dog";
	brain = new Brain(*input.brain);
	std::cout << "Dog copy constructed!" << std::endl;
}

Dog& Dog::operator=( const Dog& input )
{
	if (this != &input)
	{
		Animal::operator=( input );
		type = "Dog";
		delete brain;
		brain = new Brain(*input.brain);
	}
	std::cout << "Dog assigned!" << std::endl;
	return ( *this );
}

Dog::~Dog()
{
	delete brain;
	std::cout << "Dog deconstructed!" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Bark!" << std::endl;
}

Brain& Dog::getBrain()
{
	return *brain;
}

void Dog::setBrain( const Brain& input )
{
	*brain = input;
}
