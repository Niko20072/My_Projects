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
	void FarmTile::Clicked()
	{
		isClicked = true;
		frame = 2;
	}
	void FarmTile::Update(float x, float y)
	{
		// Tile rectangle
		bool tileRectangle = WorldState::worldX >= x && WorldState::worldX < x + Map::TileSize && WorldState::worldY >= y && WorldState::worldY < y + Map::TileSize;
		bool tileInReach = WorldState::reachX1 < x + Map::TileSize && WorldState::reachX2 > x && WorldState::reachY1 < y + Map::TileSize && WorldState::reachY2 > y;

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
		else if (isClicked)
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
			Clicked(); // Mark the tile as clicked when planting
			plant = nullptr;
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
	void FarmTile::UpdatePlant()
	{
		if (planted)
		{
			if ((plant->getGrown() || !plant->getAlive()) && clicked)
			{
				plant->Update();
				isClicked = false; // Reset click state after harvesting
				frame = 0; // Reset tile frame after harvesting
			}
			if (plant->getHarvested())
				DeletePlant();
		}
	}
	void FarmTile::NextDayPlant()
	{
		if (planted)
		{
			plant->setWatered(watered);
			plant->NextDay();
		}
		
	}
	void FarmTile::DrawPlant(Surface* screen)
	{
		if (planted)
			plant->Draw(screen);
	}
};