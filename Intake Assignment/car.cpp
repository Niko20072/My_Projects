#include "car.h"

namespace Tmpl8
{
	int Car::CarInvIsOpen()
	{
		return carisopen;
	}
	int Car::getFrame()
	{
		return frame;
	}
	void Car::UpdateOrderDays()
	{
		daysUntilOrderReset--;
	}
	void Car::BuySeeds(int& coinCounter)
	{
		// Buying seeds buttons
		bool button1 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 224 && WorldState::mouseY <= 250;
		bool button2 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 267 && WorldState::mouseY <= 293;
		bool button3 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 310 && WorldState::mouseY <= 337;
		bool button4 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 355 && WorldState::mouseY <= 379;
		bool button5 = Buttons::leftPressed && WorldState::mouseX >= 458 && WorldState::mouseX <= 499 && WorldState::mouseY >= 394 && WorldState::mouseY <= 420;

		// Buying seeds if car inventory is open
		if (carisopen && frame == 4)
		{
			// Buying Sunblossom seeds
			if (button1 && coinCounter >= 10)
			{
				//contSeedSunblossom++;
				inventory.AddItem(Inventory::Item::SeedSunblossom); // Add seed to inventory
				coinCounter -= 10;
				Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
			}
			// Buying Moonleaf seeds
			if (button2 && coinCounter >= 12)
			{
				inventory.AddItem(Inventory::Item::SeedMoonleaf); // Add seed to inventory
				coinCounter -= 12;
				Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
			}
			// Buying Emberroot seeds
			if (button3 && coinCounter >= 18)
			{
				inventory.AddItem(Inventory::Item::SeedEmberroot); // Add seed to inventory
				coinCounter -= 18;
				Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
			}
			// Buying Frostmint seeds
			if (button4 && coinCounter >= 20)
			{
				inventory.AddItem(Inventory::Item::SeedFrostmint); // Add seed to inventory
				coinCounter -= 20;
				Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
			}
			// Buying Nightshade Berry seeds
			if (button5 && coinCounter >= 30)
			{
				inventory.AddItem(Inventory::Item::SeedBerry); // Add seed to inventory
				coinCounter -= 30;
				Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
			}
		}
	}
	void Car::CarInventoryLogic(int& coinCounter)
	{
		// Detect clicks and player proximity
		bool clickedOutsideInv = Buttons::leftPressed && !(WorldState::mouseX >= 207 && WorldState::mouseX <= 579 && WorldState::mouseY >= 78 && WorldState::mouseY <= 519);
		bool clickedOnShopButton = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 345 && WorldState::mouseX <= 389 && WorldState::mouseY >= 471 && WorldState::mouseY <= 510;
		bool clickedOnOrdersButton = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 399 && WorldState::mouseX <= 444 && WorldState::mouseY >= 471 && WorldState::mouseY <= 510;
		bool playerCloseToCar = WorldState::reachX2 >= 528 && WorldState::reachX1 <= 686 && WorldState::reachY2 >= 175 && WorldState::reachY1 <= 220;
		bool clickedOnCar = WorldState::worldX >= 528 && WorldState::worldX <= 686 && WorldState::worldY >= 175 && WorldState::worldY <= 220;
		bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

		//Toggle car inventory
		if (Buttons::leftPressed && clickedOnCar && playerCloseToCar && !carisopen)
		{
			Buttons::leftPressed = false; // Reset left click state to avoid multiple clicks
			//inventoryisopen = false;
			carisopen = !carisopen;
			frame = 4;
		}

		//Click car inventory
		if (carisopen)
		{
			// Manage frame selection buttons
			if (clickedOnShopButton)
				frame = 4;
			if (clickedOnOrdersButton)
				frame = 5;
			if (moved || clickedOutsideInv || Buttons::ePressed || Buttons::qPressed || inventory.MainInvIsOpen())
				carisopen = false;
		}
		carinventory.SetFrame(frame);

		// Buy seeds logic
		BuySeeds(coinCounter);
	}
	void Car::Draw(Surface* screen)
	{
		if (carisopen)
			carinventory.Draw(screen, 140, 20);
	}
	void Car::MakeNewOrders()
	{
		//check if all orders are completed
		if (daysUntilOrderReset == 0) ///or CheckAllCompleted()
		{
			//generate new orders
			daysUntilOrderReset = 5;
			srand(time(0));
			orders.clear();
			for (int i = 0; i <= 5; i++)
				orders.emplace_back(i, inventory);
		}
	}
	void Car::UpdateOrders(int &coinCounter)
	{
		if (carisopen && frame == 5)
			for (auto& x : orders)
				x.Logic(coinCounter);
	}
	void Car::DrawOrders(Surface* screen)
	{
		if (carisopen && frame == 5)
		{
			// Draw order text and button based on completion status
			char daysUntilResetText[64];
			sprintf(daysUntilResetText, "Days until order reset: %d", daysUntilOrderReset);
			screen->Print(daysUntilResetText, 330, 94, 0x0);
			for (auto& x : orders)
				x.Draw(screen);
		}
	}
}
