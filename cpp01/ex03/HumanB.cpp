#include "HumanB.hpp"

HumanB::HumanB(std::string name)
	: weapon(nullptr)
{
	this->name = name;
}

void    HumanB::setWeapon(Weapon& weapon)
{
	this->weapon = &weapon;
}

void    HumanB::attack()
{
	if (this->weapon)
		std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
	else
		std::cout << this->name << " has no weapon" << std::endl;
}
