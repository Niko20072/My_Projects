#pragma once
#include "surface.h"
namespace Tmpl8
{
	class Inventory;

	class Crafting
	{
	public:
		Crafting(Inventory& inv) : inventory(inv) {};
		//---Getters---
		bool CraftingIsOpen();
		int getFrame();
		bool getTutorialCraft() { return tutorialCraft; }
		//---Setters---
		void setFrame(int state);
		void setState(bool state);
		//---Main functions---
		void ManageFrames(); // Manage frame selection
		void CraftVitalTonic(); // Craft Vital Tonic
		void CraftCalmMind(); // Craft Calm Mind Elixir
		void CraftDreamDraught(); // Craft Dream Draught
		void CraftFireHeart(); // Craft FireHeart Brew
		void CraftFrostVeil(); // Craft Frostveil Potion
		void CraftPotions(); // Handle crafting logic
		void Draw(Surface* screen); // Draw crafting interface
	private:
		Inventory& inventory;
		Sprite crafting = Sprite(new Surface("assets/image/crafting.png"), 3);
		bool craftingisopen = false; // Crafting screen open state
		int frame = 0; // Current crafting frame
		bool tutorialCraft = false; // Tutorial state to check if the player has crafted a potion for the first time
		void CraftingDraw(Surface* screen); // Draw crafting screen and ingredient counts
	};
}