#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <iostream>

class Brain{
	private: 
		std::string ideas[100];
	public:
		Brain();
		Brain( const Brain& input);
		Brain& operator=( const Brain& input);
		~Brain();

		void setIdeas( int index, const std::string& idea );
		std::string getIdeas( int index );
};

#endif