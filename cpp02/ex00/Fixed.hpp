#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>

class Fixed{
	private:
		int point;
		static const int number = 8;
	public:
		Fixed();
		Fixed(const Fixed& input);
		Fixed& operator=(const Fixed& input);
		~Fixed();
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};

#endif