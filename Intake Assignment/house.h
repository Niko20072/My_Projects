#pragma once
#include "surface.h"
#include <windows.h>
#include "inventory.h"
#include "template.h"

namespace Tmpl8
{
	namespace House
	{
		extern Sprite house;
		extern Sprite crafting;
		extern bool houseisopen;
		extern bool craftingisopen;
		extern int frame;
		void ManageFrames(int mouseX, int mouseY);
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& potion);
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& ingredient3, int& potion);
		void Craft(bool leftPressed, int mouseX, int mouseY);
		void ShowHouse(Surface* screen, bool qPressed, float reachX1, float reachX2, float reachY1, float reachY2, int worldX, int worldY);
		void ShowCrafting(Surface* screen, bool qPressed, int mouseX, int mouseY);
		void DayUpdate(bool leftPressed, int& dayCounter, int mouseX, int mouseY);
	}
};