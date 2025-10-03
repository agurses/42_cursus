#include "Zombie.hpp"

int main()
{
	Zombie* x;
	x = zombieHorde(7, "Foo");

	for(int i = 0; i < 7; i++)
	{
		x[i].announce();
	}
	delete[] x;
	return (0);
}
