#pragma once
#include <unordered_map>
#include "surface.h"

namespace Tmpl8
{
	/*
	// Frame 0 : Ingredients
	// Frame 1 : Potions
	// Frame 2 : Seeds
	// Frame 3 : Planting seeds
	// Frame 4 : Car Shop
	// Frame 5 : Car Orders
	*/

	class WateringCan; // Forward declaration of WateringCan class

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
			SeedBerry,
			COUNT
		};
		Inventory(WateringCan& wa) : wateringCan(wa) {}
		//---Getters---
		int getFrame();
		bool MainInvIsOpen();
		bool SeedInvIsOpen();
		//---Setters---
		void setSeedState(bool state);
		//---Item management---
		void AddItem(Item item, int quantity = 1); // Add item to inventory
		void SetItemTo(Item item, int quantity);
		int GetItemCount(Item item); // Get count of specific item in inventory
		//--Main functions---
		void MainInventoryLogic(); // Normal inventory management
		void SeedInventoryLogic(bool tileClicekd); // Seed inventory management
		void Draw(Surface* screen);
	private:
		int frame = 0; // Inventory frame
		bool inventoryisopen = false; // Inventory open state
		bool seedsisopen = false; // Seed inventory open state
		WateringCan& wateringCan; // Reference to player's watering can
		Sprite inventory = Sprite(new Surface("assets/image/inventory.png"), 6);
		std::unordered_map<Item, int> items = {
			{ Item::VitalTonic, 0 },
			{ Item::CalmMind, 0 },
			{ Item::DreamDraught, 0 },
			{ Item::FireHeart, 0 },
			{ Item::FrostVeil, 0 },
			{ Item::Sunblossom, 1 },
			{ Item::Emberroot, 1 }, 
			{ Item::Moonleaf, 0 }, 
			{ Item::Frostmint, 0 }, 
			{ Item::Berry, 0 },
			{ Item::SeedSunblossom, 2 },
			{ Item::SeedEmberroot, 1 },
			{ Item::SeedMoonleaf, 2 },
			{ Item::SeedFrostmint, 1 },
			{ Item::SeedBerry, 0 }
		}; // Map to store item counts
		void InventoryText(Surface* screen);
	};
}