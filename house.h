#pragma once
#include "surface.h"
#include "crafting.h"
#include <Audio/Sound.hpp>

namespace Tmpl8
{
	class Inventory;
	class Player;

	class House
	{
		
	public:
		House(Player& pl);
		Crafting& hCrafting() { return crafting; } // Reference to crafting system
		bool IsOpen();
		int getFrame();
		bool NightstandIsOpen() { return nightstandisopen; }
		bool BedIsOpen() { return bedisopen; }
		int MainScreenOpen();
		bool getClickedYes() { return clickedYes; }
		void HouseLogic(float mouseWorldX, float mouseWorldY); // Handle house interactions (opening/closing, crafting menu)
		void Craftinglogic(); // Handle crafting menu interactions
		void BedLogic(int &dayCounter); // Handle bed click and day progression logic
		bool ConfirmedToSleep();
		void NightstandLogic(); // Handle nightstand click
		void Draw(Surface* screen);
		void CheckGameCompleted(int coinCounter, bool& gameCompleted);
	private:
		Sprite house = Sprite(new Surface("assets/house.png"), 3);
		Sprite nightstand = Sprite(new Surface("assets/nightstand2.png"), 1);
		Sprite bed_hover = Sprite(new Surface("assets/bed_hover.png"), 1);
		Sprite table_hover = Sprite(new Surface("assets/table_hover.png"), 1);
		Sprite nightstand_hover = Sprite(new Surface("assets/nightstand_hover.png"), 1);
		Player& player; // reference to existing player
		Inventory& inventory; // reference to existing inventory
		
		Crafting crafting;
		Audio::Sound doorOpen;
		Audio::Sound doorClose;
		bool houseisopen = false; // Is the house menu open?
		bool nightstandisopen = false; // Is the nightstand menu open?
		bool bedisopen = false; // Is the bed menu open?
		int frame = 0; // Current frame of the house
		bool clickedYes = 0;
		bool clickedNo = 0;
		void DrawHover(Surface* screen);
	};
}