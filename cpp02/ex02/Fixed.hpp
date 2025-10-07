#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed{
	private:
		int point;
		static const int number = 8;
	public:
		Fixed();
		Fixed( const Fixed& input );
		Fixed& operator=( const Fixed& input );
		Fixed( int value);
		Fixed( float value );
		int getRawBits() const;
		void setRawBits( const int input );
		float toFloat() const;
		int toInt() const;
	
		bool operator>(const Fixed& other) const;
		bool operator<(const Fixed& other) const;
		bool operator>=(const Fixed& other) const;
		bool operator<=(const Fixed& other) const;
		bool operator==(const Fixed& other) const;
		bool operator!=(const Fixed& other) const;
		Fixed& operator++();
		Fixed operator++( int );
		Fixed& operator--();
		Fixed operator--( int );
		Fixed operator+( const Fixed& input ) const;
		Fixed operator-( const Fixed& input ) const;
		Fixed operator*( const Fixed& input ) const;
		Fixed operator/( const Fixed& input ) const;
		static Fixed& min( Fixed& a, Fixed& b);
		static const Fixed& min( const Fixed& a, const Fixed& b );
		static Fixed& max( Fixed&a, Fixed& b);
		static const Fixed& max( const Fixed& a, const Fixed& b );
		~Fixed();
};

std::ostream& operator<<( std::ostream& os, const Fixed& obj );

#endif