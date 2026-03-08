#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base()
{

}

Base *generate(void)
{
	int a = std::rand();

	if ((a % 3) == 0)
		return new A;
	else if (a % 3 == 1)
		return new B;
	else if (a % 3 == 2)
		return new C;
	
	return NULL;
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "type A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "type B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "type C" << std::endl;
	else
		std::cout << "Unkonwn type cast" << std::endl; 
}

void identify(Base& p)
{
	try {
		A& a = dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
		(void)a;
		return;
    } catch (std::bad_cast&) {}

	try {
		B& b = dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
		(void)b;
        return;
    } catch (std::bad_cast&) {}

	try {
		C& c = dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
		(void)c;
        return;
    } catch (std::bad_cast&) {}

	std::cout << "Unknown type cast" << std::endl;
}
