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
	Plant::Plant(float x, float y, int harvestDay, int frame, int tileNumber) : x(x), y(y), harvestDay(harvestDay), frame(frame), tileNumber(tileNumber), sun(std::make_unique<Sprite>(new Surface("assets/plants1.png"), 19)) 
	{
		FarmTile::farmTiles[tileNumber].Clicked(); // Mark the corresponding farm tile as clicked
	}

	void Plant::Draw(Surface* screen)
	{
		sun->SetFrame(frame);
		sun->Draw(screen, x - Map::cameraX, y - Map::cameraY);
	}
	void Plant::NextDay()
	{
		daysPassed++;
		if (daysPassed <= harvestDay)
			frame++;
		if (daysPassed >= harvestDay && !harvested)
			grown = true;
	}
	void Plant::Collect()
	{
		if (frame == 2) // Sunblossom
			Inventory::contSunblossom++;
		if (frame == 5) // Moonleaf
			Inventory::contMoonleaf++;
		if (frame == 9) // Emberroot
			Inventory::contEmberroot++;
		if (frame == 13) // Frostmint
			Inventory::contFrostmint++;
		if (frame == 18) // Berry
			Inventory::contBerry++;
	}
	void Plant::Grown()
	{
		if (grown && FarmTile::farmTiles[tileNumber].clicked)
		{
			harvested = true;
			grown = false; // prevent multiple harvesting
			FarmTile::farmTiles[tileNumber].isClicked = false;
			FarmTile::farmTiles[tileNumber].frame = 0;
			Collect();
		}
	}
	
	
	void Plant::Delete()
	{
		//eroare daca plantele cresc in zile diferite
		/*
		{
			Plant::plants.erase(std::remove_if(Plant::plants.begin(), Plant::plants.end(), [](const Plant& p)
				{
					return p.grown == true; // conditia de sters
				}), Plant::plants.end());
		}*/
	}
	void DrawAll()
	{
		
	}
};