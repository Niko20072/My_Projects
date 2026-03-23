#include "farmtile.h"
#include "input.h"
#include "wateringCan.h"
#include "inventory.h"
#include "map.h"
#include "camera.h"
#include "player.h"



namespace Tmpl8
{
	FarmTile::FarmTile(float x, float y, Player& pl, Camera& cam) : farmTileX(x * Map::TileSize), farmTileY(y * Map::TileSize), player(pl), camera(cam), wateringCan(player.pWateringCan()), inventory(player.pInventory()), farmTile(std::make_unique<Sprite>(new Surface("assets/image/tiles.png"), 3)), hover(std::make_unique<Sprite>(new Surface("assets/image/tiles_hover.png"), 1))
	{
		// Load Audio
		itemCollect.loadMusic("assets/audio/itempickup.mp3");
		itemCollect.setVolume(2.2f);
	}
	bool FarmTile::getPlanted() 
	{ 
		return planted; 
	}
	bool FarmTile::getClicked() 
	{ 
		return clicked; 
	}
	void FarmTile::setClicked(bool state) 
	{
		clicked = state; 
	}
	void FarmTile::setWatered(bool state) 
	{
		watered = state; 
	}
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
	void FarmTile::Update(float mouseWorldX, float mouseWorldY)
	{
		// Tile rectangle
		bool checkHover = mouseWorldX >= farmTileX && mouseWorldX < farmTileX + Map::TileSize && mouseWorldY >= farmTileY && mouseWorldY < farmTileY + Map::TileSize;
		bool tileInReach = player.getReachX1() < farmTileX + Map::TileSize && player.getReachX2() > farmTileX && player.getReachY1() < farmTileY + Map::TileSize && player.getReachY2() > farmTileY;

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
			time = 10; // Set time to 10 to prevent "Not ready!" message from showing immediately after planting
		}
	}
	void FarmTile::DeletePlant()
	{
		plant = nullptr;
		planted = false;
	}
	void FarmTile::CollectPlant(float deltaTime)
	{
		if (planted) // avoid null pointer access
		{
			if ((plant->getGrown() || !plant->getAlive()) && clicked && !wateringCan.getState()) // Check if the plant is ready for harvest or dead, and the tile has been clicked
			{
				itemCollect.play();
				plant->Collect();
				DeletePlant();
			}
			else if (!plant->getGrown() && clicked && !wateringCan.getState()) // If the plant is not ready and the tile has been clicked, start accumulating time
				time = 0;
			if (time <= 2)
			{
				time += deltaTime;
				printNotReady = true;
			}
			else
				printNotReady = false;
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
		{
			plant->Draw(screen);
			if(printNotReady)
				screen->PrintScaled("Not ready!", static_cast<int>(farmTileX - camera.getCameraX() - 25), static_cast<int>(farmTileY - camera.getCameraY() - 20), 2, 2, 0xffff00);
		}
			
	}
};