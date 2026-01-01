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

		int contVitalTonic = 0;
		int contCalmMind = 0;
		int contDreamDraught = 0;
		int contFireHeart = 0;
		int contFrostveil = 0;

		int contSeedSunblossom = 12;
		int contSeedMoonleaf = 0;
		int contSeedEmberroot = 3;
		int contSeedFrostmint = 0;
		int contSeedBerry = 0;

		Sprite inventory = Sprite(new Surface("assets/Inventory.png"), 6);

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
				screen->Print(seedSunBlossom, 350, 236, 0x0);
				screen->Print(seedMoonLeaf, 350, 280, 0x0);
				screen->Print(seedEmberRoot, 350, 321, 0x0);
				screen->Print(seedFrostMint, 350, 367, 0x0);
				screen->Print(seedBerry, 350, 411, 0x0);
			}
			if (carisopen && frame == 4)
			{
				screen->Print(sunBlossom, 350 - 30, 236, 0x0);
				screen->Print(moonLeaf, 350 - 30, 280, 0x0);
				screen->Print(emberRoot, 350 - 30, 321, 0x0);
				screen->Print(frostMint, 350 - 30, 367, 0x0);
				screen->Print(berry, 350 - 30, 411, 0x0);
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
		void CarInventory(Surface* screen, bool ePressed, int mouseX, int mouseY, float worldX, float worldY, float reachX1, float reachY1, float reachX2, float reachY2)
		{
			bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
			bool clickedOnShopButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 345 && mouseX <= 389 && mouseY >= 471 && mouseY <= 510;
			bool clickedOnOrdersButton = GetAsyncKeyState(VK_LBUTTON) && mouseX >= 399 && mouseX <= 444 && mouseY >= 471 && mouseY <= 510;
			//bool playerCloseToCar = worldPlayerX >= 448 && worldPlayerX <= 688 && worldPlayerY >= 86 && worldPlayerY <= 195;
			bool playerCloseToCar = reachX2 >= 528 && reachX1 <= 686 && reachY2 >= 175 && reachY1 <= 220;
			bool clickedOnCar = worldX >= 528 && worldX <= 686 && worldY >= 175 && worldY <= 220;
			bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

			//Toggle car inventory
			if (GetAsyncKeyState(VK_LBUTTON) && clickedOnCar && playerCloseToCar)
			{
				isopen = false;
				carisopen = false;
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
		void SeedsInventory(Surface* screen, bool ePressed, int mouseX, int mouseY, float worldX, float worldY, bool tileClicekd)
		{
			bool clickedOutsideInv = GetAsyncKeyState(VK_LBUTTON) && !(mouseX >= 207 && mouseX <= 579 && mouseY >= 78 && mouseY <= 519);
			bool moved = GetAsyncKeyState('W') || GetAsyncKeyState('A') || GetAsyncKeyState('S') || GetAsyncKeyState('D');

			//Toggle seed inventory
			if (GetAsyncKeyState(VK_LBUTTON) && tileClicekd)
			{
				isopen = false;
				carisopen = false;
				seedsisopen = !seedsisopen;
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
		bool InventorysClosed()
		{
			if (!isopen && !carisopen && !seedsisopen)
				return 1;
			return 0;
		}
	}
};