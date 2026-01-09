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
		extern bool houseisopen; // Is the house menu open?
		extern int frame; // Current frame of the house
		void ShowHouse(Surface* screen, bool qPressed, float reachX1, float reachX2, float reachY1, float reachY2, float worldX, float worldY);// Show house menu
		void DayUpdate(bool& leftPressed, int& dayCounter, int mouseX, int mouseY);// Update house menu based on day progression
		void ClickedNightstand(Surface* screen, bool leftPressed, int& coinCounter, int mouseX, int mouseY);// Handle nightstand click
	}
};