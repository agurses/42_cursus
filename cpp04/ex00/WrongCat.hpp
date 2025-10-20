#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal{
	public:
		WrongCat();
		WrongCat( const std::string& input);
		WrongCat( const WrongCat& input );
		WrongCat& operator=( const WrongCat& input );
		~WrongCat();
		void makeSound() const;
};

#endif