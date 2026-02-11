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
	class Inventory
	{
	public:
		int frame = 0; // Inventory frame
		bool inventoryisopen; // Inventory open state
		bool carisopen; // Car inventory open state
		bool seedsisopen; // Seed inventory open state

		// Ingredient counters
		int contSunblossom; // Sunblossom counter
		int contMoonleaf; // Moonleaf counter
		int contEmberroot; // Emberroot counter
		int contFrostmint; // Frostmint counter
		int contBerry; // Nightshade Berry counter

		// Potion counters
		int contVitalTonic; // Vital Tonic counter
		int contCalmMind; // Calm Mind Elixir counter
		int contDreamDraught; // Dream Draught counter
		int contFireHeart; // FireHeart Brew counter
		int contFrostveil; // Frostveil Potion counter

		// Seed counters
		int contSeedSunblossom; // Sunblossom Seed counter
		int contSeedMoonleaf; // Moonleaf Seed counter
		int contSeedEmberroot; // Emberroot Seed counter
		int contSeedFrostmint; // Frostmint Seed counter
		int contSeedBerry; // Nightshade Berry Seed counter

		// Vector of pointers to potion counters
		std::vector<int*> potionCounters;

		Sprite inventory;
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
	};
}