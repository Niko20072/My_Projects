#include "inventory.h"

namespace Tmpl8
{
	bool Inventory::isopen = false;
	Inventory::Inventory( int x, int y) : x(x), y(y) 
	{
	}
	void Inventory::Draw(Surface* screen, int x, int y)
	{
		inventory.Draw(screen, x, y);
	}
};