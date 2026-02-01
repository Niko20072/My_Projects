#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
#include <cstdio> //printf
#include <iostream>
#include <vector>
#include "house.h"
#include "plant.h"
#include "worldState.h"
#include "buttons.h"

namespace Tmpl8
{
	namespace Inventory
	{
		extern int frame; // Inventory frame
		extern bool inventoryisopen; // Inventory open state
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

		void BuySeeds(Surface* screen, int& coinCounter); // Buying seeds logic
		void PlantSeeds(Surface* screen, float plantX, float plantY, int tileNumber); // Planting seeds logic
		void DrawInventory(Surface* screen); // Drawing inventory on screen
		void MainInventory(Surface* screen); // Normal inventory management
		void CarInventory(Surface* screen, int& coinCounter); // Car inventory management
		void SeedsInventory(Surface* screen, float plantX, float plantY, bool tileClicekd, int tileNumber); // Seed inventory management
		void Draw(Surface* screen); // Draw inventory if open
		bool InventorysClosed(); // Check if all inventories are closed
	}
};