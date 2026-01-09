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
		extern bool craftingisopen;
		extern int frame;
		void ManageFrames(int mouseX, int mouseY);
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& potion);
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& ingredient3, int& potion);
		void Craft(bool leftPressed, int mouseX, int mouseY);
		void ShowCrafting(Surface* screen, bool qPressed, int mouseX, int mouseY);
	}
};