#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
#include <cstdio> //printf
#include <iostream>
#include <vector>
#include "house.h"
#include "plant.h"

namespace Tmpl8
{
	namespace Inventory
	{
		extern int x, y; // Inventory position
		extern int frame; // Inventory frame
		extern bool isopen; // Inventory open state
		extern bool carisopen; // Car inventory open state
		extern bool seedsisopen; // Seed inventory open state

		// Ingredient counters
		extern int contSunblossom; // Sunblossom counter
		extern int contMoonleaf; // Moonleaf counter
		extern int contEmberroot; // Emberroot counter
		extern int contFrostmint; // Frostmint counter
		extern int contBerry; // Nightshade Berry counter

		// Potion counters
		extern int contVitalTonic; // Vital Tonic counter
		extern int contCalmMind; // Calm Mind Elixir counter
		extern int contDreamDraught; // Dream Draught counter
		extern int contFireHeart; // FireHeart Brew counter
		extern int contFrostveil; // Frostveil Potion counter

		// Seed counters
		extern int contSeedSunblossom; // Sunblossom Seed counter
		extern int contSeedMoonleaf; // Moonleaf Seed counter
		extern int contSeedEmberroot; // Emberroot Seed counter
		extern int contSeedFrostmint; // Frostmint Seed counter
		extern int contSeedBerry; // Nightshade Berry Seed counter

		// Vector of pointers to potion counters
		extern std::vector<int*> potionCounters;

		extern Sprite inventory;
		// Frame 0 : Ingredients
		// Frame 1 : Potions
		// Frame 2 : Seeds
		// Frame 3 : Planting seeds
		// Frame 4 : Car Shop
		// Frame 5 : Car Orders

		void BuySeeds(Surface* screen, bool &leftPressed, int& coinCounter, int mouseX, int mouseY); // Buying seeds logic
		void PlantSeeds(Surface* screen, bool& leftPressed, int mouseX, int mouseY, float plantX, float plantY, int tileNumber); // Planting seeds logic
		void DrawInventory(Surface* screen); // Drawing inventory on screen
		void NormalInventory(Surface* screen, bool leftPressed, bool ePressed, bool qPressed, int mouseX, int mouseY); // Normal inventory management
		void CarInventory(Surface* screen, int& coinCounter, bool ePressed, bool qPressed, bool& leftPressed, int mouseX, int mouseY, float worldX, float worldY, float reachX1, float reachY1, float reachX2, float reachY2); // Car inventory management
		void SeedsInventory(Surface* screen, bool ePressed, bool qPressed, bool& leftPressed, int mouseX, int mouseY, float worldX, float worldY, float plantX, float plantY, bool tileClicekd, int tileNumber); // Seed inventory management
		void DrawOnScreen(Surface* screen, float deltaTime); // Draw inventory if open
		bool InventorysClosed(); // Check if all inventories are closed
	}
};