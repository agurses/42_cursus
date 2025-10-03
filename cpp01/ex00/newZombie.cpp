#include "Zombie.hpp"

Zombie* newZombie( std::string name )
{
    Zombie* x = new Zombie(name);
    return (x);
}
