#include "farmtile.h"
#include "input.h"
#include "worldState.h"
#include "wateringCan.h"
#include "inventory.h"


namespace Tmpl8
{
	FarmTile::FarmTile(float x,float y, WateringCan& wa, Inventory& inv) : farmTileX(x * WorldState::mapTileSize), farmTileY(y * WorldState::mapTileSize), wateringCan(wa), inventory(inv), farmTile(std::make_unique<Sprite>(new Surface("assets/tiles.png"), 3)), hover(std::make_unique<Sprite>(new Surface("assets/tiles_hover.png"), 1)) {}
	void FarmTile::Draw(Surface* screen)
	{
		farmTile->Draw(screen, static_cast<int>(farmTileX - WorldState::cameraX), static_cast<int>(farmTileY - WorldState::cameraY));
	}
	void FarmTile::DrawHover(Surface* screen)
	{
		bool checkHover = WorldState::mouseWorldX >= farmTileX && WorldState::mouseWorldX < farmTileX + WorldState::mapTileSize && WorldState::mouseWorldY >= farmTileY && WorldState::mouseWorldY < farmTileY + WorldState::mapTileSize;
		if (checkHover)
			hover->Draw(screen, static_cast<int>(farmTileX - WorldState::cameraX), static_cast<int>(farmTileY - WorldState::cameraY));
	}
	void FarmTile::Update()
	{
		// Tile rectangle
		bool checkHover = WorldState::mouseWorldX >= farmTileX && WorldState::mouseWorldX < farmTileX + WorldState::mapTileSize && WorldState::mouseWorldY >= farmTileY && WorldState::mouseWorldY < farmTileY + WorldState::mapTileSize;
		bool tileInReach = WorldState::reachX1 < farmTileX + WorldState::mapTileSize && WorldState::reachX2 > farmTileX && WorldState::reachY1 < farmTileY + WorldState::mapTileSize && WorldState::reachY2 > farmTileY;

		// Click
		if (Input::GetMouseButtonPressed(1) && checkHover && tileInReach)
			clicked = true;
		if (clicked && wateringCan.getState())
			watered = true;
		// Hover & state logic
		if (watered)
			frame = 2;   // idle wet tile
		else if (planted)
			frame = 1;   // idle dry tile
		else
			frame = 0;   // default tile

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
			if ((plant->getGrown() || !plant->getAlive()) && clicked && !wateringCan.getState()) // Check if the plant is ready for harvest or dead, and the tile has been clicked
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