#include "inventory.h"

namespace Tmpl8//sterge
{
		//namespace to class de ce
		int Inventory::getFrame()
		{
			return frame;
		}
		int Inventory::getCarState()
		{
			return carisopen;
		}
		int Inventory::getInvState()
		{
			return inventoryisopen;
		}
		int Inventory::getSeedState()
		{
			return seedsisopen;
		}
		void Inventory::setSeedState(bool state)
		{
			seedsisopen = state;
		}

		int Inventory::getContSunblossom()
		{
			return contSunblossom;
		}
		int Inventory::getContMoonleaf()
		{
			return contMoonleaf;
		}
		int Inventory::getContEmberroot()
		{
			return contEmberroot;
		}
		int Inventory::getContFrostmint()
		{
			return contFrostmint;
		}
		int Inventory::getContBerry()
		{
			return contBerry;
		}
		int Inventory::getContVitalTonic()
		{
			return contVitalTonic;
		}
		int Inventory::getContCalmMind()
		{
			return contCalmMind;
		}
		int Inventory::getContDreamDraught()
		{
			return contDreamDraught;
		}
		int Inventory::getContFireHeart()
		{
			return contFireHeart;
		}
		int Inventory::getContFrostveil()
		{
			return contFrostveil;
		}
		int Inventory::getContSeedSunblossom()
		{
			return contSeedSunblossom;
		}
		int Inventory::getContSeedMoonleaf()
		{
			return contSeedMoonleaf;
		}
		int Inventory::getContSeedEmberroot()
		{
			return contSeedEmberroot;
		}
		int Inventory::getContSeedFrostmint()
		{
			return contSeedFrostmint;
		}
		int Inventory::getContSeedBerry()
		{
			return contSeedBerry;
		}

		void Inventory::addContSunblossom()
		{
			contSunblossom++;
		}
		void Inventory::addContMoonleaf()
		{
			contMoonleaf++;
		}
		void Inventory::addContEmberroot()
		{
			contEmberroot++;
		}
		void Inventory::addContFrostmint()
		{
			contFrostmint++;
		}
		void Inventory::addContBerry()
		{
			contBerry++;
		}

