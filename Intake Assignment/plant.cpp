#include "plant.h"

namespace Tmpl8
{
	Plant::Plant(float x, float y, int harvestDay, int frame, Inventory& inv) : x(x), y(y), harvestDay(harvestDay), frame(frame), inventory(inv)
	{

	}
	void Plant::Draw(Surface* screen)
	{
		plant.SetFrame(frame);
		plant.Draw(screen, x - Map::cameraX, y - Map::cameraY - 10);
	}
	void Plant::Update()
	{
		if (alive)
		{
			daysPassed++;
			if (watered) // check if the plant is watered
			{
				if (daysPassed <= harvestDay)
					frame++;
				if (daysPassed >= harvestDay)
					grown = true;
			}
			else
			{
				alive = false;
				frame = 19; // withered plant frame
			}
		}
	}
	void Plant::Collect()
	{
		if (frame == 2) // Sunblossom
			inventory.AddItem(Inventory::Item::Sunblossom);
		if (frame == 5) // Moonleaf
			inventory.AddItem(Inventory::Item::Moonleaf);
		if (frame == 9) // Emberroot
			inventory.AddItem(Inventory::Item::Emberroot);
		if (frame == 13) // Frostmint
			inventory.AddItem(Inventory::Item::Frostmint);
		if (frame == 18) // Berry
			inventory.AddItem(Inventory::Item::Berry);
	}
};
