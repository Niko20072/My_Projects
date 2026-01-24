#pragma once
#include "template.h"
#include <iostream>
#include <vector>
#include "inventory.h"
#include "surface.h"

namespace Tmpl8
{
	class Order
	{
	public:
		// Potion types and their prices
		std::vector<const char*> potionsTypes = { "Vital Tonic", "Calm Mind", "Dream Draught", "FireHeart", "FrostVeil" };
		std::vector<int> priceNumbers = {60,45,70,95,85};

		int orderNumber; // Which order it is
		int potionNumber; // How many potions ordered
		int potionTypeNumber1; // How many of first potion ordered
		int potionTypeNumber2; // How many of second potion ordered
		int potionType1; // Type of potion1 ordered
		int potionType2; // Type of potion2 ordered
		int price; // Price of the order
		bool completed = false; // Is the order completed?
		char order[64], send[32], complete[32], daysUntilResetText[64]; // Text buffers
		static int daysUntilReset; // Days until orders reset 
		Order(int number); // Constructor
		void Logic(Surface* screen, bool& LeftPressed, int mouseX, int mouseY, int& coinCounter); // Logic for order processing
		void Draw(Surface* screen); // Draw order on screen
	};
};