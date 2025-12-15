#include "farmtile.h"
#include "map.h"
#include "inventory.h"
#include "game.h"


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

	FarmTile::FarmTile(int x,int y) : farmTileX(x * Map::TileSize), farmTileY(y * Map::TileSize){}
	void FarmTile::Draw(Surface* screen)
	{
		farmTile->Draw(screen, farmTileX - Map::cameraX, farmTileY - Map::cameraY);
	}
	void FarmTile::SetFrame(int frame)
	{
		farmTile->SetFrame(frame);
	}
	void FarmTile::Update(int x, int y, int worldX, int worldY, int reachX1, int reachX2, int reachY1, int reachY2, bool& clicked)
	{
		// Tile rectangle
		bool tileRectangle = worldX >= x && worldX < x + Map::TileSize && worldY >= y && worldY < y + Map::TileSize;
		bool tileInReach = reachX1 < x + Map::TileSize && reachX2 > x && reachY1 < y + Map::TileSize && reachY2 > y;

		//click
		if (!isClicked && GetAsyncKeyState(VK_LBUTTON) && tileRectangle && tileInReach)
		{
			isClicked = true;
			clicked = true;
			frame = 2;
		}
		//hover over clicked tile
		else if (isClicked && tileRectangle)
		{
			frame = 3;
		}
		else if (isClicked)
		{
			frame = 2;
		}
		//hover over normal tile
		else if (tileRectangle) //hover
		{
			frame = 1;
		}
		else //idle
			frame = 0;
		farmTile->SetFrame(frame);
	}
};