#include "farmtile.h"

namespace Tmpl8
{
	
	FarmTile::FarmTile(float x,float y, WateringCan& wa, Inventory& inv) : farmTileX(x * Map::TileSize), farmTileY(y * Map::TileSize), wateringCan(wa), inventory(inv), farmTile(std::make_unique<Sprite>(new Surface("assets/tiles2.png"), 6)) {}
	void FarmTile::Draw(Surface* screen)
	{
		farmTile->Draw(screen, farmTileX - Map::cameraX, farmTileY - Map::cameraY);
	}
	void FarmTile::SetFrame(int frame)
	{
		farmTile->SetFrame(frame);
	}
	void FarmTile::Update()
	{
		// Tile rectangle
		bool tileRectangle = WorldState::worldX >= farmTileX && WorldState::worldX < farmTileX + Map::TileSize && WorldState::worldY >= farmTileY && WorldState::worldY < farmTileY + Map::TileSize;
		bool tileInReach = WorldState::reachX1 < farmTileX + Map::TileSize && WorldState::reachX2 > farmTileX && WorldState::reachY1 < farmTileY + Map::TileSize && WorldState::reachY2 > farmTileY;

		// Click
		if (Buttons::leftPressed && tileRectangle && tileInReach)
		{
			Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
			clicked = true;
		}
		if (clicked && wateringCan.getState())
			watered = true;
		// Hover & state logic
		if (watered)
		{
			if (tileRectangle)
				frame = 5;   // hover on wet tile
			else
				frame = 4;   // idle wet tile
		}
		else if (planted)
		{
			if (tileRectangle)
				frame = 3;   // hover on dry tile
			else
				frame = 2;   // idle dry tile
		}
		else if (tileRectangle)
			frame = 1;       // hover on default tile
		else
			frame = 0;       // default tile

		farmTile->SetFrame(frame);

	}
	void FarmTile::CreatePlant(int plantType)
	{
		if (!planted)
		{
			//plant = nullptr;
			if (plantType == 0) // Sunblossom
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 2, 0, inventory);
			if (plantType == 1) // Moonleaf
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 2, 3, inventory);
			if (plantType == 2) // Emberroot
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 3, 6, inventory);
			if (plantType == 3) // Frostmint
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 3, 10, inventory);
			if (plantType == 4) // Nightshade Berry
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 4, 14, inventory);
			planted = true;
		}
	}
	void FarmTile::DeletePlant()
	{
		plant = nullptr;
		planted = false;
	}
	void FarmTile::CollectPlant()
	{
		if (planted) // avoid null pointer access
		{
			if ((plant->getGrown() || !plant->getAlive()) && clicked) // Check if the plant is ready for harvest or dead, and the tile has been clicked
			{
				plant->Collect();
				DeletePlant();
			}
		}
	}
	void FarmTile::UpdatePlant()
	{
		if (planted) // avoid null pointer access
		{
			plant->setWatered(watered);
			plant->Update();
		}
		
	}
	void FarmTile::DrawPlant(Surface* screen)
	{
		if (planted) // avoid null pointer access
			plant->Draw(screen);
	}
};