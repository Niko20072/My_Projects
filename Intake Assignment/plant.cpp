#include "plant.h"

namespace Tmpl8
{
	

	Plant::Plant(float x, float y, int harvestDay, int frame, int tileNumber, Inventory& inv) : x(x), y(y), harvestDay(harvestDay), frame(frame), tileNumber(tileNumber), inventory(inv), plant(std::make_unique<Sprite>(new Surface("assets/plant.png"), 20))
	{
		FarmTile::farmTiles[tileNumber].Clicked(); // Mark the corresponding farm tile as clicked
	}
	void Plant::Draw(Surface* screen)
	{
		plant->SetFrame(frame);
		plant->Draw(screen, x - Map::cameraX, y - Map::cameraY - 10);
	}
	void Plant::NextDay()
	{
		if (alive)
		{
			daysPassed++;
			if (FarmTile::farmTiles[tileNumber].getWatered()) // check if the plant is watered
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
		if ((grown || !alive) && FarmTile::farmTiles[tileNumber].getClicked())
		{
			harvested = true;
			grown = false; // prevent multiple harvesting
			alive = true; // prevent multiple harvesting
			FarmTile::farmTiles[tileNumber].setIsClicked(false);
			FarmTile::farmTiles[tileNumber].setFrame(0);
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
};
