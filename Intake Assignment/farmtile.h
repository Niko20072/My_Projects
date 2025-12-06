#pragma once
#include "surface.h"
#include "template.h"
namespace Tmpl8
{
	class FarmTile
	{
	public:
		Sprite WetFarmTile = Sprite(new Surface("assets/FarmLand_Tile.png"), 1);
		int farmTileX;
		int farmTileY;
		//FarmTile(Surface* screen);
		FarmTile::FarmTile(int x, int y);
		void FarmTile::Draw(Surface* screen);
	};
};