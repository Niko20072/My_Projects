#pragma once
#include "surface.h"
#include <windows.h>
#include "inventory.h"
#include "template.h"
#include "crafting.h"

namespace Tmpl8
{
	namespace House
	{
		extern Sprite house;
		extern bool houseisopen;
		void ShowHouse(Surface* screen, bool qPressed, float reachX1, float reachX2, float reachY1, float reachY2, float worldX, float worldY);
		void DayUpdate(bool leftPressed, int& dayCounter, int mouseX, int mouseY);
	}
};