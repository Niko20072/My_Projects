#include "farmtile.h"

namespace Tmpl8
{
	/*
	FarmTile::FarmTile(Surface* screen)
	{
		for (int y = 7; y <= 31; y++)
		{
			for (int x = 2; x <= 29; x++)
			{
				WetFarmTile.Draw(screen, x * Map::TileSize - Map::cameraX, y * Map::TileSize - Map::cameraY);
			}
		}
		for (int x = 4; x <= 29; x++)
		{
				WetFarmTile.Draw(screen, x * Map::TileSize - Map::cameraX, 32 * Map::TileSize - Map::cameraY);
		}
		for (int y = 7; y <= 27; y++)
		{
			for (int x = 30; x <= 33; x++)
			{
				WetFarmTile.Draw(screen, x * Map::TileSize - Map::cameraX, y * Map::TileSize - Map::cameraY);
			}
		}
	}*/
	std::vector<FarmTile> FarmTile::farmTiles;
	FarmTile::FarmTile(float x,float y) : farmTileX(x * Map::TileSize), farmTileY(y * Map::TileSize), farmTile(std::make_unique<Sprite>(new Surface("assets/tiles2.png"), 6)) {}
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
		if (clicked && WateringCan::wateringCan)
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
};