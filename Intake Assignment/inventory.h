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
#include <unordered_map>

namespace Tmpl8
{
	/*
	//make player class -> game has player -> inv
	//map -> house
	//reference to house (player)*/
	// Frame 0 : Ingredients
	// Frame 1 : Potions
	// Frame 2 : Seeds
	// Frame 3 : Planting seeds
	// Frame 4 : Car Shop
	// Frame 5 : Car Orders
	class Inventory
	{
	public:

		enum class Item
		{
			VitalTonic,
			CalmMind,
			DreamDraught,
			FireHeart,
			FrostVeil,
			Sunblossom,
			Moonleaf,
			Emberroot,
			Frostmint,
			Berry,
			SeedSunblossom,
			SeedMoonleaf,
			SeedEmberroot,
			SeedFrostmint,
			SeedBerry
		};
		
		Inventory(WateringCan& wa) : wateringCan(wa) {}
		int getFrame();
		int MainInvIsOpen();
		int SeedInvIsOpen();
		void setSeedState(bool state);

		int AddItem(Item item, int quantity = 1); // Add item to inventory
		int GetItemCount(Item item); // Get count of specific item in inventory

		void MainInventoryLogic(Surface* screen); // Normal inventory management
		void SeedInventoryLogic(Surface* screen, bool tileClicekd); // Seed inventory management
		void Draw(Surface* screen);

	private:
		int frame = 0; // Inventory frame
		bool inventoryisopen = false; // Inventory open state
		bool seedsisopen = false; // Seed inventory open state
		WateringCan& wateringCan; // Reference to player's watering can
		Sprite inventory = Sprite(new Surface("assets/inventory.png"), 6);
		std::unordered_map<Item, int> items = {
			{ Item::VitalTonic, 10 },
			{ Item::CalmMind, 10 },
			{ Item::DreamDraught, 10 },
			{ Item::FireHeart, 10 },
			{ Item::FrostVeil, 10 },
			{ Item::Sunblossom, 10 },
			{ Item::Emberroot, 10 }, 
			{ Item::Moonleaf, 10 }, 
			{ Item::Frostmint, 10 }, 
			{ Item::Berry, 10 },
			{ Item::SeedSunblossom, 10 },
			{ Item::SeedEmberroot, 10 },
			{ Item::SeedMoonleaf, 10 },
			{ Item::SeedFrostmint, 10 },
			{ Item::SeedBerry, 10 }
		}; // Map to store item counts
	};
}