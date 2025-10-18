#include "ClapTrap.hpp"

int main()
{
	ClapTrap robot1("Alpha");
	ClapTrap robot2("Beta");

	robot1.attack("Bravo");
	robot2.takeDamage(robot1.getAttackDamage());

	robot2.attack("Alpha");
	robot1.takeDamage(robot2.getAttackDamage());

	robot1.beRepaired(3);
	robot1.attack("Bravo");

	return (0);
}
