#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	Animal* a[10];
	
	for (int i = 0; i < 5; i++)
		a[i] = new Dog();

	for (int i = 5; i < 10; i++)
		a[i] = new Cat();
		
	for(int i = 9; i >= 0; i--)
		delete a[i];

	Dog x;
	x.getBrain().setIdeas( 0, "Brainzz");
	Dog y;
	y = x;
	std::cout << x.getBrain().getIdeas( 0 ) << std::endl;
	std::cout << y.getBrain().getIdeas( 0 ) << std::endl;
	y.getBrain().setIdeas( 0, "Diff" );
	std::cout << x.getBrain().getIdeas( 0 ) << std::endl;
	std::cout << y.getBrain().getIdeas( 0 ) << std::endl; 
	std::cout << "---------------" << std::endl;

	return 0;
}
