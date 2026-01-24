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
	FarmTile::FarmTile(float x,float y) : farmTileX(x * Map::TileSize), farmTileY(y * Map::TileSize){}
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
	void FarmTile::Update(bool leftClicked, float x, float y, float worldX, float worldY, float reachX1, float reachX2, float reachY1, float reachY2)
	{
		// Tile rectangle
		bool tileRectangle = worldX >= x && worldX < x + Map::TileSize && worldY >= y && worldY < y + Map::TileSize;
		bool tileInReach = reachX1 < x + Map::TileSize && reachX2 > x && reachY1 < y + Map::TileSize && reachY2 > y;

		// Click
		if (leftClicked && tileRectangle && tileInReach)
		{
			leftClicked = false; // Reset left click state to avoid multiple clicks
			clicked = true;
		}
		
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