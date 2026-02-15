#pragma once
#include "surface.h"
#include "template.h"
#include <cassert>
#include <vector>
#include <iostream>
#include "map.h"
#include "worldState.h"
#include "inventory.h"
#include "buttons.h"
#include "wateringCan.h"
#include "plant.h"

namespace Tmpl8
{
	//fix click problem!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	class FarmTile
	{
	public:
		FarmTile(float x, float y, WateringCan& wa, Inventory& inv);
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

		//planting and plant management
		void CreatePlant(int plantType); // Create a plant on this tile based on the plant type (1-5)
		void DeletePlant(); // Delete the plant on this tile
		void UpdatePlant(); // Update the plant's state each day
		void NextDayPlant(); // Progress the plant to the next day
		void DrawPlant(Surface* screen);
	private:
		WateringCan& wateringCan; // reference to existing watering can state
		Inventory& inventory;
		std::unique_ptr<Sprite> farmTile;
		std::unique_ptr<Plant> plant;
		float farmTileX;
		float farmTileY;
		int frame = 0; // Current frame of the farm tile sprite
		bool planted = false; // Whether a plant is planted on this tile
		bool isClicked = false; // Whether the tile has been clicked
		bool clicked = false;
		bool watered = false;
	};
};