#pragma once
#include "surface.h"
#include <windows.h>
#include "inventory.h"
#include "template.h"
#include "buttons.h"
namespace Tmpl8
{
	class Crafting
	{
	public:
		Crafting(Inventory& inv) : inventory(inv) {};

		bool getState();
		void setState(bool state);
		int getFrame();
		void setFrame(int state);

		void ManageFrames(); // Manage frame selection
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& potion); // For potions with two ingredients
		void CraftLogic(bool button, int Frame, int& ingredient1, int& ingredient2, int& ingredient3, int& potion); // For potions with three ingredients
		void Craft(); // Handle crafting logic
		void ManageCrafring(); // Show crafting interface
		void CraftingDraw(Surface* screen); // Draw crafting screen and ingredient counts
		void Draw(Surface* screen);
	private:
		Sprite crafting = Sprite(new Surface("assets/crafting.png"), 3);
		bool craftingisopen = false; // Crafting screen open state
		int frame = 0; // Current crafting frame
		Inventory& inventory;
	};
}