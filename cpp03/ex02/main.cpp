#include "ClapTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    FragTrap robot1("Alpha");
    FragTrap robot2("Beta");

    robot1.attack("Bravo");
    robot2.takeDamage(robot1.getAttackDamage());

    robot2.beRepaired(5);

    robot2.attack("Alpha");
    robot1.takeDamage(robot2.getAttackDamage());

    robot1.beRepaired(3);

    robot1.highFivesGuys();

    return (0);
}
