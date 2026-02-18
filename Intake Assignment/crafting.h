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
		void CraftVitalTonic(); // Craft Vital Tonic
		void CraftCalmMind(); // Craft Calm Mind Elixir
		void CraftDreamDraught(); // Craft Dream Draught
		void CraftFireHeart(); // Craft FireHeart Brew
		void CraftFrostVeil(); // Craft Frostveil Potion
		void CraftLogic(); // Handle crafting logic
		void ManageCrafring(); // Show crafting interface
		void Draw(Surface* screen);
	private:
		Sprite crafting = Sprite(new Surface("assets/crafting.png"), 3);
		bool craftingisopen = false; // Crafting screen open state
		int frame = 0; // Current crafting frame
		Inventory& inventory;
		void CraftingDraw(Surface* screen); // Draw crafting screen and ingredient counts
	};
}