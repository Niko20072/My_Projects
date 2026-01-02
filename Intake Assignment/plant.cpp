#include "plant.h"

namespace Tmpl8
{
	/*
	Plant::Plant(std::string plantName)
	{
		name = plantName;
		daysPassed = 0;
		grown = false;

		if (name == "Sunblossom")
			harvestDay = 3;
		else if (name == "Moonleaf")
			harvestDay = 2;
		else if (name == "Emberroot")
			harvestDay = 3;
		else if (name == "Frostmint")
			harvestDay = 2;
		else if (name == "Berry")
			harvestDay = 4;
		else
			harvestDay = 0;
	}*/
	Plant::Plant(float x, float y) : x(x), y(y) {}

	void Plant::Draw(Surface* screen)
	{
		sun->Draw(screen, x - Map::cameraX, y - Map::cameraY);
	}
	void Plant::NextDay()
	{
		daysPassed++;
		if (grown)
		{
			return;
		}
			
		if (daysPassed >= harvestDay)
			grown = true;
	}
};