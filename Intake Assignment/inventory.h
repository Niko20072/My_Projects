#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
namespace Tmpl8
{
	class Inventory
	{
	public:
		int x, y;
		int frame;
		static bool isopen;
		static bool carisopen;
		Sprite inventory = Sprite(new Surface("assets/inv5.png"), 4);
		Inventory(int x, int y);
		void Draw(Surface* screen, int x, int y);
		void SetFrame(int frame);
		void  InventoryIsOpen(Surface* screen);
	};
};