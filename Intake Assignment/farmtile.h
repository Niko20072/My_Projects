#pragma once
#include "surface.h"
#include <iostream>
#include "plant.h"


namespace Tmpl8
{
	class Inventory;
	class WateringCan;
	class Camera;
	class Player;

	class FarmTile
	{
	public:
		FarmTile(float x, float y, WateringCan& wa, Inventory& inv, Camera& cam, Player& pl);
		bool getPlanted() { return planted; }
		int getClicked() { return clicked; }
		void setClicked(bool state) { clicked = state; }
		void setWatered(bool state) { watered = state; }

		void Draw(Surface* screen);// Draw farm tile at its position
		void DrawHover(Surface* screen, float mouseWorldX, float mouseWorldY);
		void Update(float mouseWorldX, float mouseWorldY); // Update tile state based on interaction

		//planting and plant management
		void CreatePlant(int plantType); // Create a plant on this tile based on the plant type (1-5)
		void DeletePlant(); // Delete the plant on this tile
		void CollectPlant(); // Update the plant's state each day
		void UpdatePlant(); // Progress the plant to the next day
		void DrawPlant(Surface* screen, float DeltaTime);
	private:
		WateringCan& wateringCan; // reference to existing watering can state
		Inventory& inventory;
		Camera& camera;
		Player& player;
		std::unique_ptr<Sprite> farmTile;
		std::unique_ptr<Sprite> hover;
		std::unique_ptr<Plant> plant;
		float farmTileX;
		float farmTileY;
		int frame = 0; // Current frame of the farm tile sprite
		bool planted = false; // Whether a plant is planted on this tile
		bool clicked = false;
		bool watered = false;
		float time = 0;
	};
};