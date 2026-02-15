#pragma once
#include "surface.h"
#include "template.h"
#include "map.h"
#include <vector>
#include <iostream>
#include "inventory.h"
#include "buttons.h"

namespace Tmpl8
{
	class Plant
	{
	public:
		Plant(float x, float y, int harvestDay, int frame, Inventory &inv);
		int getGrown() { return grown; }
		int getAlive() { return alive; }
		void setWatered(bool state) { watered = state; }
		void Draw(Surface* screen);
		void Update();
		void Collect();

	private:
		Inventory& inventory;
		//plant(std::make_unique<Sprite>(new Surface("assets/plant.png"), 20)
		Sprite plant = Sprite(new Surface("assets/plant.png"), 20);
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