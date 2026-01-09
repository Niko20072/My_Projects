#pragma once
#include "surface.h"
#include <windows.h>
#include "inventory.h"
#include "template.h"
namespace Tmpl8
{
	namespace Crafting
	{
		extern Sprite crafting;
		extern bool craftingisopen; // Crafting screen open state
		extern int frame; // Current crafting frame
		void CraftingDraw(Surface* screen); // Draw crafting screen and ingredient counts
		void ManageFrames(int mouseX, int mouseY); // Manage frame selection
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& potion); // For potions with two ingredients
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& ingredient3, int& potion); // For potions with three ingredients
		void Craft(bool &leftPressed, int mouseX, int mouseY); // Handle crafting logic
		void ShowCrafting(Surface* screen, bool &leftPressed, bool &qPressed, int mouseX, int mouseY); // Show crafting interface
	}
};