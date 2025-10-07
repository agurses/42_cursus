#include "Fixed.hpp"

//_____________Constructor_____________

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	point = 0;
}

Fixed::Fixed(const Fixed& input)
{
	std::cout << "Copy constructor called" << std::endl;
	point = input.point;
}

Fixed& Fixed::operator=(const Fixed& input)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &input)
		this->point = input.point;
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

//_____________Int and Float Constructor_____________

Fixed::Fixed( int value )
{
	std::cout << "Int constructor called" << std::endl;
	point = value << number;
}

Fixed::Fixed( float value )
{
	std::cout << "Float constructor called" << std::endl;
	point = roundf(value * (1 << number));
}

float Fixed::toFloat() const
{
	return (static_cast<float>(point) / (1 << number));
}

int Fixed::toInt() const
{
	return (static_cast<int>(point >> number) );
}

//_____________Insertion operator_____________


std::ostream& operator<<(std::ostream& os, const Fixed& obj)
{
	os << obj.toFloat();
    return os;
}

//_____________Raw Bits_____________

int Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (point);
}

void Fixed::setRawBits(int input)
{
	std::cout << "setRawBits member function called" << std::endl;
	point = input;
}
