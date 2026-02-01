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
	namespace House
	{
		extern Sprite house;
		extern Sprite nightstand;
		extern bool houseisopen; // Is the house menu open?
		extern bool nightstandisopen; // Is the nightstand menu open?
		extern bool bedisopen; // Is the bed menu open?
		extern int frame; // Current frame of the house
		extern int gameframe; // Current frame of the game end screen
		void HouseLogic(); // Show house menu
		void DayUpdate(int& dayCounter); // Update house menu based on day progression
		void ClickedNightstand(Surface* screen, int coinCounter); // Handle nightstand click
		void Draw(Surface* screen);
		void GameCompleted(Surface* screen, int coinCounter, bool& gameCompleted); // Show game completed screen
	}
};