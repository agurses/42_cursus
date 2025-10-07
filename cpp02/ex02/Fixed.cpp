#include "Fixed.hpp"

//_____________Constructor_____________

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	point = 0;
}

Fixed::Fixed( const Fixed& input )
{
	std::cout << "Copy constructor called" << std::endl;
	point = input.point;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}
//_____________Float and Int Constructor_____________
Fixed::Fixed( int value)
{
	point = value << number;
}

Fixed::Fixed( float value )
{
	point = roundf( value * (1 << number));
}

//_____________Operators_____________

Fixed& Fixed::operator=( const Fixed& input )
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &input)
		point = input.point;
	return (*this);
}

std::ostream& operator<<( std::ostream& os, const Fixed& obj )
{
	os << obj.toFloat();
	return ( os );
}

//_____________change cast_____________

float Fixed::toFloat() const
{
	std::cout << "Float Constructor called" << std::endl;
	return ( static_cast<float>(point) / (1 << number) );
}

int Fixed::toInt() const
{
	std::cout << "Int Constructor called" << std::endl;
	return ( static_cast<int>(point >> number) );
}

//_____________Raw Bits_____________

int Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (point);
}

void Fixed::setRawBits( const int input )
{
	std::cout << "setRawBits member function called" << std::endl;
	point = input;
}

//_____________Compare Operator_____________

bool Fixed::operator>(const Fixed& other) const
{
	return (point > other.point);
}

bool Fixed::operator<(const Fixed& other) const
{
	return ( point < other.point);
}

bool Fixed::operator>=(const Fixed& other) const
{
	return ( point >= other.point);
}

bool Fixed::operator<=(const Fixed& other) const
{
	return ( point <= other.point);
}

bool Fixed::operator==(const Fixed& other) const
{
	return ( point == other.point);
}

bool Fixed::operator!=(const Fixed& other) const
{
	return ( point != other.point);
}

//_____________ArithmeticOperator____________

Fixed Fixed::operator+( const Fixed& input ) const
{
	return ( Fixed(toFloat() + input.toFloat()) );
}

Fixed Fixed::operator-( const Fixed& input ) const
{
	return ( Fixed(toFloat() - input.toFloat()) );
}

Fixed Fixed::operator*( const Fixed& input ) const
{
	std::cout << "* Constructor called" << std::endl;
	return ( Fixed(toFloat() * input.toFloat()) );
}

Fixed Fixed::operator/( const Fixed& input ) const
{
	return ( Fixed(toFloat() / input.toFloat()) );
}

//_____________Increase and Decrease Operator_____________

//______Pre-increment______

Fixed& Fixed::operator++()
{
	point++;
	return ( *this );
}

Fixed& Fixed::operator--()
{
	point--;
	return ( *this );
}

//______Post-increment______

Fixed Fixed::operator++( int )
{
	Fixed temp(*this);
	point++;
	return ( temp );
}

Fixed Fixed::operator--( int )
{
	Fixed temp(*this);
	point--;
	return ( temp );
}

//_____________Min and Max Static Functions_____________

Fixed& Fixed::min( Fixed& a, Fixed& b)
{
	return ( (a < b) ? a : b );
}

const Fixed& Fixed::min( const Fixed& a, const Fixed& b )
{
	return ( (a < b) ? a : b );
}

Fixed& Fixed::max( Fixed&a, Fixed& b)
{
	return ((a > b) ? a : b);
}

const Fixed& Fixed::max( const Fixed& a, const Fixed& b )
{
	return ((a > b) ? a : b);
}
