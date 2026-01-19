#pragma once
#include "surface.h"
#include "template.h"
#include "map.h"
#include <vector>
#include <iostream>
#include "farmtile.h"

namespace Tmpl8
{
	class Plant
	{
	public:
		/*
		Sprite *sun = new Sprite(new Surface("assets/ball.png"), 1);
		std::string name;
		int harvestDay; //the day when the plant is grown
		int daysPassed; //plant age
		bool grown;
		float x, y;

		//Plant(std::string plantName);
		Plant(float x, float y);

		~Plant() { delete sun; }
		Plant(const Plant&) = delete;
		Plant& operator=(const Plant&) = delete;
		Plant(Plant&& t) {
			sun = t.sun;
			t.sun = nullptr;
			harvestDay = t.harvestDay;
		}
		Plant& operator=(Plant&& t)
		{
			if (this != &t) {
				delete sun;
				sun = t.sun;
				t.sun = nullptr;
				harvestDay = t.harvestDay;
			}
			return *this;
		}*/
		static std::vector<Plant> plants;   
		std::unique_ptr<Sprite> sun;
		std::string name;
		int harvestDay; //the day when the plant is grown
		int daysPassed = 0; //plant age
		bool grown = false;
		int frame; //sprite frame
		float x, y;

		Plant(float x, float y, int harvestDay, int frame, int tileNumber);
		void Draw(Surface* screen);
		void Grow();
	};
};
