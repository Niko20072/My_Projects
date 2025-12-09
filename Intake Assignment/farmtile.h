#pragma once
#include "surface.h"
#include "template.h"
#include <cassert>
#include <vector>

namespace Tmpl8
{
	class FarmTile
	{
	public:
		Sprite WetFarmTile = Sprite(new Surface("assets/tileset1.png"), 2);
		int farmTileX;
		int farmTileY;
		//FarmTile(Surface* screen);
		FarmTile(int x, int y);
		void Draw(Surface* screen);
		void SetFrame(int frame);
	};
};