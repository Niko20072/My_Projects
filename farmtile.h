#pragma once
#include "surface.h"
#include <iostream>
#include "plant.h"
#include <Audio/Sound.hpp>

namespace Tmpl8
{
	class Inventory;
	class WateringCan;
	class Camera;
	class Player;

	class FarmTile
	{
	public:
		FarmTile(float x, float y, Player& pl, Camera& cam);
		//---Getters---
		bool getPlanted();
		bool getClicked();
		//---Setters---
		void setClicked(bool state);
		void setWatered(bool state);
		//---Farmtile---
		void Draw(Surface* screen);// Draw farm tile at its position
		void DrawHover(Surface* screen, float mouseWorldX, float mouseWorldY);
		void Update(float mouseWorldX, float mouseWorldY); // Update tile state based on interaction
		//---Plant---
		void CreatePlant(int plantType); // Create a plant on this tile based on the plant type (1-5)
		void DeletePlant(); // Delete the plant on this tile
		void CollectPlant(float deltaTime); // Collect the plant if it's ready and the player interacts with it
		void UpdatePlant(); // Progress the plant to the next day
		void DrawPlant(Surface* screen);
	private:
		Player& player; // reference to existing player
		Camera& camera;
		WateringCan& wateringCan; 
		Inventory& inventory;
		std::unique_ptr<Sprite> farmTile;
		std::unique_ptr<Sprite> hover;
		std::unique_ptr<Plant> plant;
		Audio::Sound itemCollect;
		float farmTileX;
		float farmTileY;
		int frame = 0; // Current frame of the farm tile sprite
		bool planted = false; // Whether a plant is planted on this tile
		bool clicked = false;
		bool watered = false;
		float time = 0; // Time accumulator for plant growth
		bool printNotReady = false; // Whether the "Not ready!" message is being printed for this tile
	};
};