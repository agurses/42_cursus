#include "Point.hpp"

int main()
{
	Fixed a(4);
	Fixed b(0.222f);

	std::cout << a.toFloat() << std::endl;
	std::cout << a.toInt() << std::endl;
	std::cout << a.getRawBits() << std::endl;

	std::cout << b.toFloat() << std::endl;
	std::cout << b.toInt() << std::endl;
	std::cout << b.getRawBits() << std::endl;

	Point c(100, 0);
	Point d(0, 0);
	Point e(0, 100);
	Point f(5, 3);
	std::cout << bsp(c, d, e, f) << std::endl;
}
