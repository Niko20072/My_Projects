#pragma once
#include "surface.h"
#include "template.h"
#include <cassert>
#include <vector>
#include <iostream>
#include "map.h"
#include "worldState.h"
#include "buttons.h"
#include "wateringCan.h"

namespace Tmpl8
{
	//fix click problem!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	class FarmTile
	{
	public:
		FarmTile(float x, float y, WateringCan& wa);
		//int getFrame() { return frame; }
		float getX() { return farmTileX; }
		float getY() { return farmTileY; }
		int getIsClicked() { return isClicked; }
		int getClicked() { return clicked; }
		int getWatered() { return watered; }
		void setIsClicked(bool state) { isClicked = state; }
		void setClicked(bool state) { clicked = state; }
		void setWatered(bool state) { watered = state; }
		void setFrame(int f) { frame = f; }

		void Draw(Surface* screen);// Draw farm tile at its position
		void SetFrame(int frame); // Set the current frame of the farm tile sprite
		void Clicked(); // Mark the tile as clicked and update its frame
		void Update(float x, float y); // Update tile state based on interaction
	private:
		WateringCan& wateringCan; // reference to existing watering can state
		std::unique_ptr<Sprite> farmTile;
		float farmTileX;
		float farmTileY;
		int frame = 0; // Current frame of the farm tile sprite
		bool isClicked = false; // Whether the tile has been clicked
		bool clicked = false;
		bool watered = false;
	};
};