#include "inventory.h"

namespace Tmpl8
{
	namespace Inventory
	{
		int x = 10, y = 10;
		int frame = 0;
		bool isopen = false;
		bool carisopen = false;
		bool seedsisopen = false;

		int contSunblossom = 2;
		int contMoonleaf = 3;
		int contEmberroot = 2;
		int contFrostmint = 2;
		int contBerry = 1;

		int contVitalTonic = 10;
		int contCalmMind = 10;
		int contDreamDraught = 10;
		int contFireHeart = 1;
		int contFrostveil = 0;

		int contSeedSunblossom = 12;
		int contSeedMoonleaf = 0;
		int contSeedEmberroot = 3;
		int contSeedFrostmint = 0;
		int contSeedBerry = 0;

		std::vector<int*> potionCounters = { &contVitalTonic, &contCalmMind, &contDreamDraught, &contFireHeart, &contFrostveil };

		Sprite inventory = Sprite(new Surface("assets/invagain.png"), 6);

		void SetFrame(int frame)
		{
			inventory.SetFrame(frame);
		}
		void DrawInventory(Surface* screen)
		{
			inventory.Draw(screen, 140, 20);
			char sunBlossom[32], moonLeaf[32], emberRoot[32], frostMint[32], berry[32];
			char vitalTonic[32], calmMind[32], dreamDraught[32], fireHeart[32], frostVeil[32];
			char seedSunBlossom[32], seedMoonLeaf[32], seedEmberRoot[32], seedFrostMint[32], seedBerry[32];
			char counterSeedSunBlossom[32], counterSeedMoonLeaf[32], counterSeedEmberRoot[32], counterSeedFrostMint[32], counterSeedBerry[32];

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

			if (isopen && frame == 0)
			{
				screen->Print(sunBlossom, 350, 236, 0x0);
				screen->Print(moonLeaf, 350, 280, 0x0);
				screen->Print(emberRoot, 350, 321, 0x0);
				screen->Print(frostMint, 350, 367, 0x0);
				screen->Print(berry, 350, 411, 0x0);
			}
			if (isopen && frame == 1)
			{
				screen->Print(vitalTonic, 350, 241, 0x0);
				screen->Print(calmMind, 350, 285, 0x0);
				screen->Print(dreamDraught, 350, 328, 0x0);
				screen->Print(fireHeart, 350, 373, 0x0);
				screen->Print(frostVeil, 350, 418, 0x0);
			}
			if (isopen && frame == 2)
			{
				screen->Print(seedSunBlossom, 350, 236, 0x0);
				screen->Print(seedMoonLeaf, 350, 280, 0x0);
				screen->Print(seedEmberRoot, 350, 321, 0x0);
				screen->Print(seedFrostMint, 350, 367, 0x0);
				screen->Print(seedBerry, 350, 411, 0x0);
			}
			if (seedsisopen && frame == 3)
			{
				screen->Print(counterSeedSunBlossom, 350 + 160, 236, 0x0);
				screen->Print(counterSeedMoonLeaf, 350 + 160, 280, 0x0);
				screen->Print(counterSeedEmberRoot, 350 + 160, 321, 0x0);
				screen->Print(counterSeedFrostMint, 350 + 160, 367, 0x0);
				screen->Print(counterSeedBerry, 350 + 160, 411, 0x0);
			}
			if (carisopen && frame == 4)
			{
				screen->Print(counterSeedSunBlossom, 350 + 160, 236, 0x0);
				screen->Print(counterSeedMoonLeaf, 350 + 160, 280, 0x0);
				screen->Print(counterSeedEmberRoot, 350 + 160, 321, 0x0);
				screen->Print(counterSeedFrostMint, 350 + 160, 367, 0x0);
				screen->Print(counterSeedBerry, 350 + 160, 411, 0x0);
			}
		}
		void NormalInventory(Surface* screen, bool ePressed, int mouseX, int mouseY)
		{
			bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
			bool clickedOnPlantButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 323 && mouseX <= 366 && mouseY >= 471 && mouseY <= 510;
			bool clickedOnPotionButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 375 && mouseX <= 510 && mouseY >= 471 && mouseY <= 510;
			bool clickedOnSeedButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 430 && mouseX <= 475 && mouseY >= 471 && mouseY <= 510;

			//Toggle normal inventory
			if (ePressed)
			{
				carisopen = false;
				seedsisopen = false;
				isopen = !isopen;
				frame = 0;
				inventory.SetFrame(frame);
			}

			//Click inventory
			if (isopen)
			{
				if (clickedOnPlantButton)
				{
					frame = 0;
					inventory.SetFrame(frame);
				}
				if (clickedOnPotionButton)
				{
					frame = 1;
					inventory.SetFrame(frame);
				}
				if (clickedOnSeedButton)
				{
					frame = 2;
					inventory.SetFrame(frame);
				}
				if (clickedOutsideInv)
					isopen = false;
			}

		}
		void CarInventory(Surface* screen, bool ePressed, bool &leftPressed, int mouseX, int mouseY, float worldX, float worldY, float reachX1, float reachY1, float reachX2, float reachY2)
		{
			bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
			bool clickedOnShopButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 345 && mouseX <= 389 && mouseY >= 471 && mouseY <= 510;
			bool clickedOnOrdersButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 399 && mouseX <= 444 && mouseY >= 471 && mouseY <= 510;
			//bool playerCloseToCar = worldPlayerX >= 448 && worldPlayerX <= 688 && worldPlayerY >= 86 && worldPlayerY <= 195;
			bool playerCloseToCar = reachX2 >= 528 && reachX1 <= 686 && reachY2 >= 175 && reachY1 <= 220;
			bool clickedOnCar = worldX >= 528 && worldX <= 686 && worldY >= 175 && worldY <= 220;
			bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

			//Toggle car inventory
			if (leftPressed && clickedOnCar && playerCloseToCar && !carisopen)
			{
				leftPressed = false;
				isopen = false;
				seedsisopen = false;
				carisopen = !carisopen;
				frame = 4;
				inventory.SetFrame(frame);
			}

			//Click car inventory
			if (carisopen)
			{
				if (clickedOnShopButton)
				{
					frame = 4;
					inventory.SetFrame(frame);
				}
				if (clickedOnOrdersButton)
				{
					frame = 5;
					inventory.SetFrame(frame);
				}
				if (moved || clickedOutsideInv || ePressed)
					carisopen = false;
			}

		}
		void SeedsInventory(Surface* screen, bool ePressed, bool &leftPressed, int mouseX, int mouseY, float worldX, float worldY, bool tileClicekd)
		{
			bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
			bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

			//Toggle seed inventory
			if (leftPressed && tileClicekd && seedsisopen == false)
			{
				isopen = false;
				carisopen = false;
				leftPressed = false;
				seedsisopen = true;
				frame = 3;
				inventory.SetFrame(frame);
			}

			//Click seed inventory
			if (seedsisopen)
			{
				if (clickedOutsideInv || ePressed || moved)
					seedsisopen = false;
			}

		}
		void DrawOnScreen(Surface* screen, float deltaTime)
		{
			if (isopen || carisopen || seedsisopen)
				DrawInventory(screen);
		}
		void BuySeeds(Surface* screen, bool leftPressed, int& coinCounter, int mouseX, int mouseY)
		{
			//buying seeds
			bool button1 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 224 && mouseY <= 250;
			bool button2 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 267 && mouseY <= 293;
			bool button3 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 310 && mouseY <= 337;
			bool button4 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 355 && mouseY <= 379;
			bool button5 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 394 && mouseY <= 420;
			if (carisopen && frame == 4)
			{
				if (button1 && coinCounter >= 10)
				{
					Inventory::contSeedSunblossom++;
					coinCounter -= 10;
				}
				if (button2 && coinCounter >= 12)
				{
					Inventory::contSeedMoonleaf++;
					coinCounter -= 12;
				}
				if (button3 && coinCounter >= 18)
				{
					Inventory::contSeedEmberroot++;
					coinCounter -= 18;
				}
				if (button4 && coinCounter >= 20)
				{
					Inventory::contSeedFrostmint++;
					coinCounter -= 20;
				}
				if (button5 && coinCounter >= 30)
				{
					Inventory::contSeedBerry++;
					coinCounter -= 30;
				}
			}
		}
		void PlantSeeds(Surface* screen, bool leftPressed, int mouseX, int mouseY)
		{
			//buying seeds
			bool button1 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 224 && mouseY <= 250;
			bool button2 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 267 && mouseY <= 293;
			bool button3 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 310 && mouseY <= 337;
			bool button4 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 355 && mouseY <= 379;
			bool button5 = leftPressed && mouseX >= 458 && mouseX <= 499 && mouseY >= 394 && mouseY <= 420;
			if (seedsisopen)
			{
				if (button1 && contSeedSunblossom > 0)
				{
					Inventory::contSeedSunblossom--;
					seedsisopen = false;
				}
				if (button2 && contSeedMoonleaf > 0)
				{
					Inventory::contSeedMoonleaf--;
					seedsisopen = false;
				}
				if (button3 && contSeedEmberroot > 0)
				{
					Inventory::contSeedEmberroot--;
					seedsisopen = false;
					
				}
				if (button4 && contSeedFrostmint > 0)
				{
					Inventory::contSeedFrostmint--;
					seedsisopen = false;
					
				}
				if (button5 && contSeedBerry > 0)
				{
					Inventory::contSeedBerry--;
					seedsisopen = false;
				}
			}
		}
		bool InventorysClosed()
		{
			if (!isopen && !carisopen && !seedsisopen)
				return 1;
			return 0;
		}
	}
};