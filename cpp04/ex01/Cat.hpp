#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal{
	private:
		Brain* brain;
	public:
		Cat();
		Cat( const std::string& input );
		Cat( const Cat& input );
		Cat& operator=( const Cat& input );
		~Cat();

		void makeSound() const;
};


#endif