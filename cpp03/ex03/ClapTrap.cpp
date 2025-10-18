#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
	: name(""), hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap( const std::string& name )
	: name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "ClapTrap " << name << " constructor called" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap deconstructor called" << std::endl;
}

ClapTrap::ClapTrap( const ClapTrap& input)
{
	std::cout << "ClapTrap Copy constructor called" << std::endl;
	name = input.name;
	hitPoints = input.hitPoints;
	energyPoints = input.energyPoints;
	attackDamage = input.attackDamage;
}

ClapTrap& ClapTrap::operator=( const ClapTrap& input )
{
	std::cout << "ClapTrap Copy assignment operator called" << std::endl;
	if (this != &input)
	{
		name = input.name;
		hitPoints = input.hitPoints;
		energyPoints = input.energyPoints;
		attackDamage = input.attackDamage;
	}
	return (*this);
}

void ClapTrap::attack(const std::string& target)
{
	if (hitPoints > 0 && energyPoints > 0)
	{
		energyPoints--;
		std::cout << "ClapTrap " << name << " attacks " << target
				  << ", causing " << attackDamage << " points of damage!" << std::endl;
	}
	else if (hitPoints == 0)
	{
		std::cout << "ClapTrap " << name << " cannot attack: no hit points left!" << std::endl;
	}
	else if (energyPoints == 0)
	{
		std::cout << "ClapTrap " << name << " cannot attack: no energy points left!" << std::endl;
	}
}
void ClapTrap::takeDamage(unsigned int amount)
{
	if (hitPoints >= amount)
	{
		std::cout << "ClapTrap " << name << " takes " << amount << " points of damage!" << std::endl;
		hitPoints -= amount;
	}
	else if (amount > hitPoints)
	{
		std::cout << "ClapTrap " << name << " takes " << amount << " points of damage!" << std::endl;
		hitPoints = 0;
	}
	if (hitPoints == 0)
	{
		std::cout << "ClapTrap " << name << " needs repair." << std::endl;
	}
	
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (hitPoints > 0 && energyPoints > 0)
	{
		std::cout << "ClapTrap " << name << " is repaired for " << amount << " hit points!" << std::endl;
		energyPoints--;
		hitPoints += amount;
	}
	else
	{
		std::cout << "ClapTrap " << name << " cannot repair itself!" << std::endl;
	}
}

unsigned int ClapTrap::getAttackDamage()
{
	return (attackDamage);
}
