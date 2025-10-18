#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
	: ClapTrap(), ScavTrap(), FragTrap() 
{
	std::cout << "DiamondTrap default constructor called" << std::endl;
	ClapTrap::name = name + "_clap_name";
	this->name = this->ClapTrap::name;
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 30;
}

DiamondTrap::DiamondTrap( std::string input )
	:  ClapTrap(input + "_clap_name"),  ScavTrap(input), FragTrap(input)
{
	name = input;
	hitPoints = 100;
	energyPoints = 50;
	attackDamage = 30;
	std::cout << "DiamondTrap " << name << " constructor called" << std::endl;
}

DiamondTrap::DiamondTrap( const DiamondTrap& input )
	: ClapTrap(input), ScavTrap(input), FragTrap(input)
{
	name = input.name;
	hitPoints = input.hitPoints;
	energyPoints = input.energyPoints;
	attackDamage = input.attackDamage;
	std::cout << "DiamondTrap Copy constructor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=( const DiamondTrap& input )
{
	ClapTrap::operator=(input);
	name = input.name;
	hitPoints = input.hitPoints;
	energyPoints = input.energyPoints;
	attackDamage = input.attackDamage;
	std::cout << "DiamondTrap Copy assignment operator called" << std::endl;
	return (*this);
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap deconstructor called" << std::endl;
}

void DiamondTrap::whoAmI()
{
	std::cout << "DiamondTrap's name is " << name << "." << std::endl;
	std::cout << "ClapTrap's name is " << ClapTrap::name << "." << std::endl;
}
void DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::getAll()
{
	std::cout << "name: " << name << std::endl;
	std::cout << "energy: " << energyPoints << std::endl;
	std::cout << "hitpoints: " << hitPoints << std::endl;
	std::cout << "attack: " << attackDamage << std::endl;
}
