#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
    Weapon club = Weapon("crude spiked club");
    HumanA bob("Bob", club);
    bob.attack();
    club.setType("knife");
    bob.attack();

    HumanB jim("Jim");
    jim.attack();
    jim.setWeapon(club);
    jim.attack();

    club.setType("Ak47");
    jim.setWeapon(club);
    jim.attack();

    return (0);
}
