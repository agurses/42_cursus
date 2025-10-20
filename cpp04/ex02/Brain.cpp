#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain( const Brain& input)
{
	std::cout << "Brain copy constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		ideas[i] = input.ideas[i];
}

Brain& Brain::operator=( const Brain& input)
{
	std::cout << "Brain assignment operator called." << std::endl;
	if (this != &input)
	{
		for(int i = 0; i < 100; i++)
			ideas[i] = input.ideas[i];
	}
	return *this;
}

Brain::~Brain()
{
	std::cout << "Brain deconstructor called." << std::endl;
}


void Brain::setIdeas( int index, const std::string& idea )
{
	if (index >= 0 && index < 100)
		ideas[index] = idea;
}

std::string Brain::getIdeas( int index )
{
	if (index >= 0 && index < 100)
		return ideas[index];
	else
		return "";
}
