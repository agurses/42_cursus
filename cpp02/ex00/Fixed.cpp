#include "Fixed.hpp"

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	this->point = 0;
}

Fixed::Fixed(const Fixed& input)
{
	std::cout << "Copy constructor called" << std::endl;
	this->point = input.point;
}

Fixed& Fixed::operator=(const Fixed& input)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &input)
		this->point = input.point;
	return (*this);
}

int Fixed::getRawBits( void ) const 
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->point);
}

void Fixed::setRawBits( int const raw )
{
	std::cout << "setRawBits member function called" << std::endl;
	this->point = raw;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}