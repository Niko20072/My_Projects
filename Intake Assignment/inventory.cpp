#include "inventory.h"

namespace Tmpl8
{
	bool Inventory::isopen = false;
	bool Inventory::carisopen = false;
	int frame = 0;
	Inventory::Inventory( int x, int y) : x(x), y(y) 
	{
	}
	void Inventory::Draw(Surface* screen, int x, int y)
	{
		inventory.Draw(screen, x, y);
	}
	void Inventory::SetFrame(int frame)
	{
		inventory.SetFrame(frame);
	}
	void  Inventory::InventoryIsOpen(Surface*screen)
	{
		inventory.Draw(screen, 140, 20);
		screen->Print("Plant      x0", 270, 220, 0x0);
		screen->Print("Inventory Opened", 270, 240, 0x0);
		screen->Print("Inventory Opened", 270, 260, 0x0);
		screen->Print("Inventory Opened", 270, 280, 0x0);
		screen->Print("Inventory Opened", 270, 300, 0x0);
		screen->Print("Inventory Opened", 270, 320, 0x0);
		screen->Print("Inventory Opened", 270, 340, 0x0);
		screen->Print("Inventory Opened", 270, 360, 0x0);
		screen->Print("Inventory Opened", 270, 380, 0x0);
		screen->Print("Inventory Opened", 270, 400, 0x0);
	}
};