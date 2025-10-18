#include "DiamondTrap.hpp"

int main()
{
	DiamondTrap dia("firstDia");
	DiamondTrap dia2(dia);
	DiamondTrap dia3;

	dia3 = dia2;

	dia3.getAll();
	dia.whoAmI();
	dia.getAll();


	return (0);
}
