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
	void Plant::NextDay()
	{
		if (alive)
		{
			daysPassed++;
			if (watered) // check if the plant is watered
			{
				if (daysPassed <= harvestDay)
					frame++;
				if (daysPassed >= harvestDay && !harvested)
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
			inventory.addContSunblossom();
		if (frame == 5) // Moonleaf
			inventory.addContMoonleaf();
		if (frame == 9) // Emberroot
			inventory.addContEmberroot();
		if (frame == 13) // Frostmint
			inventory.addContFrostmint();
		if (frame == 18) // Berry
			inventory.addContBerry();
	}
	void Plant::Update()
	{
		harvested = true;
		grown = false; // prevent multiple harvesting
		alive = true; // prevent multiple harvesting
		Collect();
	}
};
