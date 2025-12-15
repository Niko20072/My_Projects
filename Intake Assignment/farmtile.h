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
		Sprite *farmTile = new Sprite(new Surface("assets/tiles.png"), 4);
		int farmTileX;
		int farmTileY;
		int frame = 0;
		bool isClicked = false;

		//FarmTile(Surface* screen);

		FarmTile(int x, int y);

		//i actually dk what ahppened here but it works now -> study
		~FarmTile() { delete farmTile; }
		FarmTile(const FarmTile&) = delete;
		FarmTile& operator=(const FarmTile&) = delete;
		FarmTile(FarmTile&& t) {	
			farmTile = t.farmTile;
			t.farmTile = nullptr;
			farmTileX = t.farmTileX;
			farmTileY = t.farmTileY;
		}
		FarmTile& operator=(FarmTile&& t) 
		{
			if (this != &t) {
				delete farmTile;
				farmTile = t.farmTile;
				t.farmTile = nullptr;
				farmTileX = t.farmTileX;
				farmTileY = t.farmTileY;
			}
			return *this;
		}
		//i actually dk what ahppened here but it works now

		void Draw(Surface* screen);
		void SetFrame(int frame);
		void Update(float x, float y, float worldX, float worldY, float reachX1, float reachX2, float reachY1, float reachY2, bool& clicked);
	};
};