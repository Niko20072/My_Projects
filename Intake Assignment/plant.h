#pragma once
#include "surface.h"
#include <vector>
#include <iostream>
#include "camera.h"



namespace Tmpl8
{
	class Inventory;
	class Camera;
	class Plant
	{
	public:
		Plant(float x, float y, int harvestDay, int frame, Inventory &inv, Camera& cam);
		int getGrown() { return grown; }
		int getAlive() { return alive; }
		void setWatered(bool state) { watered = state; }
		void Draw(Surface* screen);
		void Update();
		void Collect();

	private:
		Inventory& inventory;
		Camera& camera;
		//plant(std::make_unique<Sprite>(new Surface("assets/plant.png"), 20)
		Sprite plant = Sprite(new Surface("assets/plant12.png"), 20);
		int harvestDay; //the day when the plant is grown
		int daysPassed = 0; //plant age
		bool grown = false;
		int frame; //sprite frame
		float x, y;
		bool alive = true;
		bool watered = false;
		//static bool wateringCan;
	};
}