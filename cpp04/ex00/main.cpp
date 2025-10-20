#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;

	std::cout << "-----------" << std::endl;

	Animal* k = new Dog();
	k->makeSound();

	Dog x;
	x.makeSound();

	Animal b;
	b = Dog();
	b.makeSound();
	std::cout << b.getType() << std::endl;

	delete k;
	std::cout << "-----------" << std::endl;


	WrongAnimal *a = new WrongCat();
	a->makeSound();

	WrongCat *y = new WrongCat();
	y->makeSound();
	delete a;
	delete y;
	return 0;
}
