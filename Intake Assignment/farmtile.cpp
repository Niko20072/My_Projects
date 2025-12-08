#include "farmtile.h"
#include "map.h"

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
	FarmTile::FarmTile(int x,int y)
	{
		farmTileX = x;
		farmTileY = y;
		WetFarmTile = Sprite(new Surface("assets/tileset1.png"), 2);
	}
	//or : farmTileX(x), farmTileY(y), WetFarmTile(new Surface("assets/tileset1.png"), 2)

	void FarmTile::Draw(Surface* screen)
	{
		WetFarmTile.Draw(screen, farmTileX - Map::cameraX, farmTileY - Map::cameraY);
	}
	void FarmTile::SetFrame(int frame)
	{
		WetFarmTile.SetFrame(1);
	}

};