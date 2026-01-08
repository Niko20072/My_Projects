#pragma once
#include "template.h"
#include <iostream>
#include <vector>
#include "inventory.h"
namespace Tmpl8
{
	class Order
	{
	public:
		std::vector<const char*> potionsTypes = { "Vital Tonic", "Calm Mind", "Dream Draught", "FireHeart", "FrostVeil" };
		std::vector<int> priceNumbers = { 60,45,70,95,85 };
		int orderNumber;
		int potionNumber;//how many potions ordered
		int potionTypeNumber1;//how many of one potion ordered
		int potionTypeNumber2;//how many of one potion ordered
		int potionType1;//type of potion ordered
		int potionType2;//type of potion ordered
		int price;
		bool completed = false;
		char order[64], send[32], complete[32];
		Order(int number);
		void Logic(Surface* screen, bool& LeftPressed, int mouseX, int mouseY, int& coinCounter);
		void Draw(Surface* screen);
	};
};