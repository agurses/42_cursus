#include "Zombie.hpp"

int main()
{
	Zombie *x;
	std::string name = "Foo";

	x = newZombie(name);
	x->announce();
	delete x;
	
	randomChump(name);
	return (0);
}
