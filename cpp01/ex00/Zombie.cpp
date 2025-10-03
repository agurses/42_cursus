#include "Zombie.hpp"

Zombie::Zombie (std::string name)
    : name(name)
{
}

Zombie::~Zombie()
{
    std::cout << this->name << " : Zombie is dead"<< std::endl;
}

void    Zombie::announce()
{
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
