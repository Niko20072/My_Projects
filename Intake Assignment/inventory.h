#pragma once
#include "surface.h"
#include "template.h"
#include <windows.h>
#include <cstdio> //printf
#include <iostream>
#include <vector>
#include "worldState.h"
#include "buttons.h"
#include "wateringCan.h"

namespace Tmpl8
{
	//make player class -> game has player -> inv
	//map -> house
	//reference to house (player)
	class Inventory
	{
	public:
		Inventory(WateringCan& wa) : wateringCan(wa) {}

		// Ingredient counters
		int contSunblossom = 10; // Sunblossom counter
		int contMoonleaf = 10; // Moonleaf counter
		int contEmberroot = 10; // Emberroot counter
		int contFrostmint = 10; // Frostmint counter
		int contBerry = 10; // Nightshade Berry counter

		// Potion counters
		int contVitalTonic = 10; // Vital Tonic counter
		int contCalmMind = 10; // Calm Mind Elixir counter
		int contDreamDraught = 10; // Dream Draught counter
		int contFireHeart = 10; // FireHeart Brew counter
		int contFrostveil = 10; // Frostveil Potion counter

		// Seed counters
		int contSeedSunblossom = 10; // Sunblossom Seed counter
		int contSeedMoonleaf = 10; // Moonleaf Seed counter
		int contSeedEmberroot = 10; // Emberroot Seed counter
		int contSeedFrostmint = 10; // Frostmint Seed counter
		int contSeedBerry = 10; // Nightshade Berry Seed counter
		
		// Vector of pointers to potion counters
		std::vector<int*> potionCounters = { &contVitalTonic, &contCalmMind, &contDreamDraught, &contFireHeart, &contFrostveil };

		int getFrame();
		int getCarState();
		int getInvState();
		int getSeedState();
		void setSeedState(bool state);

		int getContSunblossom();
		int getContMoonleaf();
		int getContEmberroot();
		int getContFrostmint();
		int getContBerry();
		int getContVitalTonic();
		int getContCalmMind();
		int getContDreamDraught();
		int getContFireHeart();
		int getContFrostveil();
		int getContSeedSunblossom();
		int getContSeedMoonleaf();
		int getContSeedEmberroot();
		int getContSeedFrostmint();
		int getContSeedBerry();

		void addContSunblossom();
		void addContMoonleaf();
		void addContEmberroot();
		void addContFrostmint();
		void addContBerry();

		void BuySeeds(Surface* screen, int& coinCounter); // Buying seeds logic
		void PlantSeeds(Surface* screen, float plantX, float plantY, int tileNumber); // Planting seeds logic
		void DrawInventory(Surface* screen); // Drawing inventory on screen
		void MainInventory(Surface* screen); // Normal inventory management
		void CarInventory(Surface* screen, int& coinCounter); // Car inventory management
		void SeedsInventory(Surface* screen, float plantX, float plantY, bool tileClicekd); // Seed inventory management
		void Draw(Surface* screen); // Draw inventory if open
		bool InventorysClosed(); // Check if all inventories are closed

	private:
		int frame = 0; // Inventory frame
		bool inventoryisopen = false; // Inventory open state
		bool carisopen = false; // Car inventory open state
		bool seedsisopen = false; // Seed inventory open state
		WateringCan& wateringCan; // Reference to player's watering can

		Sprite inventory = Sprite(new Surface("assets/inventory.png"), 6);
		// Frame 0 : Ingredients
		// Frame 1 : Potions
		// Frame 2 : Seeds
		// Frame 3 : Planting seeds
		// Frame 4 : Car Shop
		// Frame 5 : Car Orders
		

	};
}