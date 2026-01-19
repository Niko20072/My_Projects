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
	std::vector<Plant> Plant::plants;   
	Plant::Plant(float x, float y, int harvestDay, int frame, int tileNumber) : x(x), y(y), harvestDay(harvestDay), frame(frame), sun(std::make_unique<Sprite>(new Surface("assets/plants1.png"), 19)) 
	{
		FarmTile::farmTiles[tileNumber].Clicked(); // Mark the corresponding farm tile as clicked
	}

	void Plant::Draw(Surface* screen)
	{
		sun->SetFrame(frame);
		sun->Draw(screen, x - Map::cameraX, y - Map::cameraY);
	}
	void Plant::Grow()
	{
		daysPassed++;
		if (daysPassed <= harvestDay)
		{
			frame++;
		}
		if (daysPassed > harvestDay)
			grown = true;
	}
};