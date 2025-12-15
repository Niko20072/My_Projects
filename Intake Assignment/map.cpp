#include "map.h"

namespace Tmpl8
{
	int Map::cameraX = 0;
	int Map::cameraY = 0;

	bool Map::IsBlocked(int x,int y)
	{
		//Transform screen coordinates to tile coordinates
		int tx = x / TileSize;
		int ty = y / TileSize;
		//return true if tile is blocked/ false if not
		return map[ty][tx * 3 + 2] == 'X';
	}
	void Map::DrawTile(Surface* screen, int tx, int ty, int x, int y)
	{
		int TileStartX = 0; // starting point in tile
		int TileStartY = 0;
		int TileSizeX = TileSize; // size of tile to draw
		int TileSizeY = TileSize;

		// clip tile to screen boundaries (up left)
		if (x < 0)
		{
			TileStartX = -x;
			TileSizeX -= TileStartX;
			x = 0;
		}
		if (y < 0) 
		{ 
			TileStartY = -y;
			TileSizeY -= TileStartY;
			y = 0;
		}

		// clip tile to screen boundaries (down right)
		if (x + TileSizeX > ScreenWidth) TileSizeX = ScreenWidth - x;
		if (y + TileSizeY > ScreenHeight) TileSizeY = ScreenHeight - y;

		// if tile not on the screen -> skip drawing
		if (TileSizeX <= 0 || TileSizeY <= 0) return;

		Pixel* src = tiles.GetBuffer() + (tx * TileSize) + (ty * TileSize) * MapSize;
		src += TileStartX + TileStartY * MapSize;

		Pixel* dst = screen->GetBuffer() + x + y * ScreenWidth;
		for (int iy = 0; iy < TileSizeY; iy++, src += MapSize, dst += ScreenWidth)
			for (int ix = 0; ix < TileSizeX; ix++)
				dst[ix] = src[ix]; //copy pixel from tile to screen
	}
	void Map::DrawMap(Surface* screen)
	{
		for (int y = 0; y < MapHeight; y++)
		{
			for (int x = 0; x < MapWidth; x++)
			{
				int tx = map[y][x * 3] - '0';
				int ty = map[y][x * 3 + 1] - '0';
				DrawTile(screen, tx, ty, x * TileSize - cameraX, y * TileSize - cameraY);
			}
		}
	}
};