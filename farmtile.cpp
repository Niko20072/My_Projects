#include "farmtile.h"
#include "input.h"
#include "wateringCan.h"
#include "inventory.h"
#include "map.h"
#include "camera.h"
#include "player.h"


namespace Tmpl8
{
	FarmTile::FarmTile(float x, float y, WateringCan& wa, Inventory& inv, Camera& cam, Player& pl) : farmTileX(x * Map::TileSize), farmTileY(y * Map::TileSize), wateringCan(wa), inventory(inv), camera(cam), player(pl), farmTile(std::make_unique<Sprite>(new Surface("assets/tiles.png"), 3)), hover(std::make_unique<Sprite>(new Surface("assets/tiles_hover.png"), 1)) {}
	void FarmTile::Draw(Surface* screen)
	{
		farmTile->Draw(screen, static_cast<int>(farmTileX - camera.getCameraX()), static_cast<int>(farmTileY - camera.getCameraY()));
	}
	void FarmTile::DrawHover(Surface* screen, float mouseWorldX, float mouseWorldY)
	{
		bool checkHover = mouseWorldX >= farmTileX && mouseWorldX < farmTileX + Map::TileSize && mouseWorldY >= farmTileY && mouseWorldY < farmTileY + Map::TileSize;
		if (checkHover)
			hover->Draw(screen, static_cast<int>(farmTileX - camera.getCameraX()), static_cast<int>(farmTileY - camera.getCameraY()));
	}
	void FarmTile::Update(float mouseWorldX, float mouseWorldY) //add deltatime here
	{
		// Tile rectangle
		bool checkHover = mouseWorldX >= farmTileX && mouseWorldX < farmTileX + Map::TileSize && mouseWorldY >= farmTileY && mouseWorldY < farmTileY + Map::TileSize;
		bool tileInReach = player.getReachX1() < farmTileX + Map::TileSize && player.getReachX2() > farmTileX && player.getReachY1() < farmTileY + Map::TileSize && player.getReachY2() > farmTileY;

		// Click
		if (Input::GetMouseButtonPressed(1) && checkHover && tileInReach)
			clicked = true;
		//else
		//	clicked = false; //why is this not working
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
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 2, 0, inventory, camera);
			if (plantType == 1) // Moonleaf
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 2, 3, inventory, camera);
			if (plantType == 2) // Emberroot
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 3, 6, inventory, camera);
			if (plantType == 3) // Frostmint
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 3, 10, inventory, camera);
			if (plantType == 4) // Nightshade Berry
				plant = std::make_unique<Plant>(farmTileX, farmTileY, 4, 14, inventory, camera);
			planted = true;
			time = 10; // Set time to a high value to prevent "Not ready!" message from showing immediately after planting
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
	void FarmTile::DrawPlant(Surface* screen, float deltaTime)
	{
		if (planted) // avoid null pointer access
		{
			plant->Draw(screen);
			//std::cout << time << std::endl;
			if (!plant->getGrown() && clicked && !wateringCan.getState())
				time = 0;
			if (time <= 2)
			{
				time += deltaTime;
				screen->PrintScaled("Not ready!", static_cast<int>(farmTileX - camera.getCameraX() - 25), static_cast<int>(farmTileY - camera.getCameraY() - 20), 2, 2, 0xffff00);
			}
		}
			
	}
};