#pragma once
#include "surface.h"
namespace Tmpl8
{
	class Inventory;

	class Crafting
	{
	public:
		Crafting(Inventory& inv) : inventory(inv) {};

		bool CraftingIsOpen();
		void setState(bool state);
		int getFrame();
		void setFrame(int state);
		bool getTutorialCraft() { return tutorialCraft; }

		void ManageFrames(); // Manage frame selection
		void CraftVitalTonic(); // Craft Vital Tonic
		void CraftCalmMind(); // Craft Calm Mind Elixir
		void CraftDreamDraught(); // Craft Dream Draught
		void CraftFireHeart(); // Craft FireHeart Brew
		void CraftFrostVeil(); // Craft Frostveil Potion
		void CraftPotions(); // Handle crafting logic
		void Draw(Surface* screen);
	private:
		Sprite crafting = Sprite(new Surface("assets/crafting.png"), 3);
		bool craftingisopen = false; // Crafting screen open state
		int frame = 0; // Current crafting frame
		bool tutorialCraft = false;
		Inventory& inventory;
		void CraftingDraw(Surface* screen); // Draw crafting screen and ingredient counts
	};
}