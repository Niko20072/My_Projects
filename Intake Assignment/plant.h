#pragma once
#include "surface.h"
#include "template.h"
#include <vector>
#include <iostream>

namespace Tmpl8
{
	class Plant
	{
	public:
		std::string name;
		int harvestDay; //the day when the plant is grown
		int daysPassed; //plant age
		bool grown;

		Plant(std::string& plantName);
		void NextDay();
	};
};
