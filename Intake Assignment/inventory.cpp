#include "inventory.h"

namespace Tmpl8
{
	int Inventory::contSunblossom = 2;
	int Inventory::contMoonleaf = 3;
	int Inventory::contEmberroot = 1;
	int Inventory::contFrostmint = 2;
	int Inventory::contBerry = 1;

	int Inventory::contVitalTonic = 0;
	int Inventory::contCalmMind = 0;
	int Inventory::contDreamDraught = 0;
	int Inventory::contFireHeart = 0;
	int Inventory::contFrostveil = 0;

	int Inventory::contSeedSunblossom = 12;
	int Inventory::contSeedMoonleaf = 0;
	int Inventory::contSeedEmberroot = 3;
	int Inventory::contSeedFrostmint = 0;
	int Inventory::contSeedBerry = 0;

	Inventory::Inventory( int x, int y) : x(x), y(y) 
	{
	}
	void Inventory::SetFrame(int frame)
	{
		inventory.SetFrame(frame);
	}
	void Inventory::DrawInventory(Surface* screen)
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
		if ((isopen && frame == 2) || (seedsisopen && frame == 3))
		{
			screen->Print(seedSunBlossom, 350, 236, 0x0);
			screen->Print(seedMoonLeaf, 350, 280, 0x0);
			screen->Print(seedEmberRoot, 350, 321, 0x0);
			screen->Print(seedFrostMint, 350, 367, 0x0);
			screen->Print(seedBerry, 350, 411, 0x0);
		}
	}	
	void Inventory::NormalInventory(Surface* screen, bool ePressed, int mouseX, int mouseY)
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
	void Inventory::CarInventory(Surface* screen, int mouseX, int mouseY, float worldX, float worldY, float reachX1, float reachY1, float reachX2, float reachY2)
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
			if (moved || clickedOutsideInv || GetAsyncKeyState('E'))
				carisopen = false;
		}

	}
	void Inventory::SeedsInventory(Surface* screen, int mouseX, int mouseY, float worldX, float worldY, bool tileClicekd)
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
			if (clickedOutsideInv || GetAsyncKeyState('E') || moved)
				seedsisopen = false;
		}

	}
	void Inventory::DrawOnScreen(Surface* screen, float deltaTime)
	{
		if (isopen || carisopen || seedsisopen)
			DrawInventory(screen);
	}
	bool Inventory::InventorysClosed()
	{
		if (!isopen && !carisopen && !seedsisopen)
			return 1;
		return 0;
	}
};