#include <iostream>
#include <string>

int main()
{
	std::string x = "HI THIS IS BRAIN";
	std::string* stringPtr = &x;
	std::string& stringREF = x;

	std::cout << &x << std::endl;
	std::cout << stringPtr << std::endl;
	std::cout << &stringREF << std::endl;

	std::cout << x << std::endl;
	std::cout << *stringPtr << std::endl;
	std::cout << stringREF << std::endl;
	return (0);
}
