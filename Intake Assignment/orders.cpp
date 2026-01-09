#include "orders.h"
namespace Tmpl8
{
	Order::Order(int number)
	{
		orderNumber = number;
		potionNumber = 1 + IRand(3); // 1 to 2 potions (bigger chance for 2)
		potionTypeNumber1 = 1 + IRand(3); // 1 to 3 of first potion
		potionTypeNumber2 = 1 + IRand(3); // 1 to 3 of second potion
		potionType1 = IRand(5); // Type of first potion
		potionType2 = IRand(5); // Type of second potion
		while (potionType1 == potionType2) //ensure different potion types
			potionType2 = IRand(5);

		// Create order text and calculate price
		if (potionNumber == 1)
		{
			// Order with one potion
			sprintf(order, "%s x%d", potionsTypes[potionType1], potionTypeNumber1);
			price = priceNumbers[potionType1] * potionTypeNumber1;
		}
		else
		{
			// Order with two potions
			sprintf(order, "%s x%d, %s x%d", potionsTypes[potionType1], potionTypeNumber1, potionsTypes[potionType2], potionTypeNumber2);
			price = (priceNumbers[potionType1] * potionTypeNumber1) + (priceNumbers[potionType2] * potionTypeNumber2);
		}
		// Create send and complete texts
		sprintf(send, "send(%d)", price);
		sprintf(complete, "completed");
		//std::cout <<" Potion number: " << potionNumber << std::endl;
	}
	void Order::Logic(Surface* screen, bool &LeftPressed, int mouseX, int mouseY, int& coinCounter)
	{
		int range = 5; // Click range
		// Check if send button is clicked
		int button = LeftPressed && mouseX >= (475 - range) && mouseX <= (526 + range) && mouseY >= (235 + orderNumber * 35 - range) && mouseY <= (242 + orderNumber * 35 + range);
		// Button outline for debugging
		screen->Box(475 - range, 235 + orderNumber * 35 - range, 526 + range, 242 + orderNumber * 35 + range, 0x0);

		// Process order if button clicked and not completed
		if (button && !completed)
		{
			LeftPressed = false; // Reset left click state to avoid multiple clicks

			// Order with one potion
			if (potionNumber == 1) 
			{
				// Check if enough potions in inventory
				if (*Inventory::potionCounters[potionType1] - potionTypeNumber1 >= 0)
				{
					// Remove potions from inventory and add coins
					*Inventory::potionCounters[potionType1] -= potionTypeNumber1;
					coinCounter += price;
					// Mark order as completed
					completed = true;
				}
			}
			// Order with two potions
			if (potionNumber > 1)
			{
				// Check if enough potions in inventory
				if (*Inventory::potionCounters[potionType1] - potionTypeNumber1 >= 0 && *Inventory::potionCounters[potionType2] - potionTypeNumber2 >= 0)
				{
					// Remove potions from inventory and add coins
					*Inventory::potionCounters[potionType1] -= potionTypeNumber1;
					*Inventory::potionCounters[potionType2] -= potionTypeNumber2;
					coinCounter += price;
					// Mark order as completed
					completed = true;
				}
			}
		}
	}
	void Order::Draw(Surface* screen)
	{
		// Draw order text and button based on completion status
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