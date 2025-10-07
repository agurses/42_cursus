#include "Fixed.hpp"

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	point = 0;
}

Fixed::Fixed( int input )
{
	std::cout << "Default with input constructor called" << std::endl;
	point = input << number;
}

Fixed::Fixed( float value )
{
	point = roundf( value * (1 << number));
}

Fixed::Fixed( const Fixed& input )
{
	std::cout << "Copy constructor called" << std::endl;
	point = input.point;
}

Fixed& Fixed::operator=( const Fixed& input)
{
	std::cout << "Assignment constructor called" << std::endl;
	if (this != &input)
		point = input.point;
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Deconstructor called" << std::endl;
}

float Fixed::toFloat() const
{
	return ( static_cast<float>(point) / (1 << number));
}

int Fixed::toInt() const
{
	return( static_cast<int>(point >> number) );
}

int Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return( point );
}

void Fixed::setRawBits( int const raw )
{
	std::cout << "setRawBits member function called" << std::endl;
	point = raw;
}
