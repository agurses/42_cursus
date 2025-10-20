#include "WrongCat.hpp"

WrongCat::WrongCat()
	: WrongAnimal()
{
	std::cout << "Default WrongCat constructed!" << std::endl;
	type = "Cat";
}

WrongCat::WrongCat( const std::string& input)
	: WrongAnimal(input)
{
	std::cout << "WrongCat constructed with input!" << std::endl;
	type = "Cat";
}

WrongCat::WrongCat( const WrongCat& input )
	: WrongAnimal(input)
{
	type = "Cat";
	std::cout << "Cat copy constructed!" << std::endl;
}

WrongCat& WrongCat::operator=( const WrongCat& input )
{
	if ( this != &input )
	{
		WrongAnimal::operator=( input );
		type = "Cat";
	}
	std::cout << "WrongCat assigned!" << std::endl;
	return ( *this );
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat deconstructed!" << std::endl;
}

void WrongCat::makeSound() const
{
	std::cout << "Meow!" << std::endl;
}
