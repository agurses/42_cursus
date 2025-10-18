#include "FragTrap.hpp"

FragTrap::FragTrap()
	: ClapTrap()
{
	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap( const std::string& name )
	: ClapTrap(name)
{
	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	std::cout << "FragTrap " << this->name << " constructor called" << std::endl;
}

FragTrap::FragTrap( const FragTrap& input )
	: ClapTrap(input)
{
	std::cout << "FragTrap Copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=( const FragTrap& other )
{
	ClapTrap::operator=( other );
	std::cout << "FragTrap Copy assignment operator called" << std::endl;
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap deconstructor called" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap said. Give me a high five" << std::endl; 
}

void FragTrap::attack(const std::string& target)
{
	if (hitPoints > 0 && energyPoints > 0)
	{
		energyPoints--;
		std::cout << "FragTrap " << name << " attacks " << target
				  << ", causing " << attackDamage << " points of damage!" << std::endl;
	}
	else if (hitPoints == 0)
	{
		std::cout << "FragTrap " << name << " cannot attack: no hit points left!" << std::endl;
	}
	else if (energyPoints == 0)
	{
		std::cout << "FragTrap " << name << " cannot attack: no energy points left!" << std::endl;
	}
}
