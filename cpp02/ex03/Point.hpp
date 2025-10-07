#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point{
	private:
		const Fixed x;
		const Fixed y;
	public:
		Point();
		Point( float str, float str2);
		Point( const Point& input );
		Point& operator=(const Point& input);
		~Point();
		const Fixed& getX() const;
		const Fixed& getY() const;
};

bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif