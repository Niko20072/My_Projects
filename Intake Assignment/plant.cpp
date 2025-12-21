#include "plant.h"

namespace Tmpl8
{
	int Plant::contSunblossom = 0;
	int Plant::contMoonleaf = 0;
	int Plant::contEmberroot = 0;
	int Plant::contFrostmint = 0;
	int Plant::contBerry = 0;

	Plant::Plant(std::string& plantName)
	{
		name = plantName;
		daysPassed = 0;
		grown = false;

		if (name == "Sunblossom")
			harvestDay = 3;
		else if (name == "Moonleaf")
			harvestDay = 2;
		else if (name == "Emberroot")
			harvestDay = 3;
		else if (name == "Frostmint")
			harvestDay = 2;
		else if (name == "Berry")
			harvestDay = 4;
		else
			harvestDay = 0;
	}

	void Plant::NextDay()
	{
		daysPassed++;
		if (grown)
		{
			if (name == "Sunblossom")
				contSunblossom++;
			else if (name == "Moonleaf")
				contMoonleaf++;
			else if (name == "Emberroot")
				contEmberroot++;
			else if (name == "Frostmint")
				contFrostmint++;
			else if (name == "Berry")
				contBerry++;
			return;
		}
			
		if (daysPassed >= harvestDay)
			grown = true;
	}
};