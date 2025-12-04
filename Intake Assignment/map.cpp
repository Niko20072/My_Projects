#include "map.h"

namespace Tmpl8
{
	void Map::DrawTile(Surface* screen, int tx, int ty, int x, int y)
	{
		int TileStartX = 0; // starting point in tile
		int TileStartY = 0;
		int TileSizeX = TileSize; // size of tile to draw
		int TileSizeY = TileSize;

		// clip tile to screen boundaries (up left)
		if (x < 0) TileStartX = -x, TileSizeX -= TileStartX, x = 0;
		if (y < 0) TileStartY = -y, TileSizeY -= TileStartY, y = 0;

		// clip tile to screen boundaries (down right)
		if (x + TileSizeX > ScreenWidth) TileSizeX = ScreenWidth - x;
		if (y + TileSizeY > ScreenHeight) TileSizeY = ScreenHeight - y;

		// if tile not on the screen -> skip drawing
		if (TileSizeX <= 0 || TileSizeY <= 0) return;

		Pixel* src = tiles.GetBuffer() + (tx * TileSize) + (ty * TileSize) * MapSize; // 768 = tile size
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
				int tx = map[y][x * 3] - 'a';
				int ty = map[y][x * 3 + 1] - 'a';
				DrawTile(screen, tx, ty, x * TileSize - cameraX, y * TileSize - cameraY);
			}
		}
	}

	int Map::cameraX = 0;
	int Map::cameraY = 0;
};