#pragma once
#include "surface.h"
#include <windows.h>

namespace Tmpl8
{
	namespace House
	{
		extern Sprite house;
		extern Sprite crafting;
		extern float inputCooldown;
		extern bool houseisopen;
		extern bool craftingisopen;
		void ManageFrames(int mouseX, int mouseY);
		void ShowHouse(Surface* screen, float reachX1, float reachX2, float reachY1, float reachY2, int worldX, int worldY);
		void ShowCrafting(Surface* screen, int mouseX, int mouseY);
		void DayUpdate(int& dayCounter, int mouseX, int mouseY);
		void Update(Surface* screen, float deltaTime);
	}
};