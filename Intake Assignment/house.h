#pragma once
#include "surface.h"
#include <windows.h>
#include "inventory.h"
#include "template.h"
#include "crafting.h"
#include "plant.h"
#include "orders.h"
#include "worldState.h"
#include "buttons.h"

namespace Tmpl8
{
	class House
	{
		
	public:
		House(Inventory& inv) : inventory(inv), crafting(inv) {};
		Crafting& getCrafting() { return crafting; }
		int getHouseState();
		int getFrame();
		void HouseLogic(); // Handle house interactions (opening/closing, crafting menu)
		void ManageCrafring();
		void DayUpdate(int& dayCounter); // Update house menu based on day progression
		void NightstandLogic(Surface* screen, int coinCounter); // Handle nightstand click
		void Draw(Surface* screen);
		void GameCompleted(Surface* screen, int coinCounter, bool& gameCompleted); // Show game completed screen
	private:
		Sprite house = Sprite(new Surface("assets/house.png"), 3);
		Sprite nightstand = Sprite(new Surface("assets/nightstand.png"), 1);
		Sprite gameendscreen = Sprite(new Surface("assets/endgame.png"), 7);
		Inventory& inventory; // reference to existing inventory
		Crafting crafting;
		bool houseisopen = false; // Is the house menu open?
		bool nightstandisopen = false; // Is the nightstand menu open?
		bool bedisopen = false; // Is the bed menu open?
		int frame = 0; // Current frame of the house
		int gameframe = 0; // Current frame of the game end screen
		bool clickedYes = 0;
		bool clickedNo = 0;
	};
}