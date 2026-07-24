#include "easyfind.hpp"

int main()
{
	std::vector<int> intCont;

	intCont.push_back(4);
	intCont.push_back(12);
	intCont.push_back(24);
	intCont.push_back(2);

	std::vector<int>::iterator result = easyfind(intCont, 12);

	if (result != intCont.end())
		std::cout << "Result find ------ Pass" << std::endl;
	else
		std::cout << "Result wrong" << std::endl;

	result = easyfind(intCont, 14);

	if (result == intCont.end())
		std::cout << "Result wrong ------ Pass" << std::endl;
	else
		std::cout << "Result find" << std::endl;
	
	intCont.push_back(12);

	result = easyfind(intCont, 12);

	if (result == intCont.begin() + 1)
		std::cout << "First result find ------ Pass" << std::endl;
	else
		std::cout << "First result wrong" << std::endl;
//---------------------------------------------------------------//

	std::cout << std::endl;

	std::list<int> listCont;

	listCont.push_back(4);
	listCont.push_back(12);
	listCont.push_back(24);
	listCont.push_back(2);

	std::list<int>::iterator resultlist = easyfind(listCont, 24);

	if (resultlist != listCont.end())
		std::cout << "Resultlist find ------ Pass" << std::endl;
	else
		std::cout << "Resultlist wrong" << std::endl;

	resultlist = easyfind(listCont, 22);

	if (resultlist == listCont.end())
		std::cout << "Resultlist wrong ------ Pass" << std::endl;
	else
		std::cout << "Resultlist find" << std::endl;
//---------------------------------------------------------------//

	std::cout << std::endl;

	std::deque<int> deqCont;
	
	deqCont.push_back(4);
	deqCont.push_back(12);
	deqCont.push_back(24);
	deqCont.push_back(2);

	std::deque<int>::iterator deqresult = easyfind(deqCont, 2);

	if (deqresult != deqCont.end())
		std::cout << "Deqresult find ------ Pass" << std::endl;
	else
		std::cout << "Deqresult wrong" << std::endl;

	deqresult = easyfind(deqCont, 22);

	if (deqresult == deqCont.end())
		std::cout << "Deqresult wrong ------ Pass" << std::endl;
	else
		std::cout << "Deqresult find" << std::endl;

	std::cout << std::endl;

	std::deque<int> deqEmpty;

	std::deque<int>::iterator empResult = easyfind(deqEmpty, 22);

	if (empResult != deqEmpty.end())
		std::cout << "There is a problem!!" << std::endl;
	else
		std::cout << "This is Empty ------ Pass" << std::endl;

	return 0;
}