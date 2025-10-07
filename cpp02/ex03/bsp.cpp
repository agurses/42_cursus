#include "Point.hpp"

int area(Point const &a, Point const &b, Point const &c)
{
	int result = ((a.getX().getRawBits() * b.getY().getRawBits()) + 
				(b.getX().getRawBits() * c.getY().getRawBits()) + 
				(c.getX().getRawBits() * a.getY().getRawBits()) -
				(a.getY().getRawBits() * b.getX().getRawBits()) -
				(b.getY().getRawBits() * c.getX().getRawBits()) -
				(c.getY().getRawBits() * a.getX().getRawBits())) / 2;
	return (result);
}

bool bsp( Point const a, Point const b, Point const c, Point const point)
{
	if (area(a, b, point) == 0 ||
		area(a, point, c) == 0 ||
		area(point, b, c) == 0)
	{
		std::cout << "The point is on the edge or vertex of the triangle." << std::endl;
		return (0);
	}
	if (area(a, b, c) == area(a, b, point) + area(a, point, c) + area(point, b, c))
	{
		std::cout << "The point is inside the triangle." << std::endl;
		return ( 1 );
	}
	else
	{
		std::cout << "The point is outside the triangle." << std::endl;
		return ( 0 );
	}
}
