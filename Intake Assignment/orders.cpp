#include "orders.h"
namespace Tmpl8
{
	
	Order::Order(int number)
	{
		orderNumber = number;
		potionNumber = 1 + IRand(3);
		potionTypeNumber1 = 1 + IRand(3);
		potionTypeNumber2 = 1 + IRand(3);
		potionType1 = IRand(5);
		potionType2 = IRand(5);
		while(potionType1 == potionType2)
			potionType2 = IRand(5);

		if (potionNumber == 1)
		{
			sprintf(order, "%s x%d", potionsTypes[potionType1], potionTypeNumber1);
			price = priceNumbers[potionType1] * potionTypeNumber1;
		}
		else
		{
			sprintf(order, "%s x%d, %s x%d", potionsTypes[potionType1], potionTypeNumber1, potionsTypes[potionType2], potionTypeNumber2);
			price = (priceNumbers[potionType1] * potionTypeNumber1) + (priceNumbers[potionType2] * potionTypeNumber2);
		}
		sprintf(send, "send(%d)", price);
		sprintf(complete, "completed");
		//std::cout <<" Potion number: " << potionNumber << std::endl;
	}

	void Order::Logic(Surface* screen, int mouseX, int mouseY, int& coinCounter)
	{
		int range = 5;
		int button = GetAsyncKeyState(VK_LBUTTON) && mouseX >= (475 - range) && mouseX <= (526 + range) && mouseY >= (235 + orderNumber * 35 - range) && mouseY <= (242 + orderNumber * 35 + range);
		screen->Box(475 - range, 235 + orderNumber * 35 - range, 526 + range, 242 + orderNumber * 35 + range, 0x0);
		/*
		if (button && !completed)
		{
			if (Inventory::contVitalTonic >= potionTypeNumber1 && potionType1 == 0)
			{
				Inventory::contVitalTonic -= potionTypeNumber1;
				completed = true;
			}
			else if (Inventory::contCalmMind >= potionTypeNumber1 && potionType1 == 1)
			{
				Inventory::contCalmMind -= potionTypeNumber1;
				completed = true;
			}
			else if (Inventory::contDreamDraught >= potionTypeNumber1 && potionType1 == 2)
			{
				Inventory::contDreamDraught -= potionTypeNumber1;
				completed = true;
			}
			else if (Inventory::contFireHeart >= potionTypeNumber1 && potionType1 == 3)
			{
				Inventory::contFireHeart -= potionTypeNumber1;
				completed = true;
			}
			else if (Inventory::contFrostveil >= potionTypeNumber1 && potionType1 == 4)
			{
				Inventory::contFrostveil -= potionTypeNumber1;
				completed = true;
			}
			if (potionNumber == 2 && completed)
			{
				if (Inventory::contVitalTonic >= potionTypeNumber2 && potionType2 == 0)
				{
					Inventory::contVitalTonic -= potionTypeNumber2;
				}
				else if (Inventory::contCalmMind >= potionTypeNumber2 && potionType2 == 1)
				{
					Inventory::contCalmMind -= potionTypeNumber2;
				}
				else if (Inventory::contDreamDraught >= potionTypeNumber2 && potionType2 == 2)
				{
					Inventory::contDreamDraught -= potionTypeNumber2;
				}
				else if (Inventory::contFireHeart >= potionTypeNumber2 && potionType2 == 3)
				{
					Inventory::contFireHeart -= potionTypeNumber2;
				}
				else if (Inventory::contFrostveil >= potionTypeNumber2 && potionType2 == 4)
				{
					Inventory::contFrostveil -= potionTypeNumber2;
				}
				else
					completed = false;//if second potion cant be delivered,
	}*/
		if (button && !completed)
		{
			if (potionNumber == 1)
			{
				if (*Inventory::potionCounters[potionType1] - potionTypeNumber1 >= 0)
				{
					*Inventory::potionCounters[potionType1] -= potionTypeNumber1;
					coinCounter += price;
					completed = true;
				}
			}
			if (potionNumber > 1)
			{
				if (*Inventory::potionCounters[potionType1] - potionTypeNumber1 >= 0 && *Inventory::potionCounters[potionType2] - potionTypeNumber2 >= 0)
				{
					*Inventory::potionCounters[potionType1] -= potionTypeNumber1;
					*Inventory::potionCounters[potionType2] -= potionTypeNumber2;
					coinCounter += price;
					completed = true;
				}
			}
		}
	}
	void Order::Draw(Surface* screen)
	{
		
		if (!completed)
		{
			screen->Print(order, 265, 236 + orderNumber * 35, 0x0);
			screen->Print(send, 475, 236 + orderNumber * 35, 0xff0000);
		}
		else
		{
			screen->Print(order, 265, 236 + orderNumber * 35, 0x0);
			screen->Print(complete, 475, 236 + orderNumber * 35, 0x00ff00);
		}
	}
	
};