		void Inventory::BuySeeds(Surface* screen, int& coinCounter)
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
					Inventory::contSeedSunblossom++;
					coinCounter -= 10;
					Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
				}
				// Buying Moonleaf seeds
				if (button2 && coinCounter >= 12)
				{
					Inventory::contSeedMoonleaf++;
					coinCounter -= 12;
					Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
				}
				// Buying Emberroot seeds
				if (button3 && coinCounter >= 18)
				{
					Inventory::contSeedEmberroot++;
					coinCounter -= 18;
					Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
				}
				// Buying Frostmint seeds
				if (button4 && coinCounter >= 20)
				{
					Inventory::contSeedFrostmint++;
					coinCounter -= 20;
					Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
				}
				// Buying Nightshade Berry seeds
				if (button5 && coinCounter >= 30)
				{
					Inventory::contSeedBerry++;
					coinCounter -= 30;
					Buttons::leftPressed = false; // Reset left click state to avoid multiple purchases
				}
			}
		}
		void Inventory::DrawInventory(Surface* screen)
		{
			// Draw inventory
			inventory.Draw(screen, 140, 20);
			inventory.SetFrame(frame);
			// Display values
			char sunBlossom[32], moonLeaf[32], emberRoot[32], frostMint[32], berry[32];
			char vitalTonic[32], calmMind[32], dreamDraught[32], fireHeart[32], frostVeil[32];
			char seedSunBlossom[32], seedMoonLeaf[32], seedEmberRoot[32], seedFrostMint[32], seedBerry[32];
			char counterSeedSunBlossom[32], counterSeedMoonLeaf[32], counterSeedEmberRoot[32], counterSeedFrostMint[32], counterSeedBerry[32];

			// Format strings with current counts
			sprintf(sunBlossom, "Sunblossom          x%d", contSunblossom);
			sprintf(moonLeaf, "Moonleaf            x%d", contMoonleaf);
			sprintf(emberRoot, "Emberroot           x%d", contEmberroot);
			sprintf(frostMint, "Frostmint           x%d", contFrostmint);
			sprintf(berry, "Nightshade Berry    x%d", contBerry);

			sprintf(vitalTonic, "Vital Tonic         x%d", contVitalTonic);
			sprintf(calmMind, "Calm Mind Elixir    x%d", contCalmMind);
			sprintf(dreamDraught, "Dream Draught       x%d", contDreamDraught);
			sprintf(fireHeart, "FireHeart Brew      x%d", contFireHeart);
			sprintf(frostVeil, "Frostveil Potion    x%d", contFrostveil);

			sprintf(seedSunBlossom, "Sunblossom          x%d", contSeedSunblossom);
			sprintf(seedMoonLeaf, "Moonleaf            x%d", contSeedMoonleaf);
			sprintf(seedEmberRoot, "Emberroot           x%d", contSeedEmberroot);
			sprintf(seedFrostMint, "Frostmint           x%d", contSeedFrostmint);
			sprintf(seedBerry, "Nightshade Berry    x%d", contSeedBerry);

			sprintf(counterSeedSunBlossom, "x%d", contSeedSunblossom);
			sprintf(counterSeedMoonLeaf, "x%d", contSeedMoonleaf);
			sprintf(counterSeedEmberRoot, "x%d", contSeedEmberroot);
			sprintf(counterSeedFrostMint, "x%d", contSeedFrostmint);
			sprintf(counterSeedBerry, "x%d", contSeedBerry);

			// Display when ingredients inventory is open
			if (inventoryisopen && frame == 0)
			{
				screen->Print(sunBlossom, 350, 236, 0x0);
				screen->Print(moonLeaf, 350, 280, 0x0);
				screen->Print(emberRoot, 350, 321, 0x0);
				screen->Print(frostMint, 350, 367, 0x0);
				screen->Print(berry, 350, 411, 0x0);
			}
			// Display when potions inventory is open
			if (inventoryisopen && frame == 1)
			{
				screen->Print(vitalTonic, 350, 241, 0x0);
				screen->Print(calmMind, 350, 285, 0x0);
				screen->Print(dreamDraught, 350, 328, 0x0);
				screen->Print(fireHeart, 350, 373, 0x0);
				screen->Print(frostVeil, 350, 418, 0x0);
			}
			// Display when seeds inventory is open
			if (inventoryisopen && frame == 2)
			{
				screen->Print(seedSunBlossom, 350, 236, 0x0);
				screen->Print(seedMoonLeaf, 350, 280, 0x0);
				screen->Print(seedEmberRoot, 350, 321, 0x0);
				screen->Print(seedFrostMint, 350, 367, 0x0);
				screen->Print(seedBerry, 350, 411, 0x0);
			}
			// Display when planting seeds inventory is open
			if (seedsisopen && frame == 3)
			{
				screen->Print(counterSeedSunBlossom, 350 + 160, 236, 0x0);
				screen->Print(counterSeedMoonLeaf, 350 + 160, 280, 0x0);
				screen->Print(counterSeedEmberRoot, 350 + 160, 321, 0x0);
				screen->Print(counterSeedFrostMint, 350 + 160, 367, 0x0);
				screen->Print(counterSeedBerry, 350 + 160, 411, 0x0);
			}
			// Display when car shop inventory is open
			if (carisopen && frame == 4)
			{
				screen->Print(counterSeedSunBlossom, 350 + 160, 236, 0x0);
				screen->Print(counterSeedMoonLeaf, 350 + 160, 280, 0x0);
				screen->Print(counterSeedEmberRoot, 350 + 160, 321, 0x0);
				screen->Print(counterSeedFrostMint, 350 + 160, 367, 0x0);
				screen->Print(counterSeedBerry, 350 + 160, 411, 0x0);
			}
		}
		void Inventory::MainInventory(Surface* screen)
		{
			// Detect clicks
			bool clickedOutsideInv = Buttons::leftPressed && !(WorldState::mouseX >= 207 && WorldState::mouseX <= 579 && WorldState::mouseY >= 78 && WorldState::mouseY <= 519);
			bool clickedOnPlantButton = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 323 && WorldState::mouseX <= 366 && WorldState::mouseY >= 471 && WorldState::mouseY <= 510;
			bool clickedOnPotionButton = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 375 && WorldState::mouseX <= 510 && WorldState::mouseY >= 471 && WorldState::mouseY <= 510;
			bool clickedOnSeedButton = GetAsyncKeyState(VK_LBUTTON) && WorldState::mouseX >= 430 && WorldState::mouseX <= 475 && WorldState::mouseY >= 471 && WorldState::mouseY <= 510;

			//Toggle normal inventory
			if (Buttons::ePressed && !inventoryisopen)
			{
				carisopen = false;
				Buttons::ePressed = false;
				seedsisopen = false;
				inventoryisopen = true;
				frame = 0;
			}

			//Click inventory
			if (inventoryisopen)
			{
				// Manage frame selection buttons
				if (clickedOnPlantButton)
					frame = 0;
				if (clickedOnPotionButton)
					frame = 1;
				if (clickedOnSeedButton)
					frame = 2;
				if (clickedOutsideInv || Buttons::qPressed || Buttons::ePressed)
					inventoryisopen = false;
			}

		}
		void Inventory::CarInventory(Surface* screen, int& coinCounter)
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
				inventoryisopen = false;
				seedsisopen = false;
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
				if (moved || clickedOutsideInv || Buttons::ePressed || Buttons::qPressed)
					carisopen = false;
			}

			// Buy seeds logic
			BuySeeds(screen, coinCounter);
		}
		void Inventory::SeedsInventory(Surface* screen, float plantX, float plantY, bool tileClicekd)
		{
			// Detect clicks
			bool clickedOutsideInv = Buttons::leftPressed && !(WorldState::mouseX >= 207 && WorldState::mouseX <= 579 && WorldState::mouseY >= 78 && WorldState::mouseY <= 519);
			bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

			//Toggle seed inventory
			if (tileClicekd && seedsisopen == false && !wateringCan.getState())
			{
				inventoryisopen = false;
				carisopen = false;
				seedsisopen = true;
				frame = 3;
			}

			//Click seed inventory
			if (seedsisopen)
			{
				if (clickedOutsideInv || Buttons::ePressed || Buttons::qPressed || moved)
					seedsisopen = false;
			}
		}
		void Inventory::Draw(Surface* screen)
		{
			// Draw inventory if any is open
			if (inventoryisopen || carisopen || seedsisopen)
			{
				DrawInventory(screen);
				wateringCan.setState(false); // Disable watering can when any inventory is open
			}
				
		}
		bool Inventory::InventorysClosed()
		{
			// Check if all inventories are closed
			if (!inventoryisopen && !carisopen && !seedsisopen)
				return 1;
			return 0;
		}

		
}