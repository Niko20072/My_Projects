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
		Sprite *WetFarmTile = new Sprite(new Surface("assets/tileset1.png"), 2);
		int farmTileX;
		int farmTileY;
		//FarmTile(Surface* screen);

		FarmTile(int x, int y);

		//i actually dk what ahppened here but it works now -> study
		~FarmTile() { delete WetFarmTile; }
		FarmTile(const FarmTile&) = delete;
		FarmTile& operator=(const FarmTile&) = delete;
		FarmTile(FarmTile&& t) {	
			WetFarmTile = t.WetFarmTile;
			t.WetFarmTile = nullptr;
			farmTileX = t.farmTileX;
			farmTileY = t.farmTileY;
		}
		FarmTile& operator=(FarmTile&& t) {
			if (this != &t) {
				delete WetFarmTile;
				WetFarmTile = t.WetFarmTile;
				t.WetFarmTile = nullptr;
				farmTileX = t.farmTileX;
				farmTileY = t.farmTileY;
			}
			return *this;
		}
		//i actually dk what ahppened here but it works now

		void Draw(Surface* screen);
		void SetFrame(int frame);
	};
};