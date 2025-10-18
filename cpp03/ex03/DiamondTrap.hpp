#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap, virtual public ClapTrap{
	private:
	   std::string name;
	public:
		DiamondTrap();
		DiamondTrap( std::string input );
		DiamondTrap( const DiamondTrap& input );
		DiamondTrap& operator=( const DiamondTrap& input );
		~DiamondTrap();
		void whoAmI();
		void attack( const std::string& target );
		void getAll();
};

#endif