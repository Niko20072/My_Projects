#include "orders.h"
#include "input.h"
#include "template.h"
#include "inventory.h"

namespace Tmpl8
{
	int range = 5; // Click range (and Button outline)
	Order::Order(int number, Inventory& inv) : inventory(inv)
	{
		orderNumber = number;
		potionNumber = 1 + IRand(3); // 1 to 2 potions (bigger chance for 2)
		potionType1 = IRand(5); // Type of first potion (0-5)
		potionType2 = IRand(5); // Type of second potion (0-5)
		numberPotionType1 = 1 + IRand(3); // How many potions of the first type are generated (1-3)
		numberOfPotionType2 = 1 + IRand(3); // // How many potions of the first type are generated (1-3)
		while (potionType1 == potionType2) // Ensure different potion types
			potionType2 = IRand(5);

		// Create order text and calculate price
		if (potionNumber == 1)
		{
			// Order with one potion
			sprintf(order, "%s x%d", potionsTypes[potionType1], numberPotionType1);
			price = priceNumbers[potionType1] * numberPotionType1;
		}
		else
		{
			// Order with two potions
			sprintf(order, "%s x%d, %s x%d", potionsTypes[potionType1], numberPotionType1, potionsTypes[potionType2], numberOfPotionType2);
			int rewardBonus = 30 * (numberPotionType1 + numberOfPotionType2); // Bonus for two potions 
			price = (priceNumbers[potionType1] * numberPotionType1) + (priceNumbers[potionType2] * numberOfPotionType2) + rewardBonus;
		}

		// Create send and complete texts
		sprintf(send, "send(%d)", price);
		sprintf(complete, "completed");
		//std::cout <<" Potion number: " << potionNumber << std::endl;
	}
	void Order::Logic(int& coinCounter)
	{
		// Check if send button is clicked
		int button = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= (475 - range) && Input::GetMouseX() <= (526 + range) && Input::GetMouseY() >= (235 + orderNumber * 35 - range) && Input::GetMouseY() <= (242 + orderNumber * 35 + range);

		// Process order if button clicked and not completed
		if (button && !completed)
		{
			Inventory::Item potion1 = static_cast<Inventory::Item>(potionType1); // Convert potion type to inventory item
			Inventory::Item potion2 = static_cast<Inventory::Item>(potionType2);

			// Order with one potion
			if (potionNumber == 1)
			{
				// Check if enough potions in inventory
				if (inventory.GetItemCount(potion1) >= numberPotionType1)
				{
					// Remove potions from inventory and add coins
					inventory.AddItem(potion1, -numberPotionType1); // Remove potions from inventory
					coinCounter += price;
					// Mark order as completed
					completed = true;
				}
			}
			// Order with two potions
			if (potionNumber > 1)
			{
				// Check if enough potions in inventory
				if (inventory.GetItemCount(potion1) >= numberPotionType1 && inventory.GetItemCount(potion2) >= numberOfPotionType2)
				{
					// Remove potions from inventory and add coins
					inventory.AddItem(potion1, -numberPotionType1); // Remove potions from inventory
					inventory.AddItem(potion2, -numberOfPotionType2);
					coinCounter += price;
					// Mark order as completed
					completed = true;
				}
			}
		}
	}
	void Order::Draw(Surface* screen)
	{
		int hover = Input::GetMouseX() >= (475 - range) && Input::GetMouseX() <= (526 + range) && Input::GetMouseY() >= (235 + orderNumber * 35 - range) && Input::GetMouseY() <= (242 + orderNumber * 35 + range);

		// Button outline
		if (hover && !completed)
			screen->Box(475 - range, 235 + orderNumber * 35 - range, 526 + range, 242 + orderNumber * 35 + range, 0xfffb00); 
		else
			screen->Box(475 - range, 235 + orderNumber * 35 - range, 526 + range, 242 + orderNumber * 35 + range, 0x0);

		// Order text
		if (completed)
		{
			screen->Print(order, 265, 236 + orderNumber * 35, 0x0);
			screen->Print(complete, 475, 236 + orderNumber * 35, 0x00ff00);
		}
		else
		{
			screen->Print(order, 265, 236 + orderNumber * 35, 0x0);
			screen->Print(send, 475, 236 + orderNumber * 35, 0xff0000);
		}
	}
};