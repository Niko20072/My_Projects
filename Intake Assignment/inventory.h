#pragma once
#include "surface.h"
#include "template.h"
namespace Tmpl8
{
	class Inventory
	{
	public:
		int x, y;
		static bool isopen;
		Sprite inventory = Sprite(new Surface("assets/inventory.png"), 1);
		Inventory(int x, int y);
		void Draw(Surface* screen, int x, int y);
	};
};