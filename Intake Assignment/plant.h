#pragma once
#include "surface.h"
#include "template.h"
#include "map.h"
#include <vector>
#include <iostream>
#include "farmtile.h"
#include "wateringCan.h"
#include "buttons.h"

namespace Tmpl8
{
	class Plant
	{
	public:
		static std::vector<Plant> plants;
		Plant(float x, float y, int harvestDay, int frame, int tileNumber, Inventory &inv);
		int getGrown() { return grown; }
		int getHarvested() { return harvested; }
		void Draw(Surface* screen);
		void NextDay();
		void Collect();
		void Update();
		void Delete();
	private:
		std::unique_ptr<Sprite> plant;
		std::string name;
		Inventory& inventory;
		int harvestDay; //the day when the plant is grown
		int daysPassed = 0; //plant age
		bool grown = false;
		int frame; //sprite frame
		int tileNumber; //the farm tile where the plant is planted
		float x, y;
		bool harvested = false;
		bool alive = true;
		static bool wateringCan;
	};
}