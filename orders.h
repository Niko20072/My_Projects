#pragma once
#include <iostream>
#include <vector>
#include "surface.h"

namespace Tmpl8
{
	class Inventory;
	class Order
	{
	public:
		Order(int number, Inventory	&inv); // Constructor
		void Update(int& coinCounter); // Logic for order processing
		void Draw(Surface* screen); // Draw order on screen
	private:
		Inventory& inventory; // Reference to player's inventory

		// Potion types and their prices
		const std::vector<const char*> potionsTypes = { "Vital Tonic", "Calm Mind", "Dream Draught", "FireHeart", "FrostVeil" };
		const std::vector<int> priceNumbers = { 60,45,70,95,85 };

		int orderNumber; // Which order it is
		int potionNumber; // How many potions ordered
		int numberPotionType1; // How many of first potion ordered
		int numberPotionType2; // How many of second potion ordered
		int potionType1; // Type of potion1 ordered
		int potionType2; // Type of potion2 ordered
		int price; // Price of the order
		bool completed = false; // Is the order completed?
		char order[64], send[32], complete[32]; // Text buffers
		int range = 5; // Click range (and Button outline)
	};
}