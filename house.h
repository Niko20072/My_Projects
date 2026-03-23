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
		//---Getters---
		Crafting& hCrafting(); // Reference to crafting system
		bool IsOpen();
		int getFrame();
		bool NightstandIsOpen();
		bool BedIsOpen();
		bool MainScreenOpen();
		bool getClickedYes();
		//---Main functions---
		void HouseLogic(float mouseWorldX, float mouseWorldY); // Handle house interactions (opening/closing, crafting menu)
		void Craftinglogic(); // Handle crafting menu interactions
		void BedLogic(int &dayCounter); // Handle bed click and day progression logic
		bool ConfirmedToSleep(); // Check if player confirmed to sleep and progress to next day
		void NightstandLogic(); // Handle nightstand click
		void CheckGameCompleted(int coinCounter, bool& gameCompleted); // Check if the game completion conditions are met and set gameCompleted to true if they are
		void Draw(Surface* screen);
	private:
		Player& player; // reference to existing player
		Inventory& inventory; // reference to existing inventory
		Crafting crafting;
		Sprite house = Sprite(new Surface("assets/image/house.png"), 3);
		Sprite nightstand = Sprite(new Surface("assets/image/nightstand.png"), 1);
		Sprite bed_hover = Sprite(new Surface("assets/image/bed_hover.png"), 1);
		Sprite table_hover = Sprite(new Surface("assets/image/table_hover.png"), 1);
		Sprite nightstand_hover = Sprite(new Surface("assets/image/nightstand_hover.png"), 1);
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