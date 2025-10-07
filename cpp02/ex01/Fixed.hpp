#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed{
	private:
		int point;
		static const int number = 8;
	public:
		Fixed();
		Fixed(const Fixed& input);
		Fixed& operator=(const Fixed& input);
		Fixed( int value );
		Fixed( float value );
		float toFloat() const;
		int toInt() const;
		int getRawBits() const;
		void setRawBits(int input);
		~Fixed();
};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif