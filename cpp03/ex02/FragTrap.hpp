#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
	public:
		FragTrap();
		FragTrap( const std::string& name );
		FragTrap( const FragTrap& input );
		FragTrap& operator=( const FragTrap& other );
		~FragTrap();
		void highFivesGuys(void);
		void attack(const std::string& target);
};

#endif