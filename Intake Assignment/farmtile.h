#pragma once
#include "surface.h"
#include "template.h"
namespace Tmpl8
{
	class FarmTile
	{
	public:
		Sprite WetFarmTile = Sprite(new Surface("assets/tileset1.png"), 2);
		int farmTileX;
		int farmTileY;
		//FarmTile(Surface* screen);
		FarmTile::FarmTile(int x, int y);
		void FarmTile::Draw(Surface* screen);
		void FarmTile::SetFrame(int frame);
	};
};