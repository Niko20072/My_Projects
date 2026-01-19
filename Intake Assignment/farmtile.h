#pragma once
#include "surface.h"
#include "template.h"
#include <cassert>
#include <vector>
#include "inventory.h"
#include "map.h"

namespace Tmpl8
{
	//fix click problem!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	class FarmTile
	{
	public:
		static std::vector<FarmTile> farmTiles;
		Sprite *farmTile = new Sprite(new Surface("assets/tiles.png"), 4);
		int farmTileX;
		int farmTileY;
		int frame = 0; // Current frame of the farm tile sprite
		bool isClicked = false; // Whether the tile has been clicked

		//FarmTile(Surface* screen);

		FarmTile(float x, float y);

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

		void Draw(Surface* screen);// Draw farm tile at its position
		void SetFrame(int frame); // Set the current frame of the farm tile sprite
		void Clicked(); // Mark the tile as clicked and update its frame
		void Update(bool leftClicked, float x, float y, float worldX, float worldY, float reachX1, float reachX2, float reachY1, float reachY2, bool& clicked); // Update tile state based on interaction
	};
};