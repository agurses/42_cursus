#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed{
	private:
		int point;
		static const int number = 8;
	public:
		Fixed();
		Fixed( int input );
		Fixed( float value );
		Fixed( const Fixed& input );
		Fixed& operator=( const Fixed& input);
		~Fixed();
		float toFloat() const;
		int toInt() const;
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};

#endif