#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

/// abstract class

int main()
{
	Animal* animals[4];

	animals[0] = new Dog();
	animals[1] = new Cat();
	animals[2] = new Dog();
	animals[3] = new Cat();

	for (int i = 0; i < 4; ++i)
		animals[i]->makeSound();

	for (int i = 0; i < 4; ++i)
		delete animals[i];

	return 0;
}
