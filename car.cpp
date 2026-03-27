#include "car.h"
#include "inventory.h"
#include "input.h"
#include "player.h"

namespace Tmpl8
{
	Car::Car(Player& pl) : player(pl), inventory(player.pInventory()) {};
	int Car::CarInvIsOpen()
	{
		return carisopen;
	}
	int Car::getFrame()
	{
		return frame;
	}
	bool Car::CheckIfAnySeedButtonPressed()
	{
		if(button1 || button2 || button3 || button4 || button5)
			return true;
		return false;
	}
	void Car::UpdateOrderDays()
	{
		daysUntilOrderReset--;
	}
	void Car::BuySeeds(int& coinCounter)
	{
		// Buying seeds buttons
		button1 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 224 && Input::GetMouseY() <= 250;
		button2 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 267 && Input::GetMouseY() <= 293;
		button3 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 310 && Input::GetMouseY() <= 337;
		button4 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 355 && Input::GetMouseY() <= 379;
		button5 = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 458 && Input::GetMouseX() <= 499 && Input::GetMouseY() >= 394 && Input::GetMouseY() <= 420;
		// Buying seeds if car inventory is open
		if (carisopen && frame == 4)
		{
			// Buying Sunblossom seeds
			if (button1 && coinCounter >= 10)
			{
				//contSeedSunblossom++;
				inventory.AddItem(Inventory::Item::SeedSunblossom); // Add seed to inventory
				coinCounter -= 10;
			}
			// Buying Moonleaf seeds
			if (button2 && coinCounter >= 12)
			{
				inventory.AddItem(Inventory::Item::SeedMoonleaf); // Add seed to inventory
				coinCounter -= 12;
			}
			// Buying Emberroot seeds
			if (button3 && coinCounter >= 18)
			{
				inventory.AddItem(Inventory::Item::SeedEmberroot); // Add seed to inventory
				coinCounter -= 18;
			}
			// Buying Frostmint seeds
			if (button4 && coinCounter >= 20)
			{
				inventory.AddItem(Inventory::Item::SeedFrostmint); // Add seed to inventory
				coinCounter -= 20;
			}
			// Buying Nightshade Berry seeds
			if (button5 && coinCounter >= 30)
			{
				inventory.AddItem(Inventory::Item::SeedBerry); // Add seed to inventory
				coinCounter -= 30;
			}
		}
	}
	void Car::CarInventoryLogic(int& coinCounter, float mouseWorldX, float mouseWorldY)
	{
		// Detect clicks and player proximity
		bool clickedOutsideInv = Input::GetMouseButtonPressed(1) && !(Input::GetMouseX() >= 207 && Input::GetMouseX() <= 579 && Input::GetMouseY() >= 78 && Input::GetMouseY() <= 519);
		bool clickedOnShopButton = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 345 && Input::GetMouseX() <= 389 && Input::GetMouseY() >= 471 && Input::GetMouseY() <= 510;
		bool clickedOnOrdersButton = Input::GetMouseButtonPressed(1) && Input::GetMouseX() >= 399 && Input::GetMouseX() <= 444 && Input::GetMouseY() >= 471 && Input::GetMouseY() <= 510;
		bool playerCloseToCar = player.getReachX2() >= 528 && player.getReachX1() <= 686 && player.getReachY2() >= 175 && player.getReachY1() <= 220;
		bool mouseOnCar = mouseWorldX >= 528 && mouseWorldX <= 686 && mouseWorldY >= 175 && mouseWorldY <= 220;
		bool moved = Input::GetKeyPressed(SDL_SCANCODE_W) || Input::GetKeyPressed(SDL_SCANCODE_A) || Input::GetKeyPressed(SDL_SCANCODE_S) || Input::GetKeyPressed(SDL_SCANCODE_D);

		//Click car inventory
		if (carisopen) //This condition is first because we don't want to instantly buy seeds when opening the car inventory, only after its open
		{
			// Manage frame selection buttons
			if (clickedOnShopButton)
				frame = 4;
			if (clickedOnOrdersButton)
				frame = 5;
			if (moved || clickedOutsideInv || Input::GetKeyPressed(SDL_SCANCODE_E) || Input::GetKeyPressed(SDL_SCANCODE_Q) || inventory.MainInvIsOpen())
				carisopen = false;
			// Buy seeds logic
			BuySeeds(coinCounter);
		}
		carinventory.SetFrame(frame);

		//Toggle car inventory
		if (Input::GetMouseButtonPressed(1) && mouseOnCar && playerCloseToCar && !carisopen)
		{
			carisopen = true;
			frame = 4;
		}
	}
	void Car::DrawCarText(Surface* screen)
	{
		char counterSeedSunBlossom[32], counterSeedMoonLeaf[32], counterSeedEmberRoot[32], counterSeedFrostMint[32], counterSeedBerry[32];
		sprintf(counterSeedSunBlossom, "x%d", inventory.GetItemCount(Inventory::Item::SeedSunblossom));
		sprintf(counterSeedMoonLeaf, "x%d", inventory.GetItemCount(Inventory::Item::SeedMoonleaf));
		sprintf(counterSeedEmberRoot, "x%d", inventory.GetItemCount(Inventory::Item::SeedEmberroot));
		sprintf(counterSeedFrostMint, "x%d", inventory.GetItemCount(Inventory::Item::SeedFrostmint));
		sprintf(counterSeedBerry, "x%d", inventory.GetItemCount(Inventory::Item::SeedBerry));
		// Display when car shop inventory is open
		if (carisopen && frame == 4)
		{
			screen->PrintScaled(counterSeedSunBlossom, 510, 236, 2, 2, 0x0);
			screen->PrintScaled(counterSeedMoonLeaf, 510, 278, 2, 2, 0x0);
			screen->PrintScaled(counterSeedEmberRoot, 510, 321, 2, 2, 0x0);
			screen->PrintScaled(counterSeedFrostMint, 510, 364, 2, 2, 0x0);
			screen->PrintScaled(counterSeedBerry, 510, 405, 2, 2, 0x0);
		}
	}
	void Car::Draw(Surface* screen)
	{
		if (carisopen)
		{
			carinventory.Draw(screen, 140, 20);
			DrawCarText(screen);
		}
			
	}
	void Car::MakeNewOrders()
	{
		if (daysUntilOrderReset == 0)
		{
			//generate new orders
			daysUntilOrderReset = 5;
			srand(static_cast<unsigned int>(time(0)));
			orders.clear();
			for (int i = 0; i <= 5; i++)
				orders.emplace_back(i, inventory);
		}
	}
	void Car::UpdateOrders(int &coinCounter)
	{
		if (carisopen && frame == 5)
			for (auto& order : orders)
				order.Update(coinCounter);
	}
	void Car::DrawOrders(Surface* screen)
	{
		if (carisopen && frame == 5)
		{
			// Draw order text and button based on completion status
			char daysUntilResetText[64];
			sprintf(daysUntilResetText, "Days until orders reset: %d", daysUntilOrderReset);
			screen->PrintScaled(daysUntilResetText, 245, 92, 2, 2, 0x870101);
			for (auto& order : orders)
				order.Draw(screen);
		}
	}
}
