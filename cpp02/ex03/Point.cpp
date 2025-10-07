#include "Point.hpp"

Point::Point()
	: x(), y()
{
	std::cout << "Default constructor called" << std::endl;
}

Point::Point( float str, float str2)
	: x(str), y(str2)
{
	std::cout << "Float constructor called" << std::endl;
}

Point::Point( const Point& input )
	: x(input.x), y(input.y)
{
	std::cout << "Copy constructor called" << std::endl;
}

Point& Point::operator=(const Point& input)
{
	(void)input;
	std::cout << "Assignment constructor called" << std::endl;
	return (*this);
}

Point::~Point()
{
	std::cout << "Deconstructor called" << std::endl;
}

const Fixed& Point::getX() const
{
	return ( x );
}

const Fixed& Point::getY() const
{
	return ( y );
}
