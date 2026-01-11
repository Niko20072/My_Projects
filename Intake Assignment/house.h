#pragma once
#include "surface.h"
#include <windows.h>
#include "inventory.h"
#include "template.h"
#include "crafting.h"

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
		void ShowHouse(Surface* screen, bool qPressed, float reachX1, float reachX2, float reachY1, float reachY2, float worldX, float worldY); // Show house menu
		void DayUpdate(bool& leftPressed, bool& qPressed, int& dayCounter, int mouseX, int mouseY); // Update house menu based on day progression
		void ClickedNightstand(Surface* screen, bool &leftPressed, bool qPressed, int coinCounter, int mouseX, int mouseY); // Handle nightstand click
		void GameCompleted(Surface* screen, bool &leftPressed, bool qPressed, int coinCounter, int mouseX, int mouseY, bool& gameCompleted); // Show game completed screen
	}
};